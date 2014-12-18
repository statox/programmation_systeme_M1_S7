#include "headers/worst-fit.h"


/*
 *  This function allocate the largest block fitting the requested size
 */
int WFallocate (Memory memory, int requestedSize)
{

    Block*  tmp     = memory;   // pointer to iterate through the memory
    Block*  worst    = NULL;     // pointer to the best block (the block with the smallest size fitting the request)

    printf("Worst Fit Strategy\n");
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

                if (worst == NULL || tmp->length > worst->length )
                {
                    printf ("C'est pire! (donc c'est mieux)");
                    worst = tmp;
                }
            }
        }
        printf("\n");
        tmp = tmp->next;
    }

    // if we didnt found any fitting block
    if (tmp == NULL)
    {
        printf("Il n'existe pas de bloc capable de contenir cette requete\n");
        return -1;
    }

    printf("On alloue le bloc a l'adresse %d", worst->address);


    // Allocation of the block
    allocateBlock(memory, worst->address);


    return 0;
}
