PROJECT_NAME = 3DViewer
GCC =  g++ -std=c++17
LDFLAGS = -Wall -Werror -Wextra
SOURCE = 3DViewer/main.cc 3DViewer/mainwindow.cc 3DViewer/model.cc 3DViewer/parser.cc 3DViewer/myglwidget.cc
TEST = s21_test.cc
GCOV = --coverage
BUILD = build
BUILD_DIR = ./build
APP_DIR = ./app
DIST_DIR = ./dist
QMAKE = qmake
QT_INSTALL_PREFIX = $(shell $(QMAKE) -query QT_INSTALL_PREFIX)
MANUAL = Manual

OS = $(shell uname)

ifeq ($(OS), Darwin)
LIBFLAGS = -lm -lgtest -lstdc++
LEAKS = leaks --atExit -- test -fsanitize=address
LCOV = lcov -t "test" -c -d  ./ --no-external --output-file ./coverage.info --ignore-errors mismatch
else
LIBFLAGS = -lstdc++ `pkg-config --cflags --libs gtest`
LEAKS = CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all ./test
LCOV = lcov -t "test" -c -d  ./ --no-external --output-file ./coverage.info 
endif


RUN = $(APP_DIR)/$(APP_NAME)
ifeq ($(OS), Darwin)
    RUN = open $(APP_DIR)/$(APP_NAME)
endif

APP_NAME = 3DViewer
ifeq ($(OS), Darwin)
    APP_NAME = 3DViewer.app
endif

default: all

all: install


build:
	mkdir -p $(BUILD_DIR)
	cmake -DCMAKE_PREFIX_PATH=$(QT_INSTALL_PREFIX) 3DViewer/CMakeLists.txt -B $(BUILD_DIR)
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
	texi2dvi $(MANUAL).texi -c -o $(APP_DIR)/manual.dvi

pdf:
	mkdir -p $(APP_DIR)
	texi2pdf $(MANUAL).texi -o $(APP_DIR)/manual.pdf


dist:
	mkdir -p $(DIST_DIR)
	tar -cvf $(DIST_DIR)/Calc.tar.gz s21_SmartCalc


test: $(TEST)
	rm -rf test
	$(GCC) $(LDFLAGS)  $(TEST) 3DViewer/parser.cc $(LIBFLAGS) -o test 
	./test



gcov_report:
	$(GCC)  -I $(GCOV) $(TEST) $(SOURCE)  $(LIBFLAGS) -o test
	./test
	$(LCOV) 
	genhtml ./coverage.info --output-directory ./report/


check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SOURCE) *.h */*.h  */*.cc
	cppcheck -q --enable=all --inconclusive --language=c++ --template='{id} {file}:{line} {message}' --suppress=missingIncludeSystem *.h */*.h  */*.cc
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n   */*.h *.cc */*.cc
	rm .clang-format
	
leaks:
	$(GCC)  $(LDFLAGS) $(SOURCE) $(TEST) $(LIBFLAGS) -o test 
	$(LEAKS)

style_fix:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.cc   */*.h */*.cc
	rm .clang-format

clean:
	rm -rf *.o *.a *.so *.out *.dSYM test *.txt report *.info *.gcda *.gcno *.gch .clang-format
	rm -rf ./build *.o *.a *.exe *.out *.gcov *.gcno *.gcda *.gch *.info ./tests/$(PROJECT_NAME)_test ./tests/$(PROJECT_NAME)_test_leaks ./tests/$(PROJECT_NAME)_test.c  lcover_rep *.stackdump GCOV_REPORT REPORT_VALGRIND.txt *.check
	rm -rf $(APP_DIR) $(DIST_DIR)
	rm -rf ./*.log ./*.aux ./*.bbl ./*.blg ./*.out ./*.toc
 
git:
	git add .
	git commit -m "100 %"
	git push

.PHONY:  all test check gcov_report style_fix leaks clean 

	
.PHONY: all clean test gcov_report default clang_format valgrind leaks build install uninstall rebuild run dvi dist 


min:
	g++ 3DViewer/main.cc 3DViewer/mainwindow.cc 3DViewer/model.cc 3DViewer/parser.cc 3DViewer/s21_matrix_oop.cc 3DViewer/s21_matrix_constructor.cc 3DViewer/s21_matrix_operator.cc
	./a.out
	

.PHONY: all clean test gcov_report default clang_format valgrind leaks build install uninstall rebuild run dvi dist 
