#include "headers/first-fit.h"

/*
 *  This function allocate the first memory zone fiting the requested size
 */
int FFallocate (Memory memory, int requestedSize)
{

    Block*  tmp         = memory;   // pointer to iterate through the memory
    Block*  firstBlock  = memory;   // pointer on the first block of the currently free zone
    int     nbBlock     = 0;        // number of blocks in the currently free zone
    bool    stop        = false;    // condition of the while loop
    int     available   = 0;        // available size represented by the currently free zone
    int     blocksAdd[100];         // array of the addresses of the blocks in the zone

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

    // if we didnt found any fitting block
    if (tmp == NULL)
    {
        printf("Il n'existe pas de bloc capable de contenir cette requete\n");
        return -1;
    }
    printf("On alloue le bloc %d\n", tmp->address); 


    // Allocation of the block
    allocateBlock(memory, tmp->address);


    return 0;
}
