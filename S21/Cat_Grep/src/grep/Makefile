all: s21_grep

s21_grep: s21_grep.o
	gcc -Wall -Werror -Wextra s21_grep.c -o s21_grep

test: test.sh
	bash test.sh

s21_grep.o: s21_grep.c
	gcc -Wall -Werror -Wextra -c s21_grep.c

clean:
	rm -rf *.o
	rm -rf s21_grep
	rm -rf test			