all: s21_cat

s21_cat: s21_cat.o
	gcc -Wall -Werror -Wextra s21_cat.c -o s21_cat

cat_test: test.sh
	bash test.sh

s21_cat.o: s21_cat.c
	gcc -Wall -Werror -Wextra -c s21_cat.c

clean:
	rm -rf *.o
	rm -rf *s21_cat
	rm -rf test			