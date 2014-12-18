/*
 *  Memory representation by    Matthieu de la Roche Saint Andre
 *                              Adrien Fabre
 *
 *  This programs simulate the allocation memory of an OS following different algorithms
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "headers/structures.h"


int main (int argc, char **argv)
{
    Memory memory = NULL;

    memory = createMemory(9, 3);
    printMem(memory);

    printf("allocate Block 6\n");
    allocateBlock(memory, 6);
    printMem(memory);

    printf("allocate Block 15\n");
    allocateBlock(memory, 15);
    printMem(memory);

    printf("allocate Block 15\n");
    allocateBlock(memory, 15);
    printMem(memory);

    printf("allocate Block 2\n");
    allocateBlock(memory, 2);
    printMem(memory);

    printf("allocate Block 55\n");
    allocateBlock(memory, 55);
    printMem(memory);


    printf("free Block 6\n");
    freeBlock(memory, 6);
    printMem(memory);

    printf("free Block 15\n");
    freeBlock(memory, 15);
    printMem(memory);

    printf("free Block 15\n");
    freeBlock(memory, 15);
    printMem(memory);

    printf("free Block 2\n");
    freeBlock(memory, 2);
    printMem(memory);

    printf("free Block 55\n");
    freeBlock(memory, 55);
    printMem(memory);


    return 0;
}
