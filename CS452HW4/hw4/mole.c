/*
 * Author: Anton Leslie
 * Description: This file implements functions to create and manipulate mole objects within a lawn.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mole.h"   // Include necessary header files
#define LAWNIMP     // Define LAWNIMP flag for inclusion of lawnimp.h
#include "lawnimp.h"
#undef LAWNIMP      // Undefine LAWNIMP flag after including lawnimp.h
#include "error.h"

// Function to generate a random integer within a specified range [lo, hi]
static int rdm(int lo, int hi) {
  return random()%(hi-lo+1)+lo;
}

// Function to create a new mole object within a given lawn with specified vitality range
extern Mole mole_new(Lawn l, int vimlo, int vimhi) {
  if (!vimlo) vimlo=1;            // Set default lower vitality limit if not provided
  if (!vimhi) vimhi=5;            // Set default upper vitality limit if not provided

  LawnRep lawn=(LawnRep)l;        // Cast lawn object to LawnRep type
  MoleRep mole=(MoleRep)malloc(sizeof(*mole));   // Allocate memory for mole object
  if (!mole) ERROR("malloc() failed");           // Check for memory allocation failure
  mole->size=lawn->molesize;                      // Initialize mole size from lawn
  int max=lawn->lawnsize*lawn->molesize;          // Calculate maximum possible mole position
  mole->x=rdm(0,max-1);                            // Generate random x-coordinate within lawn
  mole->y=rdm(0,max-1);                            // Generate random y-coordinate within lawn
  mole->vim0=rdm(vimlo,vimhi);                     // Generate random vitality within specified range
  mole->vim1=rdm(vimlo,vimhi);                     // Generate random vitality within specified range
  mole->vim2=rdm(vimlo,vimhi);                     // Generate random vitality within specified range
  mole->lawn=lawn;                                 // Assign lawn to mole
  mole->box=lawnimp_mole(mole);                    // Get mole's box position within lawn
  return mole;                                     // Return created mole object
}

// Function to whack a mole, removing it from the lawn
extern void mole_whack(Mole m) {
  lawnimp_whack(m);   // Call function to whack mole from lawn
  free(m);            // Free memory allocated for mole object
}
