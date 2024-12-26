CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = 
Test1 = brtest
Test2 = bwtest
Test3 = nodetest
Test4 = pqtest
EXEC1 = huff
EXEC2 = dehuff
HEADERS = bitreader.h bitwriter.h node.h pq.h

all: $(Test1) $(Test2) $(Test3) $(Test4) $(EXEC1) $(EXEC2)

$(Test1): $(Test1).o bitreader.o bitwriter.o
	$(CC) $^ $(LFLAGS) -o $@ $(LDLIBS)

$(Test2): $(Test2).o bitreader.o bitwriter.o 
	$(CC) $^ $(LFLAGS) -o $@ $(LDLIBS)

$(Test3): $(Test3).o node.o 
	$(CC) $^ $(LFLAGS) -o $@ $(LDLIBS)

$(Test4): $(Test4).o node.o pq.o
	$(CC) $^ $(LFLAGS) -o $@ $(LDLIBS)

$(EXEC1): $(EXEC1).o bitreader.o bitwriter.o node.o pq.o
	$(CC) $^ $(LFLAGS) -o $@ $(LDLIBS)

$(EXEC2): $(EXEC2).o bitreader.o bitwriter.o node.o pq.o
	$(CC) $^ $(LFLAGS) -o $@ $(LDLIBS)

clean:
	rm -rf $(Test1) $(Test2) $(Test3) $(Test4) $(EXEC1) $(EXEC2) *.o *.gch

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format

