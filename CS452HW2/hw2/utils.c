/*
Author: Anton Leslie
Class: 452
Professor: Buffenburger

Overview:
This program provides memory allocation and deallocation functionalities using mmap and munmap system calls. It also includes helper functions for manipulating bits and converting between bit sizes and byte sizes.

*/

#include <unistd.h>
#include <sys/mman.h>
#include <math.h>
#include <stdio.h>

#define bitsperbyte 8  // Add this line to define bitsperbyte
#define MAX_ORDER 10  // Adjust this value as needed

// Allocate memory using mmap
void *mmalloc(size_t size) {
    return mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

// Deallocate memory using munmap
void mmfree(void *ptr, size_t size) {
    if (ptr != NULL) {
        if (munmap(ptr, size) == -1) {
            perror("Error in mmfree");
        } else {
            printf("Successfully freed %zu bytes of memory at address %p\n", size, ptr);
        }
    } else {
        fprintf(stderr, "Error: Attempted to free a NULL pointer\n");
    }
}

// Divide n by d and round up to the nearest integer
size_t divup(size_t n, size_t d) {
    return (n + d - 1) / d;
}

// Convert number of bits to number of bytes
size_t bits2bytes(size_t bits) {
    return divup(bits, bitsperbyte);
}

// Convert exponent to size
size_t e2size(int e) {
    return (size_t)1 << e;
}

// Convert size to exponent
int size2e(size_t size) {
    return (int)log2(size);
}

// Set a bit in a byte
void bitset(void *p, int bit) {
    char *byte = (char *)p + bit / bitsperbyte;
    *byte |= 1 << (bit % bitsperbyte);
}

// Clear a bit in a byte
void bitclr(void *p, int bit) {
    char *byte = (char *)p + bit / bitsperbyte;
    *byte &= ~(1 << (bit % bitsperbyte));
}

// Invert a bit in a byte
void bitinv(void *p, int bit) {
    char *byte = (char *)p + bit / bitsperbyte;
    *byte ^= 1 << (bit % bitsperbyte);
}

// Test if a bit is set in a byte
int bittst(void *p, int bit) {
    char *byte = (char *)p + bit / bitsperbyte;
    return (*byte & (1 << (bit % bitsperbyte))) != 0;
}
