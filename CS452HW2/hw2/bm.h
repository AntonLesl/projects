// A general-purpose bitmap.

#ifndef BM_H
#define BM_H

#include <stdio.h>

// BM: Bitmap Handle
typedef void *BM;

// Function: bmcreate
// Creates a new bitmap with the specified number of bits.
// Parameters:
//   - bits: Number of bits in the bitmap.
// Returns:
//   - BM: Handle to the created bitmap.
extern BM bmcreate(size_t bits);

// Function: bmdelete
// Deallocates memory associated with the bitmap.
// Parameters:
//   - b: Handle to the bitmap.
extern void bmdelete(BM b);

// Function: bmset
// Sets the bit at the specified index in the bitmap.
// Parameters:
//   - b: Handle to the bitmap.
//   - i: Index of the bit to set.
extern void bmset(BM b, size_t i);

// Function: bmclr
// Clears the bit at the specified index in the bitmap.
// Parameters:
//   - b: Handle to the bitmap.
//   - i: Index of the bit to clear.
extern void bmclr(BM b, size_t i);

// Function: bmtst
// Tests the bit at the specified index in the bitmap.
// Parameters:
//   - b: Handle to the bitmap.
//   - i: Index of the bit to test.
// Returns:
//   - int: 1 if the bit is set, 0 otherwise.
extern int bmtst(BM b, size_t i);

// Function: bmprt
// Prints a textual representation of the bitmap to stdout.
// Parameters:
//   - b: Handle to the bitmap.
extern void bmprt(BM b);

#endif
