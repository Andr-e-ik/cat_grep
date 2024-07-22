#include <regex.h>
#include <stdio.h>
#include <string.h>
#define SIZE 16
#define SIZE_BUF 2048
struct options {
  int e;
  int i_flag;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char *patterns[SIZE];
  char *patterns_files[SIZE];
  char *files[SIZE];
  char pattern[SIZE_BUF];
  int count_files;
  int count_matches;
};
void Parser(int argc, char *argv[], struct options *opt);
void Parse_e(struct options *opt, char *argv[], int *i, int j,
             int *count_patterns);
void Parse_f(struct options *opt, char *argv[], int *i, int j,
             int *pattern_files);
void Grep(struct options *opt);
void Proccesing_patt(struct options *opt);
void Proccesing_patt_files(struct options *opt, int num);
void Processing_main_data(struct options *opt, char *line, char *file_name,
                          int num);
void Proccesing_aux_data(struct options *opt, char *file_name);
void Proccesing_o(regex_t regex, char *line, struct options *opt);

int main(int argc, char *agrv[]) {
  struct options opt = {0};
  Parser(argc, agrv, &opt);
  Grep(&opt);
  return 0;
}

void Parser(int argc, char *argv[], struct options *opt) {
  int count_files = 0;
  int count_patterns = 0;
  int pattern_files = 0;
  int error = 1;

  for (int i = 1; i < argc; i++) {
    if (error) {
      if (argv[i][0] == '-') {
        if (argv[i][1] == 'e') {
          Parse_e(opt, argv, &i, 2, &count_patterns);

        } else if (argv[i][1] == 'f') {
          Parse_f(opt, argv, &i, 2, &pattern_files);

        } else {
          int len = strlen(argv[i]);
          for (int j = 1; j < len; j++) {
            switch (argv[i][j]) {
              case 'i':
                opt->i_flag = 1;
                break;
              case 'e':
                Parse_e(opt, argv, &i, j + 1, &count_patterns);
                j = len;
                break;
              case 'v':
                opt->v = 1;
                break;
              case 'c':
                opt->c = 1;
                break;
              case 'l':
                opt->l = 1;
                break;
              case 'n':
                opt->n = 1;
                break;
              case 'h':
                opt->h = 1;
                break;
              case 's':
                opt->s = 1;
                break;
              case 'f':
                Parse_f(opt, argv, &i, j + 1, &pattern_files);
                j = len;
                break;
              case 'o':
                opt->o = 1;
                break;
              default:
                error = -1;
            }
          }
        }
      } else if (!opt->e && !opt->f) {
        opt->e = 1;
        opt->patterns[count_patterns++] = argv[i];
      } else {
        opt->files[count_files++] = argv[i];
      }
    } else {
      puts("no work flags");
      count_files = 0;
      break;
    }
  }

  if (error) {
    if (opt->o && (opt->l || opt->v || opt->c)) {
      opt->o = 0;
    }
  }
  opt->count_files = count_files;
}

void Parse_e(struct options *opt, char *argv[], int *i, int j,
             int *count_patterns) {
  opt->e = 1;
  if (argv[*i][j] != '\0') {
    char buf[SIZE_BUF] = "";
    strcat(buf, argv[*i] + j);
    opt->patterns[(*count_patterns)++] = buf;
  } else {
    opt->patterns[(*count_patterns)++] = argv[++(*i)];
  }
}

void Parse_f(struct options *opt, char *argv[], int *i, int j,
             int *pattern_files) {
  opt->f = 1;
  if (argv[*i][j] != '\0') {
    char buf[SIZE_BUF] = "";
    strcat(buf, argv[*i] + j);
    opt->patterns_files[(*pattern_files)++] = buf;
  } else {
    opt->patterns_files[(*pattern_files)++] = argv[++(*i)];
  }
}

void Grep(struct options *opt) {
  Proccesing_patt(opt);
  for (int i = 0; i < opt->count_files; i++) {
    FILE *fp = fopen(opt->files[i], "r");
    if (fp) {
      char buf[SIZE_BUF];
      int num = 1;
      while (fgets(buf, BUFSIZ, fp)) {
        int len = strlen(buf);
        if (buf[len - 1] != '\n') {
          buf[len + 1] = 0;
          buf[len] = '\n';
        }
        Processing_main_data(opt, buf, opt->files[i], num);
        num++;
      }
      Proccesing_aux_data(opt, opt->files[i]);
      fclose(fp);
    } else if (!opt->s) {
      fprintf(stderr, "s21_grep: %s: No such file or directory", opt->files[i]);
    }
  }
}

void Proccesing_patt(struct options *opt) {
  for (int i = 0; opt->patterns[i]; i++)
    strcat(strcat(opt->pattern, !strlen(opt->pattern) ? "" : "|"),
           !strlen(opt->patterns[i]) ? "." : opt->patterns[i]);
  for (int i = 0; opt->patterns_files[i]; i++) Proccesing_patt_files(opt, i);
}

void Proccesing_patt_files(struct options *opt, int num) {
  char buf[SIZE_BUF];
  FILE *fp = fopen(opt->patterns_files[num], "r");
  if (fp) {
    while (fgets(buf, SIZE_BUF, fp)) {
      char *c = buf + strlen(buf) - 1;
      if (*c == '\n') *c = '\0';
      strcat(strcat(opt->pattern, !strlen(opt->pattern) ? "" : "|"),
             !strlen(buf) ? "." : buf);
    }
  } else {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n",
            opt->patterns_files[num]);
  }
}

void Processing_main_data(struct options *opt, char *line, char *file_name,
                          int num) {
  regex_t regex;
  if (!regcomp(&regex, opt->pattern,
               opt->i_flag ? REG_ICASE + REG_EXTENDED : REG_EXTENDED)) {
    if (regexec(&regex, line, 0, NULL, 0) == opt->v) {
      opt->count_matches++;
      if ((opt->c || opt->l) == 0) {
        if (opt->count_files > 1 && !opt->h) printf("%s:", file_name);
        if (opt->n) printf("%d:", num);
        if (!opt->o)
          fputs(line, stdout);
        else
          Proccesing_o(regex, line, opt);
      }
    }
    regfree(&regex);
  }
}

void Proccesing_aux_data(struct options *opt, char *file_name) {
  if (opt->c) {
    if (opt->l) {
      opt->count_files > 1 ? printf("%s:1\n", file_name) : printf("1\n");
    } else {
      if (opt->count_files > 1) printf("%s:", file_name);
      printf("%d\n", opt->count_matches);
    }
  }
  if (opt->l && opt->count_matches) printf("%s\n", file_name);
}

void Proccesing_o(regex_t regex, char *line, struct options *opt) {
  while (!regexec(&regex, line, 0, NULL, 0)) {
    char buf[SIZE_BUF] = "";
    strcpy(buf, line);
    int left = 0;
    int right = strlen(buf);
    while (!regexec(&regex, buf + left, 0, NULL, 0)) left++;
    left--;
    while (!regexec(&regex, buf + left, 0, NULL, 0)) {
      right--;
      buf[right] = 0;
    }
    buf[right] = line[right];
    right++;
    if (!opt->v) printf("%s\n", buf + left);
    int len = right - left + 1;
    for (int i = 0; i < len; i++) {
      line[left++] = line[right++];
    }
  }
}