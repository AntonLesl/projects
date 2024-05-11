/*
   File: lawn.c
   Author: Anton Leslie
   Description: This file contains the implementation 
   of functions related to managing a lawn and its moles. 
   It provides functionality for creating a new lawn, running it in a separate thread,
    and freeing resources associated with the lawn when it's no longer needed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <X11/Xlib.h>   

#include "lawn.h"
#define LAWNIMP
#include "lawnimp.h"
#undef LAWNIMP
#include "error.h"

// Function to be executed by the thread to run the lawn
static void *run(void *l) {
  LawnRep r=(LawnRep)l;
  return lawnimp_run(r);
}

// Create a new lawn with specified sizes
extern Lawn lawn_new(int lawnsize, int molesize) {
  if (!lawnsize) lawnsize=40;
  if (!molesize) molesize=15;

  XInitThreads();

  // Allocate memory for the lawn structure
  LawnRep lawn=(LawnRep)malloc(sizeof(*lawn));
  if (!lawn) ERROR("malloc() failed");
  lawn->lawnsize=lawnsize;
  lawn->molesize=molesize;
  // Create a new lawn implementation
  lawn->window=lawnimp_new(lawnsize,molesize);
  // Create a new thread to run the lawn
  if (pthread_create(&lawn->thread,0,run,lawn))
    ERROR("pthread_create() failed: %s",strerror(errno));
  return lawn;
}

// Free resources associated with the lawn
extern void lawn_free(Lawn l) {
  LawnRep r=(LawnRep)l;
  // Free the lawn implementation
  lawnimp_free(r->window);
  // Cancel the thread running the lawn
  pthread_cancel(r->thread);
  // Wait for the thread to terminate and free the memory
  if (pthread_join(r->thread,0))
      ERROR("pthread_join() failed: %s",strerror(errno));
  free(r);
}
