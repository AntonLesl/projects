/*
Author: Anton Leslie
Class: 452
Instructor: Buffenburger

Overview:
This program demonstrates memory allocation and deallocation using a custom memory allocator (Balloc) and a free list data structure. It creates a Balloc instance, prints its information, creates a FreeList instance, allocates memory using both methods, and prints the initial and final states of the free list. However, it is commented out to avoid cleaning up the allocated memory and deleting the Balloc instance for testing purposes.

*/

#include <stdio.h>
#include <stdlib.h>
#include "balloc.h"
#include "freelist.h"

#define MAX_SIZE 1024 // Maximum size for testing

int main() {
    // Create a Balloc instance
    Balloc pool = bcreate(MAX_SIZE, 4, 10);

    // Check if Balloc was created successfully
    if (pool == NULL) {
        fprintf(stderr, "Failed to create Balloc\n");
        return 1;  // Return an error code
    }

    // Print a success message
    printf("Balloc instance created successfully!\n");

    // Test the bprint function
    printf("Printing Balloc information:\n");
    bprint(pool);

    // Create a FreeList instance
    FreeList freeList = freelistcreate(MAX_SIZE, 4, 10);

    // Check if FreeList was created successfully
    if (freeList == NULL) {
        fprintf(stderr, "Failed to create FreeList\n");
        // bdelete(pool); // Clean up Balloc instance
        return 1;  // Return an error code
    }

    // Print the initial state of the free list
    printf("Initial state of the free list:\n");
    freelistprint(freeList, 0, 10);

    // Test different allocation sizes
    for (int size = 8; size <= MAX_SIZE; size *= 2) {
        // Allocate memory using Balloc
        void *allocatedMemBalloc = balloc(pool, size);
        printf("Allocated memory using Balloc with size %d at address: %p\n", size, allocatedMemBalloc);

        // Allocate memory using the FreeList
        void *allocatedMemFreeList = freelistalloc(freeList, NULL, size, 4);
        printf("Allocated memory using FreeList with size %d at address: %p\n", size, allocatedMemFreeList);
    }

    // Print the final state of the free list
    printf("Final state of the free list:\n");
    freelistprint(freeList, 0, 10);

    // Clean up: Free the allocated memory for the free list
    // freelistdelete(freeList, 4, 10);

    // Cleanup and delete Balloc instance
    // bdelete(pool);

    return 0;
}
