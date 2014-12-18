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
        printf("Bloc %d: ", tmp->address);

        // if one Block is not allocated its size is available
        if (!tmp->allocated)
        {
            available           += tmp->length;
            blocksAdd[nbBlock]  = tmp->address;
            nbBlock++;
            printf ("libre!\n");
            // if we have enough space we stop the loop
            if (available >= requestedSize)
            {
                printf("On a assez de blocs\n");
                stop = true;
            }
            tmp = tmp -> next;
        }
        else    // if the block is allocated, we search for the next free Block
        {
            available   = 0;
            nbBlock     = 0;
            tmp         = tmp->next;
            firstBlock  = tmp;

            printf ("Occupe!\n");
        }
    }

    printf ("La zone commence au bloc %d\n", firstBlock->address);
    printf ("Elle contient %d blocs\n", nbBlock);
    printf ("Pour une taille de %d\n", available);
    printf ("Les blocs contenus sont les suivants:\n");
    
    int i = 0;
    for (i=0; i<nbBlock; ++i)
    {
        printf("\t%d\n", blocksAdd[i]);
    }


    // Allocation of the blocks
    // TODO: handle an impossible Allocation
    for (i=0; i<nbBlock; ++i)
    {
        allocateBlock(memory, blocksAdd[i]);
    }


    return 0;
}
