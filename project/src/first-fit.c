#include "headers/first-fit.h"

/*
 *  This function allocate the first memory zone fiting the requested size
 */
int FFallocate (Memory memory, int requestedSize)
{

    Block*  tmp         = memory;   // pointer to iterate through the memory
    bool    stop        = false;    // condition of the while loop

    printf("First Fit Strategy\n");
    // iterate through the memory
    while(!stop && tmp != NULL)
    {
        printf("Bloc %d: %d ", tmp->address, tmp->length);

        // if one Block is not allocated its size is available
        if (!tmp->allocated)
        {
            printf ("libre\n");

            // if we have enough space we stop the loop
            if (tmp->length >= requestedSize)
            {
                printf("\tCa rentre!\n");
                stop = true;
            }
            else    // else we look for the next block
            {
                tmp = tmp->next;
            }
        }
        else    // if the block is allocated, we search for the next free Block
        {
                printf ("Occupe!\n");
                tmp = tmp->next;
        }
    }

    // Allocation of the block
    // if we didnt found any fitting block
    if (tmp != NULL)
    {
        printf("On alloue le bloc %d\n", tmp->address);
        allocateBlock(memory, tmp->address, requestedSize);
    } else {
        return useSomeDefragmentationAlgorithm(&memory, requestedSize);
    }


    return 0;
}
