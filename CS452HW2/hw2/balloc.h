#ifndef BALLOC_H
#define BALLOC_H

// Define the structure for Balloc
typedef struct {
    unsigned int num_levels;
    unsigned int *num_blocks;
    struct {
        void *ptr;
        unsigned int size;
    } **blocks;
} BallocStruct;

// Define Balloc as a pointer to BallocStruct
typedef BallocStruct* Balloc;

// Function: bcreate
// Creates a new allocator instance.
// Parameters:
//   - size: Total size of memory available for allocation.
//   - l: Lower bound specifying the smallest allocation size (2^l).
//   - u: Upper bound specifying the largest allocation size (2^u).
// Returns:
//   - Balloc: Handle to the created allocator instance.
extern Balloc bcreate(unsigned int size, int l, int u);

// Function: bdelete
// Deallocates an allocator instance.
// Parameters:
//   - pool: Handle to the allocator instance to be deleted.
extern void bdelete(Balloc pool);

// Function: balloc
// Allocates a block of memory from the given allocator instance.
// Parameters:
//   - pool: Handle to the allocator instance.
//   - size: Size of the memory block to allocate.
// Returns:
//   - void *: Pointer to the allocated memory block.
extern void *balloc(Balloc pool, unsigned int size);

// Function: bfree
// Deallocates a block of memory previously allocated with balloc.
// Parameters:
//   - pool: Handle to the allocator instance.
//   - mem: Pointer to the memory block to deallocate.
extern void bfree(Balloc pool, void *mem);

// Function: bsize
// Returns the size of a memory block.
// Parameters:
//   - pool: Handle to the allocator instance.
//   - mem: Pointer to the memory block.
// Returns:
//   - unsigned int: Size of the memory block.
extern unsigned int bsize(Balloc pool, void *mem);

// Function: bprint
// Writes a textual representation of the allocator to stdout.
// Useful for debugging purposes.
// Parameters:
//   - pool: Handle to the allocator instance.
extern void bprint(Balloc pool);

#endif
