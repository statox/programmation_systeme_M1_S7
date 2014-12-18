 /*
  * definition of the structures used by our application
  */
#ifndef STRUCTURES_H
#define STRUCTURES_H


#include <stdbool.h>    // C99 definition for booleans

/*
 * Structure representing a memory block with
 *  - its address
 *  - its length
 *  - the following block
 */
typedef struct Block Block;
struct Block
{
    int address;
    int length;
    int usedLength;
    bool allocated;
    struct Block *next;
};


/*
 * Structure representing the whole memory composed of several blocks.
 * It is a pointer on the first Block of the memory
 */
typedef Block* Memory;



#endif /* STRUCTURES_H */
