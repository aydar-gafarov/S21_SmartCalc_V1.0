CC = gcc 
CFALGS = -Wall -Werror -Wextra -std=c11
STATLIB = s21_calc.a
OS := $(shell uname)

ifeq ($(OS),Linux)
	FLAGS = -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
	OPEN = xdg-open
else
	FLAGS = -lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
	OPEN = open
endif

all: clean install

install:
	mkdir build
	cd ./build/ && qmake ../ && make

uninstall: clean

dvi:
	open read_dvi/openme.md
	
dist: 
	mkdir dist/
	mkdir dist/src
	mkdir dist/src/images
	cp Makefile *.c *.h *.cpp *.ui *.pro *.user dist/src/
	cp images/* dist/src/images
	tar cvzf $(HOME)/Desktop/dist.tgz dist/
	rm -rf dist*

$(STATLIB): 
	$(CC) $(CFALGS) -c s21_*.c
	ar -rcs $(STATLIB) s21_*.o

test: clean $(STATLIB)
	$(CC) $(CFLAGS) tests_calc/*.c $(STATLIB) $(FLAGS) -o test
	./test

gcov_report:
	$(CC) $(CFLAGS) tests_calc/*.c s21*.c $(FLAGS) -o test
	./test
	lcov -t "./test" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html
	rm -rf *.gcno *gcda *.gcov

clang: 
	clang-format -n *.c *.h *.cpp
	clang-format -i *.c *.h *.cpp

clean: 
	rm -rf *.o $(STATLIB) test *.gcno *gcda *.gcov gcov report report.info *.dSYM ./build* ./dist*