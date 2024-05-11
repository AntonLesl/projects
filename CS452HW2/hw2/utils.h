// Utility functions for the Buddy System.

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// Constant: bitsperbyte
// Number of bits in a byte.
static const int bitsperbyte = 8;

// Function: mmalloc
// Allocates memory using mmalloc (custom memory allocator).
extern void *mmalloc(size_t size);

// Function: mmfree
// Deallocates memory using mmfree (custom memory deallocator).
extern void mmfree(void *p, size_t size);

// Function: divup
// Rounds up the result of dividing n by d.
extern size_t divup(size_t n, size_t d);

// Function: bits2bytes
// Converts the number of bits to the equivalent number of bytes.
extern size_t bits2bytes(size_t bits);

// Function: e2size
// Converts an exponent to the corresponding size (2^e).
extern size_t e2size(int e);

// Function: size2e
// Converts a size to the corresponding exponent (log2(size)).
extern int size2e(size_t size);

// Function: bitset
// Sets the specified bit in the memory.
extern void bitset(void *p, int bit);

// Function: bitclr
// Clears the specified bit in the memory.
extern void bitclr(void *p, int bit);

// Function: bitinv
// Inverts the specified bit in the memory.
extern void bitinv(void *p, int bit);

// Function: bittst
// Tests the specified bit in the memory.
// Returns:
//   - int: 1 if the bit is set, 0 otherwise.
extern int bittst(void *p, int bit);

#endif
