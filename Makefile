CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11

OS = $(shell uname)

ifeq ($(OS),Linux)
    det_OS = -lcheck  -lm -lrt -lpthread -lsubunit
else
    det_OS = -lcheck -lm -lpthread
endif

all: clean s21_matrix.a test gcov_report

test:
	$(CC) $(FLAGS) --coverage s21*.c tests.c -o test $(det_OS)

s21_matrix.o:  s21*
	$(CC) $(CFLAGS) s21*.c  -c 

s21_matrix.a : s21_matrix.o
	ar rcs s21_matrix.a *.o
	ranlib s21_matrix.a

gcov_report: test
	./test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html

check_style:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	rm -rf .clang-format

correct_style:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h
	rm -rf .clang-format

clean:
	rm -rf report *.gc* *.o *.info *.a test.dSYM test 