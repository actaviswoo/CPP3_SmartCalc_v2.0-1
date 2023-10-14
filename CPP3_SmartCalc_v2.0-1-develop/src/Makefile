all: clean build test

.PHONY: static
static:
	ar rc smartcalcV2.a model.o controller.o
	ranlib smartcalcV2.a

.PHONY: qmake
qmake:
	mkdir -p build && cd build && qmake .. 

.PHONY: build
build: qmake
	cd build && make

.PHONY: tests
tests: clean
	g++ ./Test/test.cc ./Controller/calculatorcontroller.cc ./Controller/creditcontroller.cc ./Controller/depositcontroller.cc ./Model/calculatormodel.cc ./Model/creditmodel.cc ./Model/depositmodel.cc -lstdc++ -lgtest -std=c++17 -Wall -Werror -Wextra -pedantic -o tests
	./tests

.PHONY: install
install: build
	mkdir -p $(HOME)/Desktop/Argoniaz/
	cp -rf ./build/smartcalcV2.app $(HOME)/Desktop/Argoniaz/
	make clean
	open $(HOME)/Desktop/Argoniaz/smartcalcV2.app

.PHONY: clean
clean:
	rm -rf build ./*.o ./*.a ./a.out ./*.tar ./*.gcno ./*.gcda ./gcov_report *.info ./*.info tests

.PHONY: uninstall
uninstall:
	rm -rf build*
	rm -rf $(HOME)/Desktop/Argoniaz

.PHONY: dist
dist: clean
	mkdir -p smartcalcV2/
	mkdir -p smartcalcV2/src
	cp -r Makefile Controller Info Model Test View Resources *.pro *.cpp smartcalcV2/src/
	tar -cvzf smartcalcV2.tar.gz smartcalcV2
	rm -rf smartcalcV2

.PHONY: dvi
dvi:
	open ./Info/info.html
	# pdflatex ./Info/info.html

.PHONY: style
style:
	cp ../materials/linters/.clang-format ./
	clang-format -i */*.cc */*.h
	clang-format -n */*.cc */*.h
	rm .clang-format

.PHONY: leaks
leaks: tests
	leaks -atExit -- ./tests

.PHONY: start
start:
	open $(HOME)/Desktop/Argoniaz/smartcalcV2.app