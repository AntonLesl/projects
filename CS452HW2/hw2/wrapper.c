#include <string.h>

#include "balloc.h"

// Static variable: bp
// Global variable to store the Balloc handle.
static Balloc bp = 0;

#include <stdio.h>

// Function: malloc
// Wrapper for the malloc function using the balloc allocator.
// Parameters:
//   - size: Size of the memory to allocate.
// Returns:
//   - void *: Pointer to the allocated memory.
extern void *malloc(size_t size) {
    // Initialize the Balloc handle if not already initialized
    bp = bp ? bp : bcreate(4096, 4, 12);

    // Allocate memory using the balloc allocator
    return balloc(bp, size);
}

// Function: free
// Wrapper for the free function using the balloc allocator.
// Parameters:
//   - ptr: Pointer to the memory to free.
extern void free(void *ptr) {
    // Free the memory using the balloc allocator
    bfree(bp, ptr);
}

// Function: realloc
// Wrapper for the realloc function using the balloc allocator.
// Parameters:
//   - ptr: Pointer to the previously allocated memory.
//   - size: New size of the memory.
// Returns:
//   - void *: Pointer to the reallocated memory.
extern void *realloc(void *ptr, size_t size) {
    // Local function: min
    // Returns the minimum of two values.
    size_t min(size_t x, size_t y) {
        return x < y ? x : y;
    }

    // Allocate new memory using the balloc allocator
    void *new = malloc(size);

    // If the original pointer is null, return the newly allocated memory
    if (!ptr)
        return new;

    // Copy the contents from the old memory to the new memory
    memcpy(new, ptr, min(size, bsize(bp, ptr)));

    // Free the original memory
    free(ptr);

    // Return the pointer to the newly allocated and copied memory
    return new;
}
