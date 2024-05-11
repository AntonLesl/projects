/*
Author: Anton Leslie
Class: 452
Project: Buffenburger

Overview:
This code implements a memory allocation system using the Buddy System algorithm. It provides functions to create and delete a Balloc instance, allocate and free memory blocks, and retrieve allocation size. The Balloc instance manages a FreeList for managing free blocks and a BitBlockMap (BBM) for bit-level bookkeeping.

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "balloc.h"
#include "freelist.h"
#include "bbm.h"
#include "utils.h"

// Define the internal structure of the Balloc instance
struct BallocStruct {
    FreeList freeList;  // FreeList for managing free blocks
    BBM bbm;            // BBM (Buddy Block Memory) for bit-level bookkeeping
};

// Function: bcreate
// Creates a new Balloc instance using the Buddy System for memory allocation.
// Parameters:
//   - size: Total size of memory available for allocation.
//   - l: Lower bound specifying the smallest allocation size (2^l).
//   - u: Upper bound specifying the largest allocation size (2^u).
// Returns:
//   - Balloc: Handle to the created Balloc instance.
Balloc bcreate(unsigned int size, int l, int u) {
    // Allocate memory for the BallocStruct using mmalloc
    struct BallocStruct *pool = (struct BallocStruct *)mmalloc(sizeof(struct BallocStruct));

    // Check if memory allocation was successful
    if (!pool) {
        fprintf(stderr, "Failed to create Balloc\n");
        exit(EXIT_FAILURE);
    }

    // Create a free list using freelistcreate and assign it to the freeList member of BallocStruct
    pool->freeList = freelistcreate(size, l, u);

    // Create a bbm (assuming it's a BitBlockMap) using bbmcreate and assign it to the bbm member of BallocStruct
    pool->bbm = bbmcreate(size, l);  // Assuming bbmcreate only requires two arguments

    // Cast the BallocStruct pointer to Balloc and return
    return (Balloc)pool;
}

// Function: bdelete
// Deletes a Balloc instance, freeing all allocated memory.
// Parameters:
//   - pool: Balloc instance to be deleted.
void bdelete(Balloc pool) {
    if (pool == NULL) {
        return; // Nothing to delete if Balloc instance is NULL
    }

    // Cast pool to Balloc pointer
    struct BallocStruct *b = (struct BallocStruct *)pool;

    // Cleanup: Free the free list
    if (b->freeList != NULL) {
        freelistdelete(b->freeList, 0, 10);
    }

    // Cleanup: Free the BBM
    if (b->bbm != NULL) {
        bbmdelete(b->bbm);
    }

    // After freeing all associated resources, set the pointers to NULL
    b->freeList = NULL;
    b->bbm = NULL;

    // Free the Balloc instance itself
    free(b);
}

// Placeholder function for allocating memory using the Buddy System
void *balloc(Balloc pool, unsigned int size) {
    // Implementation needed
}

// Placeholder function for freeing memory using the Buddy System
void bfree(Balloc pool, void *mem) {
    // Implementation needed
}

// Placeholder function for retrieving allocation size
unsigned int bsize(Balloc pool, void *mem) {
    // Implementation needed
}

#include <stdio.h>
#include "balloc.h" // Assuming you have a header file for Balloc

void bprint(Balloc pool) {
    if (pool == NULL) {
        printf("Balloc instance is NULL\n");
        return;
    }

    printf("Balloc information:\n");
    printf("Address: %p\n", pool); // Print the address of the Balloc instance
    // Print other relevant information about the Balloc instance as needed
}

