#include "headers/memory.h"

#include <string.h>

int intLength(int value) {
    int i = 1;
    int length = 0;

    if (value == 0) {
        return 1;
    } else {
        while (i < value + 1) {
            i *= 10;
            ++length;
        }
        return length;
    }
    // Test :
    // for (int i = 0; i < 13; ++i)
    // {
    //     printf("%d\t%d\n", i, intLength(i));
    // }
    // printf("%d %d %d", intLength(0), intLength(100), intLength(1001));
}

// Output the content of the Memory
void printMem2 (Memory memory)
{
    Block* tmp = memory;
//    int totalSpace  = 0;
//    int usedSpace   = 0;
    int quantity    = 0;

//    int addedChar   = 0;
//    int bufferMaxSize = (usedSpace + (3-1)*quantity);
//    char* buffer = malloc(bufferMaxSize * sizeof(char));



    while (tmp != NULL) {
        for (int i = tmp->usedLength - 1; i >= 0; --i)
        {
            printf("#");
        }
        for (int i = tmp->length - tmp->usedLength - 1; i >= 0; --i)
        {
            printf("_");
        }

        printf("   ");
        quantity++;
        tmp = tmp->next;
    }


    // bufferMaxSize = (usedSpace + (3-1)*quantity);
    // buffer = malloc(bufferMaxSize * sizeof(char));

    // buffer[bufferMaxSize - 1] = '\0';
    // tmp = memory;
    // int currentIndex = 0;
    // while (tmp != NULL) {
    //     // tempStringDescription(buffer, bufferMaxSize, &currentIndex, tmp);
    //     addedChar = snprintf(buffer + currentIndex*sizeof(char), bufferMaxSize - currentIndex*sizeof(char), "%d / %d", tmp->usedLength, tmp->length);
    //     for (int i = 0; i < addedChar; ++i) {
    //         printf(" ");
    //     }
    //     printf("   ");
    //     currentIndex += addedChar + 3;
    //     tmp = tmp->next;
    // }
    // printf("\n%s\n", buffer);
    // free(buffer);
    return;
}

// Output the content of the Memory
// TODO: Make this function beautiful
void printMem (Memory memory)
{

    Block* tmp=memory;
    int totalSpace  = 0;
    int usedSpace   = 0;

    printf ("@ \t - Used\t/Length\t-  n.@\tA\n");
    printf ("---------------------------------\n");
    while (tmp != NULL)
    {
        totalSpace  += tmp->length;
        usedSpace   += tmp->usedLength;
        if (tmp->next != NULL)
        {
            printf("%d \t - %d\t/ %d\t-  %d \t%d \n", tmp->address, tmp->usedLength, tmp->length, tmp->next->address, tmp->allocated);
        }
        else
        {
            printf("%d \t - %d\t/ %d\t-  NULL\t%d \n", tmp->address, tmp->usedLength, tmp->length, tmp->allocated);
        }
        tmp = tmp->next;
    }

    printf ("---------------------------------\n");
    printf ("Taille totale: %d\n", totalSpace);
    printf ("Espace utilise: %d\n", usedSpace);
    return;
}

// Utility function: create a consistent memory.
Memory createMemory (int nbBlocks, int blockSize)
{
    /*int i = 0;*/
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
        if (usedLength <= tmp->length)
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
        tmp->allocated  = false;
        tmp->usedLength = 0;
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

// iterate through the memory and free a part of the desired block
int freeBlockLength (Memory memory, int address, int lengthFree)
{
    // iteration through the memory
    Block* tmp = memory;
    while (tmp != NULL && tmp->address != address)
        tmp = tmp->next;

    // if the Block is found mark and the allocated space in the bloc is greater and the length to free
    if (tmp != NULL && tmp->allocated)
    {
        if (tmp->usedLength >= lengthFree)
        {
            tmp->usedLength = tmp->usedLength-lengthFree;
            if (tmp->usedLength==0)
                tmp->allocated = false;

            return 0;
        }else
        {
            printf ("Liberation impossible, le bloc %d ne possede pas autant d'espace occupe\n", address);
            return -4;
        }
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

// check the allocated blocks, sums the free part in the allocated blocks and compare it to the requested value
bool isDefragUseful (Memory memory, int requestedSize)
{
    Block* tmp  = memory;
    int available = 0;

    while (tmp != NULL)
    {
        if (tmp->allocated)
        {
            available += (tmp->length - tmp->usedLength);
        }
        tmp = tmp->next;
    }

    // printf ("The waisted memory in the allocated block is: %d\n", available);

    if (available >= requestedSize)
        return true;

    return false;
}

// check the allocated blocks, sums the free part in the allocated blocks and compare it to the requested value
bool isDefrag2Useful (Memory memory, int requestedSize)
{
    Block* tmp  = memory;
    int available = 0;

    while (tmp != NULL)
    {
        available += (tmp->length - tmp->usedLength);
        tmp = tmp->next;
    }

    // printf ("The waisted memory in the allocated block is: %d\n", available);

    if (available >= requestedSize)
        return true;

    return false;
}

// Create 2 new blocks from concatenation of the waisted spaces in the allocated blocks
//  In the 2 blocks
//      one is of the size of requestedSize
//      The other one is of (total waisted space) - requestedSize
//
//  Before any operation, the function uses isDefragUseful to check if there is enough
//  free space to create a block of the requestedSize

Memory defrag (Memory memory, int requestedSize)
{
    printf("\ndefrag en cours\n");
    Block* tmp      = memory;
    Block* prev     = NULL;
    int freeSpace   = 0;

    if (!isDefragUseful(memory, requestedSize))
        printf ("La defragmentation ne permettra pas de recuperer un espace de %d\n", requestedSize);

    while (tmp != NULL)
    {
        if (tmp->allocated && tmp->length != tmp->usedLength)
        {
            freeSpace   += tmp->length - tmp->usedLength;
            tmp->length = tmp->usedLength;
        }
        prev    = tmp;
        tmp     = tmp->next;
    }

    printf ("total espace perdu dans les blocs alloues %d\n", freeSpace);
    printf ("taille du nouveau bloc 1 %d\n", requestedSize);
    if (freeSpace > requestedSize) {
        printf ("taille du nouveau bloc 2 : %d\n", (freeSpace-requestedSize));
    }

    printf ("Creation d'un nouveau bloc de %d\n", requestedSize);
    memory = addEnd(memory, prev->address+1, requestedSize, 0);

    if (freeSpace > requestedSize) {
        printf ("Creation d'un nouveau bloc de %d\n", (freeSpace-requestedSize));
        memory = addEnd(memory, prev->address+2, (freeSpace-requestedSize), 0);
    }

    printf("Fin de la defragmentation.\n");

    return memory;
}

Memory defrag2SuperDestructiveAndWithSeveralErrors (Memory memory, int requestedSize)
// Memory defrag2 (Memory memory, int requestedSize)
{
    Block* tmp      = memory;
    Block* prev     = NULL;
    Block* prev2     = NULL;
    bool lastOneShouldGetBigger = false;
    bool deletion = false;
    int freeSpace   = 0;

    if (!isDefrag2Useful(memory, requestedSize))
        printf ("La defragmentation ne permettra pas de recuperer un espace de %d\n", requestedSize);

    while (tmp != NULL )
    {
        deletion = false;
        if (tmp->allocated && tmp->length != tmp->usedLength)
        {
            freeSpace   += tmp->length - tmp->usedLength;
            tmp->length = tmp->usedLength;

        }
        else if (!tmp->allocated)
        {
            freeSpace += tmp->length;
            if (prev != NULL) {
                if (tmp->next != NULL) {
                    prev->next = tmp->next;
                    free(tmp);
                    tmp = prev->next;
                    deletion = true;
                } else {
                    lastOneShouldGetBigger = true;
                }
            } else {
                if (tmp->next != NULL) {
                    memory = tmp->next;
                    free(tmp);
                    tmp = memory;
                    deletion = true;
                } else {
                    lastOneShouldGetBigger = true;
                    printf("What !!!!?");
                    perror("What !!!!?");
                }
            }
        }
        if (!deletion) {
            prev2   = prev;
            prev    = tmp;
            tmp     = tmp->next;
        }
    }

    printf ("total espace libere : %d\n", freeSpace);
    printf ("taille du nouveau bloc 1 %d\n", requestedSize);
    if (freeSpace > requestedSize) {
        printf ("taille du nouveau bloc 2 : %d\n", (freeSpace-requestedSize));
    }

    if (!lastOneShouldGetBigger) {
        printf ("Creation d'un nouveau bloc de %d\n", requestedSize);
        memory = addEnd(memory, prev->address+1, requestedSize, 0);
    } else {
        printf ("Agrandissement du dernier block de %d\n", requestedSize - prev->length);
        prev->length = requestedSize;
        prev->usedLength = requestedSize;
        prev->allocated = true;
    }

    if (freeSpace > requestedSize) {
        printf ("Creation d'un nouveau bloc de %d\n", (freeSpace-requestedSize));
        memory = addEnd(memory, prev->address+2, (freeSpace-requestedSize), 0);
    }
    printf("Fin de la defragmentation.\n");

    return memory;
}


Memory defrag2 (Memory memory, int requestedSize)
{
    Block* tmp      = memory;
    Block* prev     = NULL;
    Block* prev2    = NULL;
    bool lastOneShouldGetBigger = false;
    bool deletion = false;
    int freeSpace   = 0;

    if (!isDefrag2Useful(memory, requestedSize))
        printf ("La defragmentation ne permettra pas de recuperer un espace de %d\n", requestedSize);

    while (tmp != NULL )
    {
        deletion = false;
        if (freeSpace < requestedSize && tmp->allocated && tmp->length != tmp->usedLength)
        {
            freeSpace   += tmp->length - tmp->usedLength;
            tmp->length = tmp->usedLength;

        }
        else if (freeSpace < requestedSize && !tmp->allocated)
        {
            freeSpace += tmp->length;
            // if (prev != NULL) {
            if (tmp != memory) {
                if (tmp->next != NULL) {
                    prev->next = tmp->next;
                    free(tmp);
                    tmp = prev->next;
                    deletion = true;
                } else {
                    lastOneShouldGetBigger = true;
                }
            } else {
                if (tmp->next != NULL) {
                    // memory = tmp->next;
                    // free(tmp);
                    // tmp = memory;
                    // deletion = true;
                    tmp = memory->next;
                    memory->address = tmp->address;
                    memory->allocated = tmp->allocated;
                    memory->length = tmp->length;
                    memory->next = tmp->next;
                    memory->usedLength = tmp->usedLength;
                    free(tmp);
                    tmp = memory;
                    deletion = true;
                } else {
                    lastOneShouldGetBigger = true;
                    printf("What !!!! Degraf can't do any good if there is only one block, so we shouldn't be here...");
                    printf("What !!!! Degraf can't do any good if there is only one block, so we shouldn't be here...");
                }
            }
        }
        if (!deletion) {
            prev2   = prev;
            prev    = tmp;
            tmp     = tmp->next;
        }
    }

    printf ("total espace libere : %d\n", freeSpace);
    printf ("taille du nouveau bloc 1 : %d\n", requestedSize);
    if (freeSpace > requestedSize) {
        printf ("taille du nouveau bloc 2 : %d\n", (freeSpace-requestedSize));
    }

    if (!lastOneShouldGetBigger) {
        printf ("Creation d'un nouveau bloc de %d\n", requestedSize);
        memory = addEnd(memory, prev->address+1, requestedSize, 1);
        prev->next->usedLength = requestedSize;
    } else {
        printf ("Agrandissement du dernier block de %d\n", requestedSize - prev->length);
        prev->length = requestedSize;
        prev->usedLength = requestedSize;
        prev->allocated = true;
    }

    if (freeSpace > requestedSize) {
        printf ("Creation d'un nouveau bloc de %d\n", (freeSpace-requestedSize));
        memory = addEnd(memory, prev->address+2, (freeSpace-requestedSize), 0);
    }

    printf("Fin de la defragmentation.\n");

    return memory;
}

int useSomeDefragmentationAlgorithm (Memory *memory, int requestedSize) {
    printf("Il n'existe pas de bloc capable de contenir cette requete.\nEssayons de trouver de la place...\n");
    if (isDefragUseful(*memory, requestedSize)) {
        printf("Un algorithme efficace a ete identifie.\nEn cours...\n");
        *memory = defrag(*memory, requestedSize);
        return 0;
    } else {
        printf("Defragmenter n'est pas suffisant....\nEssayons de trouver de la place avec un autre algorithme...\n");
        if (isDefrag2Useful(*memory, requestedSize)) {
            printf("Un algorithme efficace a ete identifie.\nEn cours...\n");
            *memory = defrag2(*memory, requestedSize);
            return 0;
        } else {
            printf("Defragmenter n'est pas suffisant....\n");
        }
    }
    return -1;
}

void freeAndDeleteMemoryForGood(Memory memory) {
    Block* tmp = NULL;

    if (memory != NULL) {
        do {
            tmp = memory->next;
            free(memory);
            memory = tmp;
        } while (memory != NULL);
    }
}
