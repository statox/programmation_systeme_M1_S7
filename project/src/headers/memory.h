/*
 *  The functions in this file are used to interact with the Memory structure
 *
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Output the content of the Memory
void printMem (Memory memory);

// Add a new Block at the head of the Memory
Memory addHead (Memory memory, int address, int length, bool status);

// Add a new Block at the end of the Memory
Memory addEnd (Memory memory, int address, int length, bool status);

// Utility function: create a consistent memory.
Memory createMemory (int nbBlocks, int blockSize);

// iterate through the memory and marks the desired block to "allocated"
int allocateBlock (Memory memory, int address, int requestedSize);

// iterate through the memory and marks the desired block as "free"
int freeBlock (Memory memory, int address);

// free all the blocks of the memory
int freeMemory (Memory memory);

#endif /* MEMORY_H */
