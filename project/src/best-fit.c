#include "headers/best-fit.h"

/*
 *  This function allocate the smallest (the best) memory zone fiting the requested size
 */
int BFallocate (Memory memory, int requestedSize)
{
    Block*  tmp     = memory;   // pointer to iterate through the memory
    Block*  best    = NULL;     // pointer to the best block (the block with the smallest size fitting the request)

    printf("Best Fit Strategy\n");
    printf ("Trying to fit %d\n", requestedSize);

    // iteration through the memory
    while (tmp != NULL)
    {
        printf("Bloc %d: %d\t", tmp->address, tmp->length);

        // if the block is free, it fits the request and it is smaller than the best, then it becomes the best
        if (!tmp->allocated)
        {
            printf ("libre!\t");
            if( tmp->length >= requestedSize)
            {
                printf ("Ca rentre!\t");

                if (best == NULL || tmp->length < best->length )
                {
                    printf ("C'est mieux!");
                    best = tmp;
                }
            }
        }
        printf("\n");
        tmp = tmp->next;
    }

    printf("On alloue le bloc a l'adresse %d", best->address);


    // Allocation of the block
    // TODO: handle an impossible Allocation
    allocateBlock(memory, best->address, requestedSize);




    return 0;
}
