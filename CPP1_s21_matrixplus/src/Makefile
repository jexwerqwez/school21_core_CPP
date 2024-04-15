CC = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17
SOURCE = $(wildcard s21_*.cc)
HEADERS = $(wildcard s21_*.h)
TESTS = $(wildcard test_*)
OBJECTS = $(patsubst %.cc,%.o, ${SOURCE})
ADD_LIB = -lgtest

_UNAME_ := $(shell uname -s)

ifeq ($(_UNAME_), Linux)
	OPEN_CMD = xdg-open
	BREW = .
	BROWSER_APP = firefox 
endif

ifeq ($(_UNAME_), Darwin) # MacOS
	OPEN_CMD = open
	BREW = ${HOME}/homebrew
	BROWSER_APP = /Applications/Google\ Chrome.app
endif

PATH := $(PATH):$(BREW)/bin
GCOV = --coverage
PROJECT_NAME := s21_matrix_oop

all: clean style ${PROJECT_NAME}.a gcov_report

$(PROJECT_NAME).a: ${SOURCE} ${HEADERS}
	$(info                                         )
	$(info ----------------------------------------)
	$(info Build a static library 's21_matrix_oop.a'  )
	$(info ----------------------------------------)
	$(CC) -c $(CPPFLAGS) ${SOURCE}
	ar rc $@ ${OBJECTS}
	ranlib $@	

test: $(TESTS) ${PROJECT_NAME}.a
	$(info                                         )
	$(info ----------------------------------------)
	$(info Build tests                             )
	$(info ----------------------------------------)
	$(CC) $^ $(ADD_LIB) -o $@  
	./$@

gcov_report: clean lcov ${SOURCE} ${TESTS} 
	$(info                                         )
	$(info ----------------------------------------)
	$(info Create tests coverage report            )
	$(info ----------------------------------------)
	mkdir report
	$(CC) -c $(CPPFLAGS) $(ADD_LIB) $(GCOV) ${SOURCE} 
	$(CC) -o $@ $(GCOV) $(OBJECTS) $(TESTS) $(ADD_LIB)
	./$@
	lcov -t $@ -o $@.info -c -d . --no-external
	genhtml -o report/ $@.info

ifeq ($(_UNAME_), Darwin) # MacOS
	open $(BROWSER_APP)./ report/index.html
else
	$(BROWSER_APP)./ report/index.html
endif

lcov:
ifeq ("", "$(shell PATH=$(PATH) which lcov)")
	$(error Need to install lcov)
endif

style:
	$(info                                         )
	$(info ----------------------------------------)
	$(info Check for code style and formatting     )
	$(info ----------------------------------------)
	clang-format -style=Google -i *.cc *.h

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/
