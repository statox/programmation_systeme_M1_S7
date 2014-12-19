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
void printMem2 (Memory memory);

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

// iterate through the memory and free a part of the desired block
int freeBlockLength (Memory memory, int address, int lengthFree);

// free all the blocks of the memory
int freeMemory (Memory memory);

// delete unused space in allocated block
// then use this space to create 2 blocks of requestedSize size and remaining size
Memory defrag (Memory memory, int requestedSize);
Memory defrag2 (Memory memory, int requestedSize);

bool isDefragUseful (Memory memory, int requestedSize);
bool isDefrag2Useful (Memory memory, int requestedSize);
#endif /* MEMORY_H */
