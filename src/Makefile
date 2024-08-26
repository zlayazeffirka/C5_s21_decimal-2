TARGET = s21_decimal
CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11 
SRC = s21_decimal.c
TEST = $(wildcard tests/*.c)
LIBRARY = s21_decimal.a
S21_DECIMAL=-L. s21_decimal.a
#DEBUG =-g
SRC = $(wildcard  _*.c s21*.c) 
OBJ = $(patsubst %.c, %.o, $(SRC))
CHECK:=$(shell pkg-config --cflags --libs check)

ifeq (${OS}, Linux)
      TEST_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
else
      TEST_FLAGS = -lcheck -lm
endif



all: $(LIBRARY)

$(LIBRARY): $(SRC)
	$(CC) $(FLAGS) -c $(SRC)
	ar rc $(LIBRARY) $(OBJ)
	ranlib $(LIBRARY) 
	rm -f $(OBJ)

$(TARGET) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(TARGET)


%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

	
test : $(LIBRARY)
	$(CC) $(FLAGS) --coverage $(TEST) $(TEST_FLAGS) $(LIBRARY) -o test -lsubunit 
	./test

gcov_report: clean $(LIBRARY)
	$(CC) --coverage $(FLAGS) $(TEST_FLAGS) $(TEST) s21*.c -o test $(CHECK) $(S21_DECIMAL) -lsubunit
	./test
#	$(CC) $(FLAGS) --coverage $(TEST) $(S21_DECIMAL) s21*.c  -o test $(TEST_FLAGS) 
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf *.o *.a *.gcno *.gcda test test.info *.out report
	

style:
	clang-format -style=google -i tests/*.c
	clang-format -style=google -i *.c
	clang-format -style=google -i *.h
	clang-format -style=google -n tests/*.c
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h

	
cpp:
	cppcheck --enable=all --suppress=unusedFunction --suppress=missingIncludeSystem  *.c *.h
