CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = -lm


all: calc test


calc: calc.o stack.o mathlib.o operators.o
	$(CC) $^ $(LFLAGS) -o $@

test: tests.o mathlib.o stack.o operators.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf calc test *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format
