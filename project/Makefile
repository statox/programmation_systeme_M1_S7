
CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=src/best-fit.c src/first-fit.c src/main.c src/memory.c src/worst-fit.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=executable

all: $(SOURCES) $(EXECUTABLE)
	./executable

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
