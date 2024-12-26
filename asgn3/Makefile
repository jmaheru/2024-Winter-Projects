CC = clang
CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic -g

.PHONY: all clean format test
all: xd test

xd: xd.o
	$(CC) $(CFLAGS) $< -o xd

xd.o: xd.c 
	$(CC) $(CFLAGS) -c xd.c

format:
	clang-format -i -style=file *.[ch]

clean:
	rm -f xd *.o

test: tests
        # bash runner.sh
