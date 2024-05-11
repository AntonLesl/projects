/*
   File: thread_utils.c
   Author: Anton Leslie
   Description: This file contains utility functions for working with threads.
                It includes functions to create and join threads.
*/

#include "thread_utils.h" // Include the header file for thread utilities
#include <stdio.h> // Include standard I/O library for input/output operations
#include <stdlib.h> // Include standard library for memory allocation, exit status, etc.

// Function to create multiple threads
void create_threads(pthread_t *threads, void *(*func)(void *), ThreadArgs *args, int n) {
  for (int i = 0; i < n; ++i) {
    if (pthread_create(&threads[i], NULL, func, (void *)args) != 0) {
      // Handle error if thread creation fails
      fprintf(stderr, "Error creating thread %d\n", i);
      exit(EXIT_FAILURE); // Exit the program with failure status
    }
  }
}

// Function to join multiple threads
void join_threads(pthread_t *threads, int n) {
  for (int i = 0; i < n; ++i) {
    if (pthread_join(threads[i], NULL) != 0) {
      // Handle error if thread joining fails
      fprintf(stderr, "Error joining thread %d\n", i);
      exit(EXIT_FAILURE); // Exit the program with failure status
    }
  }
}
