#include "headers/memory.h"


// Output the content of the Memory
// TODO: Make this function beautiful
void printMem (Memory memory)
{

    Block* tmp=memory;

    printf ("@ \t - L\t-  n.@\tA\n");
    while (tmp != NULL)
    {
        if (tmp->next != NULL)
        {
            printf("%d \t - %d\t-  %d \t%d \n", tmp->address, tmp->length, tmp->next->address, tmp->allocated);
        }
        else
        {
            printf("%d \t - %d\t-  NULL\t%d \n", tmp->address, tmp->length, tmp->allocated);
        }
        tmp = tmp->next;
    }

    printf("fin de la memoire\n");
    return;
}

// Utility function: create a consistent memory.
Memory createMemory (int nbBlocks, int blockSize)
{
    int i = 0;
    Memory mem = NULL;
    /*
     *for (i=0; i<nbBlocks; ++i)
     *    mem = addEnd(mem, i*blockSize, blockSize, false);
     */

    mem = addEnd(mem, 0,    10, 0);
    mem = addEnd(mem, 1,    4,  0);
    mem = addEnd(mem, 2,    20, 0);
    mem = addEnd(mem, 3,    18, 0);
    mem = addEnd(mem, 4,    7,  0);
    mem = addEnd(mem, 5,    9,  0);
    mem = addEnd(mem, 6,    12, 0);
    mem = addEnd(mem, 7,    15, 0);

    return mem;
}


// free all the blocks of the memory
int freeMemory (Memory memory)
{

    Block* tmp = memory;
    int freedBlocks = 0;

    while (tmp != NULL)
    {
        if (tmp->allocated)
        {
            freeBlock(memory, tmp->address);
            freedBlocks++;
        }
        tmp = tmp->next;
    }

    return freedBlocks;
}

// Add a new Block at the head of the Memory
Memory addHead (Memory memory, int address, int length, bool status)
{
    // creation of a new Block
    Block* newBlock = malloc(sizeof(Block));

    // assignation of the values
    newBlock->address   = address;
    newBlock->length    = length;
    newBlock->usedLength= 0;
    newBlock->allocated = status;
    newBlock->next      = memory;

    // return of the new head of the list
    return newBlock;
}


// Add a new Block at the end of the Memory
Memory addEnd (Memory memory, int address, int length, bool status)
{
    // creation of a new Block
    Block* newBlock = malloc(sizeof(Block));

    // assignation of the values
    newBlock->address   = address;
    newBlock->length    = length;
    newBlock->usedLength= 0;
    newBlock->allocated = status;
    newBlock->next      = NULL; // it is the end of the list so no following Block

    if (memory == NULL)
    {
        // if the list if empty, the new Block is the list
        return newBlock;
    }
    else
    {
        // iteration through the memory to set the new Block as the last element
        Block* tmp=memory;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }

        tmp->next = newBlock;
        return memory;
    }
}

// iterate through the memory and marks the desired block as "allocated"
int allocateBlock (Memory memory, int address, int usedLength)
{

    // iteration through the memory
    Block* tmp = memory;
    while (tmp != NULL && tmp->address != address)
        tmp = tmp->next;

    // if the Block is found mark it as allocated
    if (tmp != NULL && !tmp->allocated)
    {
        if (usedLength < tmp->length)
        {
            tmp->allocated = true;
            tmp->usedLength = usedLength;
            return 0;
        }
        else
        {
            printf("Allocation impossible, le bloc %d ne contient pas assez d espace.\n", address);
            return -1;
        }
    }
    else if (tmp == NULL)
    {
        printf("Allocation impossible, le bloc %d n existe pas\n", address);
        return -1;
    }else if (tmp->allocated)
    {
        printf("Allocation impossible, le bloc %d est deja alloue\n", address);
        return -2;
    }


    // if we get here, there probably is a hole in the matrix
    return -3;
}

// iterate through the memory and marks the desired block as "free"
int freeBlock (Memory memory, int address)
{

    // iteration through the memory
    Block* tmp = memory;
    while (tmp != NULL && tmp->address != address)
        tmp = tmp->next;

    // if the Block is found mark it as free
    if (tmp != NULL && tmp->allocated)
    {
        tmp->allocated = false;
        return 0;
    }
    else if (tmp == NULL)
    {
        printf("Liberation impossible, le bloc %d n existe pas\n", address);
        return -1;
    }else if (!tmp->allocated)
    {
        printf("Liberation impossible, le bloc %d n est pas  alloue\n", address);
        return -2;
    }

    // if we get here, there probably is a hole in the matrix
    return -3;
}
