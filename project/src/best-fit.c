#include "headers/best-fit.c"

/*
 *  This function allocate the smallest (the best) memory zone fiting the requested size
 */
int BFallocate (Memory memory, int requestedSize)
{
    Block*  tmp          = memory;   // pointer to iterate through the memory
    Block*  cFirstBlock  = memory;  // pointer on the first block of the currently free zone
    Block*  bFirstBlock  = memory;  // pointer on the first block of the best free zone
    int     cAvailable   = 0;       // available size represented by the currently free zone
    int     bAvailable   = 0;       // available size represented by the best free zone
    int     blocksAdd[100];        // array of the addresses of the blocks in the zone
    int     nbBlock      = 0;       // number of blocks in the zone

    printf("Best Fit Strategy\n");

    // initialization of the size of the smallest zone to a very big value
    bAvailable = INT_MAX;
   
    // iterate through the memory looking for the smallest free area greater than (available)
    while(tmp != NULL)
    {
        printf("Bloc %d: ", tmp->address);
        cFirstBlock = tmp;
        cAvailable  = 0;
        // if one Block is not allocated its size is available
        while (!tmp->allocated && tmp->next != NULL)
        {   
            cAvailable += tmp->length;
            tmp = tmp -> next;
        }
        if (cAvailable < bAvailable)
        {   
            printf ("nouvelle meilleure zone au bloc %d\n", cFirstBlock->address);
            bFirstBlock = cFirstBlock;
            bAvailable  = cAvailable;
        }
        tmp = tmp->next;
    }

    // calculation of the caracteristics of the zone
    tmp = bFirstBlock;
    int nbBlocks = 0;
    while (!tmp->allocated && tmp->next!=NULL)
    {
        printf("bloc %d\n", tmp->address);
        blocksAdd[nbBlocks] = tmp->address;
        
        printf("%d\n", blocksAdd[nbBlocks]);
        nbBlocks++;
        
        tmp = tmp -> next;
    }
    

    printf ("La zone commence au bloc %d\n", bFirstBlock->address);
    printf ("Elle contient %d blocs\n", nbBlocks);
    printf ("Pour une taille de %d\n", bAvailable);
    printf ("Les blocs contenus sont les suivants:\n");
     
    
    int i = 0;
    for (i=0; i<nbBlocks; ++i)
    {
        printf("\t%d\n", blocksAdd[i]);
    }


    // Allocation of the blocks
    // TODO: handle an impossible Allocation
    /*
     *for (i=0; i<bNbBlock; ++i)
     *{
     *    allocateBlock(memory, bBlocksAdd[i]);
     *}
     */


    return 0;
}
