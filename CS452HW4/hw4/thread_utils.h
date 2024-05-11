#ifndef THREAD_UTILS_H
#define THREAD_UTILS_H

#include <pthread.h>
#include "mt_queue.h"
#include "lawn.h"


typedef struct thread_args {
  Deq q;
  Lawn l;
  int n; // Number of times to call the function
} ThreadArgs;

void create_threads(pthread_t *threads, void *(*func)(void *), ThreadArgs *args, int n);
void join_threads(pthread_t *threads, int n);

#endif
