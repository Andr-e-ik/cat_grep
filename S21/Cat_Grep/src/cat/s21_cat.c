#include <stdio.h>
#include <string.h>

struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int count_lines;
  int count;
};

int StrParcer(int argc, char *argv[], struct flags *flag);
void Print(int argc, char *argv[], struct flags flag, int count);
void CatPrint(FILE *fp, struct flags *flag);
void CatProcessing(int *c, struct flags *flag, int *prev, FILE *fp);
void NoPrinted(int *c, struct flags *flag);
void CatNumbLines(int prev, struct flags *flag);

int main(int argc, char *argv[]) {
  struct flags flag = {0};
  if (argc == 1) {
    CatPrint(stdin, &flag);
  } else {
    int count = StrParcer(argc, argv, &flag);
    if (count != -1) {
      Print(argc, argv, flag, count);
    } else {
      printf("no work argument");
    }
  }
  return 0;
}

int StrParcer(int argc, char *argv[], struct flags *flag) {
  int count = 0;
  char error;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '-' && count != -1) {
      for (size_t j = 1; j < strlen(argv[i]); j++) {
        if (count == -1) {
          break;
        } else {
          switch (argv[i][j]) {
            case 'b':
              flag->b = 1;
              count++;
              break;
            case 'e':
              flag->e = 1;
              flag->v = 1;
              count++;
              break;
            case 'n':
              flag->n = 1;
              count++;
              break;
            case 's':
              flag->s = 1;
              count++;
              break;
            case 't':
              flag->t = 1;
              flag->v = 1;
              count++;
              break;
            case 'E':
              flag->e = 1;
              count++;
              break;
            case 'T':
              flag->t = 1;
              count++;
              break;
            default:
              error = argv[i][j];
              printf("no such command exists %c\n", error);
              count = -1;
              break;
          }
        }
      }
    }
    if (argv[i][0] == '-' && argv[i][1] == '-') {
      if (strcmp(argv[i] + 2, "number-nonblank") == 0) {
        flag->b = 1;
        count++;
      } else if (strcmp(argv[i] + 2, "number") == 0) {
        flag->n = 1;
        count++;
      } else if (strcmp(argv[i] + 2, "squeeze-blank") == 0) {
        flag->s = 1;
        count++;
      } else {
        error = argv[i][1];
        printf("no such command exists %c\n", error);
        count = -1;
      }
    }
  }
  return count;
}

void CatPrint(FILE *fp, struct flags *flag) {
  int c;
  int prev = '\n';
  if (flag) {
    flag->count_lines = 0;
    flag->count = 1;
  }
  while ((c = fgetc(fp)) != EOF) {
    if (flag) {
      CatProcessing(&c, flag, &prev, fp);
    }
    if ((c != EOF)) {
      fputc(c, stdout);
    }
    prev = c;
  }
}

void Print(int argc, char *argv[], struct flags flag, int count) {
  int i = 1;
  if (count > 0) {
    i = 2;
  }
  for (; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp) {
      CatPrint(fp, &flag);
      fclose(fp);
    } else {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[1]);
    }
  }
}

void CatProcessing(int *c, struct flags *flag, int *prev, FILE *fp) {
  if (*prev == '\n' && *c == '\n') {
    flag->count_lines++;
  } else {
    flag->count_lines = 0;
  }
  if (flag->s && flag->count_lines > 1) {
    while (*c == '\n') *c = fgetc(fp);
  }
  if (*c != EOF) {
    CatNumbLines(*prev, flag);
    NoPrinted(c, flag);
  }
}
void CatNumbLines(int prev, struct flags *flag) {
  if (prev == '\n' && (flag->n || flag->b)) {
    if (!(flag->b && flag->count_lines > 0)) {
      printf("%6d\t", flag->count);
      flag->count++;
    }
  }
}

void NoPrinted(int *c, struct flags *flag) {
  if (*c == '\n') {
    if (flag->e) {
      printf("$");
    }
  } else if (*c == '\t') {
    if (flag->t) {
      printf("^");
      *c = 'I';
    }
  } else if (flag->v) {
    if (*c <= 31) {
      printf("^");
      *c += 64;
    } else if (*c == 127) {
      printf("^");
      *c = '?';
    } else if (*c >= 128 && *c < 128 + 32) {
      printf("M-^");
      *c -= 64;
    }
  }
}