#include <stdlib.h>
#include <string.h>

#include "bm.h"
#include "utils.h"

// Function: bmbits
// Returns the number of bits in the bitmap.
static size_t bmbits(BM b) {
    size_t *bits = b;
    return *--bits;
}

// Function: bmbytes
// Returns the number of bytes required for the bitmap.
static size_t bmbytes(BM b) {
    return bits2bytes(bmbits(b));
}

// Function: ok
// Checks if the given index is within the valid range for the bitmap.
static void ok(BM b, size_t i) {
    if (i < bmbits(b))
        return;
    fprintf(stderr, "bitmap index out of range\n");
    exit(1);
}

// Function: bmcreate
// Creates a new bitmap with the specified number of bits.
extern BM bmcreate(size_t bits) {
    size_t bytes = bits2bytes(bits);
    size_t *p = mmalloc(sizeof(size_t) + bytes);
    if ((long)p == -1)
        return 0;
    *p = bits;
    BM b = ++p;
    memset(b, 0, bytes);
    return b;
}

// Function: bmdelete
// Deallocates memory associated with the bitmap.
extern void bmdelete(BM b) {
    size_t *p = b;
    p--;
    mmfree(p, *p);
}

// Function: bmset
// Sets the bit at the specified index in the bitmap.
extern void bmset(BM b, size_t i) {
    ok(b, i);
    bitset(b + i / bitsperbyte, i % bitsperbyte);
}

// Function: bmclr
// Clears the bit at the specified index in the bitmap.
extern void bmclr(BM b, size_t i) {
    ok(b, i);
    bitclr(b + i / bitsperbyte, i % bitsperbyte);
}

// Function: bmtst
// Tests the bit at the specified index in the bitmap.
// Returns:
//   - int: 1 if the bit is set, 0 otherwise.
extern int bmtst(BM b, size_t i) {
    ok(b, i);
    return bittst(b + i / bitsperbyte, i % bitsperbyte);
}

// Function: bmprt
// Prints a textual representation of the bitmap to stdout.
extern void bmprt(BM b) {
    for (int byte = bmbytes(b) - 1; byte >= 0; byte--)
        printf("%02x%s", ((char *)b)[byte], (byte ? " " : "\n"));
}
