/*
 *  Those functions implements the first-fit algorithm
 */

#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include "structures.h"
#include "memory.h"


int FFallocate (Memory memory, int requestedSize);

#endif /* FIRSTFIT_H */
