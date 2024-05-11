// A module for managing a free list in the Buddy System.

#ifndef FREELIST_H
#define FREELIST_H

#include <stdio.h>

// Define the structure for FreeListNode
struct FreeListNode {
    void *address;              // Pointer to the start address of the free memory block
    int size;                   // Size of the free memory block
    struct FreeListNode *next; // Pointer to the next node in the free list
};

// Define the structure for FreeList
typedef struct FreeList {
    struct FreeListNode *head; // Pointer to the head of the free list
} *FreeList;  // Define FreeList as a pointer to struct FreeList

// Function prototypes...

// Function: freelistcreate
// Creates a new free list.
// Parameters:
//   - size: Total size of memory available for allocation.
//   - l: Lower bound specifying the smallest allocation size (2^l).
//   - u: Upper bound specifying the largest allocation size (2^u).
// Returns:
//   - FreeList: Handle to the created free list.
FreeList freelistcreate(size_t size, int l, int u);

// Function: freelistdelete
// Deallocates a free list.
// Parameters:
//   - f: Handle to the free list.
//   - l: Lower bound specifying the smallest allocation size (2^l).
//   - u: Upper bound specifying the largest allocation size (2^u).
void freelistdelete(FreeList f, int l, int u);

// Function: freelistalloc
// Allocates a block of memory from the free list.
// Parameters:
//   - f: Handle to the free list.
//   - base: Base address of the memory region.
//   - e: Exponent specifying the smallest allocation size (2^e).
//   - l: Lower bound specifying the smallest allocation size (2^l).
// Returns:
//   - void *: Pointer to the allocated memory block.
void *freelistalloc(FreeList f, void *base, int e, int l);

// Function: freelistfree
// Deallocates a block of memory and adds it back to the free list.
// Parameters:
//   - f: Handle to the free list.
//   - base: Base address of the memory region.
//   - mem: Pointer to the memory block to deallocate.
//   - e: Exponent specifying the smallest allocation size (2^e).
//   - l: Lower bound specifying the smallest allocation size (2^l).
void freelistfree(FreeList f, void *base, void *mem, int e, int l);

// Function: freelistsize
// Returns the size of an allocated memory block.
// Parameters:
//   - f: Handle to the free list.
//   - base: Base address of the memory region.
//   - mem: Pointer to the allocated memory block.
//   - l: Lower bound specifying the smallest allocation size (2^l).
//   - u: Upper bound specifying the largest allocation size (2^u).
// Returns:
//   - int: Size of the allocated memory block.
int freelistsize(FreeList f, void *base, void *mem, int l, int u);

// Function: freelistprint
// Prints a textual representation of the free list to stdout.
// Parameters:
//   - f: Handle to the free list.
//   - l: Lower bound specifying the smallest allocation size (2^l).
//   - u: Upper bound specifying the largest allocation size (2^u).
void freelistprint(FreeList f, int l, int u);

#endif
