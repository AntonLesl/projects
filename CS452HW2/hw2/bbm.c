#include "bbm.h"
#include "bm.h"
#include "utils.h"


// Function: mapsize
// Calculates the number of buddies required based on the given size and exponent.
static size_t mapsize(size_t size, int e) {
    size_t blocksize = e2size(e);
    size_t blocks = divup(size, blocksize);
    size_t buddies = divup(blocks, 2);
    return buddies;
}

// Function: bitaddr
// Calculates the bit address of a memory block based on the given parameters.
static size_t bitaddr(void *base, void *mem, int e) {
    size_t addr = baddrclr(base, mem, e) - base;
    size_t blocksize = e2size(e);
    return addr / blocksize / 2;
}

// Function: bbmcreate
// Creates a new Buddy Block Memory (BBM) allocator.
extern BBM bbmcreate(size_t size, int e) {
    BBM b = bmcreate(mapsize(size, e));
    if ((long)b == -1)
        return 0;
    return b;
}

// Function: bbmdelete
// Deallocates a BBM allocator.
extern void bbmdelete(BBM b) {
    bmdelete(b);
}

// Function: bbmset
// Sets a bit in the BBM allocator based on the memory block's bit address.
extern void bbmset(BBM b, void *base, void *mem, int e) {
    bmset(b, bitaddr(base, mem, e));
}

// Function: bbmclr
// Clears a bit in the BBM allocator based on the memory block's bit address.
extern void bbmclr(BBM b, void *base, void *mem, int e) {
    bmclr(b, bitaddr(base, mem, e));
}

// Function: bbmtst
// Tests a bit in the BBM allocator based on the memory block's bit address.
extern int bbmtst(BBM b, void *base, void *mem, int e) {
    return bmtst(b, bitaddr(base, mem, e));
}

// Function: bbmprt
// Prints a textual representation of the BBM allocator to stdout.
extern void bbmprt(BBM b) {
    bmprt(b);
}

// Function: baddrset
// Sets a bit in the memory address based on the given parameters.
extern void *baddrset(void *base, void *mem, int e) {
    unsigned int mask = 1 << e;
    return base + ((mem - base) | mask);
}

// Function: baddrclr
// Clears a bit in the memory address based on the given parameters.
extern void *baddrclr(void *base, void *mem, int e) {
    unsigned int mask = ~(1 << e);
    return base + ((mem - base) & mask);
}

// Function: baddrinv
// Inverts a bit in the memory address based on the given parameters.
extern void *baddrinv(void *base, void *mem, int e) {
    unsigned int mask = 1 << e;
    return base + ((mem - base) ^ mask);
}

// Function: baddrtst
// Tests a bit in the memory address based on the given parameters.
extern int baddrtst(void *base, void *mem, int e) {
    unsigned int mask = 1 << e;
    return (mem - base) & mask;
}
