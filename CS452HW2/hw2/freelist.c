#include <stdio.h>
#include <stdlib.h>
#include "freelist.h"
#include "utils.h"


/*
Author: Anton Leslie
Class: 452
Instructor: Buffenburger
*/

// Function: freelistcreate
// Creates a new free list.

FreeList freelistcreate(size_t size, int l, int u) {
    // Allocate memory for the FreeList structure
    FreeList f = (FreeList)mmalloc(sizeof(struct FreeList));

    // Check if memory allocation for FreeList was successful
    if (!f) {
        fprintf(stderr, "Failed to create FreeList\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the head node of the FreeList
    f->head = (struct FreeListNode *)mmalloc(sizeof(struct FreeListNode));

    // Check if memory allocation for the head node was successful
    if (!f->head) {
        fprintf(stderr, "Failed to create FreeList node\n");

        // Cleanup: Free the allocated memory for FreeList and exit the program
        free(f);
        exit(EXIT_FAILURE);
    }

    // Initialize the Free List node with memory from mmalloc
    f->head->address = mmalloc(size);
    f->head->size = size;
    f->head->next = NULL;

    // Return the created FreeList structure
    return f;
}

// Function: freelistdelete
// Deallocates a free list.
// Parameters:
//   - f: Handle to the free list.
//   - l: Lower bound specifying the smallest allocation size (2^l).
//   - u: Upper bound specifying the largest allocation size (2^u).
void freelistdelete(FreeList f, int l, int u) {
    // Check if the free list is empty
    if (f == NULL) {
        return;
    }

    // Iterate through the free list and free each node
    struct FreeListNode *current = f->head;
    struct FreeListNode *next;
    while (current != NULL) {
        next = current->next;
        free(current->address); // Free the memory associated with the node
        free(current);          // Free the node itself
        current = next;
    }

    // After freeing all nodes, set the FreeList structure's head to NULL
    f->head = NULL;

    // Free the FreeList structure itself
    free(f);
}



void *freelistalloc(FreeList f, void *base, int e, int l) {
    // Implement your allocation logic using the free list here
}

void freelistfree(FreeList f, void *base, void *mem, int e, int l) {
    // Implement your deallocation logic using the free list here
}

int freelistsize(FreeList f, void *base, void *mem, int l, int u) {
    // Implement your size retrieval logic using the free list here
}

// Function: freelistprint
// Prints a textual representation of the free list to stdout.
// Parameters:
//   - f: Handle to the free list.
//   - l: Lower bound specifying the smallest allocation size (2^l).
//   - u: Upper bound specifying the largest allocation size (2^u).
void freelistprint(FreeList f, int l, int u) {
    // Check if the free list is empty
    if (f == NULL || f->head == NULL) {
        printf("Free list is empty.\n");
        return;
    }

    // Iterate through the free list and print each node
    struct FreeListNode *current = f->head;
    while (current != NULL) {
        printf("Address: %p, Size: %d\n", current->address, current->size);
        current = current->next;
    }
}