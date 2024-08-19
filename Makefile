CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Werror -Wextra
SANFLAG=#-fsanitize=address -g
COVFLAGS=-fprofile-arcs -ftest-coverage

C_FILES = $(wildcard s21_*.c)
O_FILES = $(subst .c,.o, $(C_FILES))
O_GCOVFILES = $(addsuffix .gcov, $(O_FILES))

#Директория для тестов
TESTDIR=./tests/
C_TESTFILES=$(wildcard $(TESTDIR)*.c)
O_TESTFILES = $(subst .c,.o.test, $(C_TESTFILES))
OUT_TEST=$(TESTDIR)test.out

# Флаги для линукса отдельно
OS=$(shell uname)
ifeq ($(OS),Darwin)
	CHECKFLAGS=-lcheck -lm
else
	CHECKFLAGS=-lcheck -lsubunit -lm -lrt -lpthread
endif

all: s21_decimal.a

s21_decimal.a: $(O_FILES)
	ar rcs s21_decimal.a $^
	ranlib s21_decimal.a

test: $(O_GCOVFILES) $(O_TESTFILES)
	$(CC) $(CFLAGS) $(SANFLAG) $(COVFLAGS) $(O_TESTFILES) $(addprefix $(TESTDIR), $(O_GCOVFILES)) -o $(OUT_TEST) $(CHECKFLAGS)
	$(OUT_TEST)

gcov_report:
	(cd $(TESTDIR) && gcov *.o.gcov)
	@echo ""
	lcov -t "test" -o $(TESTDIR)report.info -c -d $(TESTDIR)
	genhtml -o $(TESTDIR)report $(TESTDIR)report.info
	open ./tests/report/index.html

# Компилируем объектные файлы функций библиотеки
%.o: %.c
	$(CC) $(CFLAGS) -c $(SANFLAG) $< -o $@

# Компилируем объектные файлы функций библиотеки с профилир/покрытием
%.o.gcov: %.c
	$(CC) $(CFLAGS) -c $(SANFLAG) $(COVFLAGS) $< -o $(TESTDIR)$@

# Компилируем объектные файлы тестов
%.o.test: %.c
	$(CC) $(CFLAGS) -c $(SANFLAG) $< -o $@

clang:
	clang-format -i *.c *.h $(TESTDIR)*.c $(TESTDIR)*.h

clean:
	rm -rf *.o* \
	*.a \
	*.gc* \
	$(TESTDIR)*.o* \
	$(TESTDIR)*.gc* \
	$(TESTDIR)*report*

# Компилируем объектный файл тестов
create_o_test:
	checkmk clean_mode=1 $(CHECK_FILE) > $(C_TEST)
	$(CC) $(CFLAGS) -c $(SANFLAG) $(COVFLAGS) $(C_TEST) -o $(O_TEST)

rebuild: clean all

docker:
	docker build -t darkandstormy:v1 .
	docker run --rm -it --name decimaldarkandstormy darkandstormy:v1

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leaks_log.txt $(OUT_TEST)
	vim leaks_log.txt
	
                              
	  
