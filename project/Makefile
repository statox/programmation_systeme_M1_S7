
CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=src/best-fit.c src/first-fit.c src/main.c src/memory.c src/worst-fit.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=executable

all: $(SOURCES) $(EXECUTABLE)
	## Tests :
	## ./executable [methodeOfAllocation requestedSize] [assert [usedLengthInEachFinalMemoryBlock]]
	## test trivial memory allocation using first-fit algorithm
	./executable 1 12 1 10 1 9 assert 10 0 12 9 0 0 0 0 > /dev/null
	# test big memory allocation using first-fit algorithm, expecting it to defrag memory at some point
	./executable 1 12 1 10 1 9 1 30 assert 10 12 9 0 0 30 0 > /dev/null
	# test trivial memory allocation using best-fit algorithm
	./executable 2 12 2 10 2 9 assert 10 0 0 0 0 9 12 0 > /dev/null
	# test big memory allocation using best-fit algorithm, expecting it to defrag memory at some point
	./executable 2 12 2 10 2 9 2 30 assert 10 0 9 12 0 30 0 > /dev/null
	## test big memory allocation using best-fit algorithm, expecting it to defrag memory at some point
	./executable 2 12 2 10 2 9 2 30 assert 10 0 9 12 0 30 0 > /dev/null
	## test trivial memory allocation using worst-fit algorithm
	./executable 3 12 3 10 3 9 3 30 assert 12 10 0 0 0 9 30 > /dev/null
	## test big memory allocation using worst-fit algorithm, expecting it to defrag memory at some point
	./executable 3 12 3 10 3 9 3 30 assert 12 10 0 0 0 9 30 > /dev/null

# [order] assert [expected usage in blocks]

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


# ./executable 1 12 1 10 1 9 1 30
# ./executable 1 12 1 10 1 9 1 30 assert 10 12 9 30 0 # for defrag2SuperDestructive
