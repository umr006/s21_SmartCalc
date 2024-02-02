CC = gcc
CFLAGC =  -Wall -Werror -Wextra  -std=c11 
SOURCES = s21.c test.c
OBJECTS = s21.o
OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -lm -pthread -lrt -lsubunit
	OPEN_REPORT = xdg-open
else
	CHECK_FLAGS = -lcheck
	OPEN_REPORT = open
endif

all:  build static tests  

build:
	$(CC) $(CFLAGC) -c $(SOURCES)

static: build
	ar rc s21.a $(OBJECTS)
	ranlib s21.a

tests:
	$(CC) $(CFLAGC) $(CHECK_FLAGS)  test.c s21.a -o test
	./test

gcov_report:
	gcc $(CFLAGC) $(CHECK_FLAGS) --coverage *.c -o gcov_report
	./gcov_report
	lcov -t "./gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	$(OPEN_REPORT) ./report/index.html

install:
	make clean
	mkdir build
	cd calc && qmake && make && make clean && rm Makefile && cd ../ && mv calc/creditv3.app build

uninstall:
	rm -rf build*

dvi:
	$(OPEN_REPORT) dvi.txt

dist:
	rm -rf Archive_calcv3/
	mkdir Archive_calcv3/
	mkdir Archive_calcv3/src
	mv ./build/creditv3.app Archive_calcv3/src/
	tar cvzf Archive_calcv3.tgz Archive_calcv3/
	rm -rf Archive_calcv3/

clean:
	rm -rf *.{a,o,dSYM,out}
	rm -rf gcov_report
	rm -rf report
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf Archive_SmartCalc_v1.0 
	rm -rf *tgz
	rm -rf build

rebuild: clean all

check:
ifeq ($(OS), Linux)
	valgrind ./test --leak-check=full
else
	leaks --atExit -- ./test
endif