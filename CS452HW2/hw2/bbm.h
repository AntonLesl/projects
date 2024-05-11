// A baddr bitmap, for the Buddy System.

#ifndef BBM_H
#define BBM_H

#include <stdio.h>

// BBM: Buddy Block Memory (BBM) Allocator Handle
typedef void *BBM;

// Function: bbmcreate
// Creates a new BBM allocator.
// Parameters:
//   - size: Total size of memory available for allocation.
//   - e: Exponent specifying the smallest allocation size (2^e).
// Returns:
//   - BBM: Handle to the created BBM allocator instance.
extern BBM bbmcreate(size_t size, int e);

// Function: bbmdelete
// Deallocates a BBM allocator.
// Parameters:
//   - b: Handle to the BBM allocator instance.
extern void bbmdelete(BBM b);

// Function: bbmset
// Sets a bit in the BBM allocator based on the memory block's bit address.
extern void bbmset(BBM b, void *base, void *mem, int e);

// Function: bbmclr
// Clears a bit in the BBM allocator based on the memory block's bit address.
extern void bbmclr(BBM b, void *base, void *mem, int e);

// Function: bbmtst
// Tests a bit in the BBM allocator based on the memory block's bit address.
// Returns:
//   - int: 1 if the bit is set, 0 otherwise.
extern int bbmtst(BBM b, void *base, void *mem, int e);

// Function: bbmprt
// Prints a textual representation of the BBM allocator to stdout.
extern void bbmprt(BBM b);

// Function: baddrset
// Sets a bit in the memory address based on the given parameters.
extern void *baddrset(void *base, void *mem, int e);

// Function: baddrclr
// Clears a bit in the memory address based on the given parameters.
extern void *baddrclr(void *base, void *mem, int e);

// Function: baddrinv
// Inverts a bit in the memory address based on the given parameters.
extern void *baddrinv(void *base, void *mem, int e);

// Function: baddrtst
// Tests a bit in the memory address based on the given parameters.
// Returns:
//   - int: 1 if the bit is set, 0 otherwise.
extern int baddrtst(void *base, void *mem, int e);

#endif
