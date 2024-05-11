/*
  Author: Anton Leslie
  Description: This file implements a simple scanner for tokenizing strings. It provides functions for creating a new scanner, 
  freeing the scanner's resources, advancing to the next token, getting the current token, 
  comparing the current token with a given string, and advancing if the current token matches a given string. 
  The scanner skips whitespace characters while tokenizing.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Scanner.h" // Include the header file for the scanner
#include "error.h"   // Include the header file for error handling

typedef struct {
  int eos;      // Flag indicating if the end of string has been reached
  char *str;    // Pointer to the original string being scanned
  char *pos;    // Pointer to the current position in the string
  char *curr;   // Pointer to the current token
} *ScannerRep; // Define a pointer to a struct representing the scanner

// Function to create a new scanner
extern Scanner newScanner(char *s) {
  ScannerRep r = (ScannerRep)malloc(sizeof(*r)); // Allocate memory for the scanner
  if (!r)
    ERROR("malloc() failed"); // Error handling for memory allocation failure
  r->eos = 0;                  // Initialize end of string flag
  r->str = strdup(s);         // Duplicate the input string
  r->pos = r->str;            // Set the current position to the beginning of the string
  r->curr = 0;                // Initialize current token pointer to NULL
  return r;                   // Return the created scanner
}

// Function to free the resources used by the scanner
extern void freeScanner(Scanner scan) {
  ScannerRep r = scan;    // Cast the scanner to its representation
  free(r->str);           // Free the duplicated string
  if (r->curr)
    free(r->curr);        // Free the current token if it exists
  free(r);                // Free the scanner structure
}

// Helper function to advance the pointer past certain characters
static char *thru(char *p, char *q) {
  for (; *p && strchr(q, *p); p++); // Iterate through characters until a character not in q is found
  return p;                           // Return the updated pointer
}

// Helper function to advance the pointer until certain characters are encountered
static char *upto(char *p, char *q) {
  for (; *p && !strchr(q, *p); p++); // Iterate through characters until a character in q is found
  return p;                           // Return the updated pointer
}

// Helper function to skip whitespace characters
static char *wsthru(char *p) { return thru(p, " \t"); }

// Helper function to find the end of whitespace
static char *wsupto(char *p) { return upto(p, " \t"); }

// Function to get the next token from the scanner
extern char *nextScanner(Scanner scan) {
  ScannerRep r = scan;        // Cast the scanner to its representation
  if (r->eos)                 // Check if end of string is reached
    return NULL;
  char *old = wsthru(r->pos); // Skip leading whitespace
  char *new = wsupto(old);    // Find end of token
  int size = new - old;        // Calculate token size
  if (size == 0) {             // If token size is zero
    r->eos = 1;                // Set end of string flag
    return NULL;
  }
  if (r->curr)
    free(r->curr);             // Free previous token if it exists
  r->curr = (char *)malloc(size + 1); // Allocate memory for the new token
  if (!r->curr)
    ERROR("malloc() failed");   // Error handling for memory allocation failure
  strncpy(r->curr, old, size);  // Copy token to current token buffer
  r->curr[size] = '\0';         // Null-terminate the current token
  r->pos = new;                 // Update current position
  return r->curr;               // Return the current token
}

// Function to get the current token from the scanner
extern char *currScanner(Scanner scan) {
  ScannerRep r = scan;          // Cast the scanner to its representation
  if (r->eos)                   // If end of string is reached
    return NULL;
  if (r->curr)                  // If current token exists
    return r->curr;             // Return current token
  return nextScanner(scan);     // Otherwise, get next token
}

// Function to compare the current token with a given string
extern int cmpScanner(Scanner scan, char *s) {
  ScannerRep r = scan;          // Cast the scanner to its representation
  currScanner(scan);            // Ensure current token is obtained
  if (r->eos)                   // If end of string is reached
    return 0;
  if (strcmp(s, r->curr))       // Compare current token with given string
    return 0;                   // Return 0 if they are not equal
  return 1;                     // Return 1 if they are equal
}

// Function to advance if the current token matches a given string
extern int eatScanner(Scanner scan, char *s) {
  int r = cmpScanner(scan, s);  // Compare current token with given string
  if (r)
    nextScanner(scan);          // If they match, advance to next token
  return r;                     // Return the result of the comparison
}

// Function to get the position of the scanner in the original string
extern int posScanner(Scanner scan) {
  ScannerRep r = scan;          // Cast the scanner to its representation
  return (r->pos) - (r->str);   // Calculate and return the position
}
