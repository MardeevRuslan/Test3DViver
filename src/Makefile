PROJECT_NAME = 3DViewer

CC = g++ -std=c++17
LDFLAGS = -Wall -Werror -Wextra 
FLAG_GCOV = -fprofile-arcs -ftest-coverage
ADD_LIBS = -lcheck
FLAG_LINUX = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
BUILD = build
BUILD_DIR = ./build
APP_DIR = ./app
DIST_DIR = ./dist
LEAKS_DIR = ./leaks
MODELS_DIR = ./models
MANUAL = Manual
QMAKE = qmake
QT_INSTALL_PREFIX = $(shell $(QMAKE) -query QT_INSTALL_PREFIX)

OS := $(shell uname -s)

ifeq ($(OS), Linux)
	ADD_LIBS +=`pkg-config --cflags --libs check` -lm -lsubunit
endif

RUN = $(APP_DIR)/$(APP_NAME)
ifeq ($(OS), Darwin)
    RUN = open $(APP_DIR)/$(APP_NAME)
endif

APP_NAME = $(PROJECT_NAME)
ifeq ($(OS), Darwin)
    APP_NAME = $(PROJECT_NAME).app
endif

default: all

all: clean style_fix install

build:
	mkdir -p $(BUILD_DIR)
	cmake -DCMAKE_PREFIX_PATH=$(QT_INSTALL_PREFIX) $(PROJECT_NAME)/CMakeLists.txt -B $(BUILD_DIR)
	make -C $(BUILD_DIR)
	

install: build
	mkdir -p $(APP_DIR)
	cp -r $(BUILD_DIR)/$(APP_NAME) $(APP_DIR)/$(APP_NAME)
	

uninstall:
	rm -rf $(APP_DIR)

rebuild: clean all

run: 
	$(RUN)

dvi:
	mkdir -p $(APP_DIR)
	texi2pdf $(MANUAL).texi
	texi2html  $(MANUAL).texi
	cp -r $(MANUAL).pdf $(APP_DIR)
	cp -r $(MANUAL).html $(APP_DIR)
	rm $(MANUAL).aux $(MANUAL).log $(MANUAL).toc $(MANUAL).pdf $(MANUAL).html

dist:
	mkdir -p $(DIST_DIR)
	tar -cvf $(DIST_DIR)/$(PROJECT_NAME).tar.gz $(PROJECT_NAME) $(LEAKS_DIR) $(MODELS_DIR) ./*.c ./*.h Makefile


./tests/$(PROJECT_NAME)_test.c : ./tests/$(PROJECT_NAME)_test.check
	checkmk ./tests/$(PROJECT_NAME)_test.check > ./tests/$(PROJECT_NAME)_test.c

test : ./tests/$(PROJECT_NAME)_test.c parser_coordinates.c s21_affine.c s21_matrix.c s21_obj.c parser_coordinates.h
	$(CC) $(LDFLAGS) ./tests/$(PROJECT_NAME)_test.c parser_coordinates.c  parser_coordinates.h s21_affine.c s21_matrix.c s21_obj.c -o ./tests/$(PROJECT_NAME)_test $(ADD_LIBS) 
	./tests/$(PROJECT_NAME)_test

gcov_report : ./tests/$(PROJECT_NAME)_test.c parser_coordinates.c s21_affine.c s21_matrix.c s21_obj.c parser_coordinates.h
	$(CC) $(LDFLAGS) ./tests/$(PROJECT_NAME)_test.c parser_coordinates.c  parser_coordinates.h s21_affine.c s21_matrix.c s21_obj.c -o ./tests/$(PROJECT_NAME)_test $(ADD_LIBS)  $(FLAG_GCOV) 
	./tests/$(PROJECT_NAME)_test
	lcov --capture --directory ./ --output-file coverage.info
	genhtml coverage.info --output-directory GCOV_REPORT
	open GCOV_REPORT/index.html

check:
	cppcheck -q  --enable=all --inconclusive --language=c++ --template='{id} {file}:{line} {message}' --suppress=missingIncludeSystem ./*/*.cc ./*/*.h
	
	
style:
	cp ../materials/linters/.clang-format ./
	clang-format -n --style=google ./*/*.cc ./*/*.h
	rm .clang-format

style_fix:
	cp ../materials/linters/.clang-format ./
	clang-format -i --style=google ./*/*.cc ./*/*.h
	rm .clang-format

valgrind: ./leaks/test.c parser_coordinates.c  s21_affine.c s21_matrix.c s21_obj.c
	$(CC) $(LDFLAGS) ./leaks/test.c parser_coordinates.c  s21_affine.c s21_matrix.c s21_obj.c -o ./leaks/$(PROJECT_NAME)_test_val -lm
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=REPORT_VALGRIND.txt ./leaks/$(PROJECT_NAME)_test_val

leaks: ./leaks/test.c parser_coordinates.c  s21_affine.c s21_matrix.c s21_obj.c
	$(CC) $(LDFLAGS) ./leaks/test.c parser_coordinates.c  s21_affine.c s21_matrix.c s21_obj.c -o ./leaks/$(PROJECT_NAME)_test_leaks 
	leaks -atExit -- ./leaks/$(PROJECT_NAME)_test_leaks

clean:
	rm -rf ./build *.o *.a *.exe *.out *.gcov *.gcno *.gcda *.gch *.info ./tests/$(PROJECT_NAME)_test ./tests/$(PROJECT_NAME)_test_leaks ./tests/$(PROJECT_NAME)_test.c  lcover_rep *.stackdump GCOV_REPORT REPORT_VALGRIND.txt *.check
	rm -rf $(APP_DIR) $(DIST_DIR)

min:
	g++ 3DViewer/main.cc 3DViewer/mainwindow.cc 3DViewer/model.cc 3DViewer/parser.cc 3DViewer/s21_matrix_oop.cc 3DViewer/s21_matrix_constructor.cc 3DViewer/s21_matrix_operator.cc
	./a.out
	

.PHONY: all clean test gcov_report default clang_format valgrind leaks build install uninstall rebuild run dvi dist 
