
CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=src/best-fit.c src/first-fit.c src/main.c src/memory.c src/worst-fit.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=executable

all: $(SOURCES) $(EXECUTABLE)
	./executable 1 12 1 10 1 9 assert 10 0 12 9 0 0 0 0 > /dev/null
	# ./executable 1 12 1 10 1 9 1 30
	# ./executable 1 12 1 10 1 9 1 30 assert 10 12 9 30 0 # for defrag2SuperDestructive
	./executable 1 12 1 10 1 9 1 30 assert 10 12 9 0 0 30 0 > /dev/null

# [order] assert [expected usage in blocks]

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
