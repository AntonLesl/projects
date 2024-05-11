/*
   Author: Anton Leslie
     Description: This program simulates a mole whacking game on a lawn using multi-threading. 
     It utilizes an MT-safe queue to handle mole objects and threads to produce and consume mole objects. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "lawn.h"
#include "mole.h"
// Remove the include of deq.h since using MT-safe wrapper
#include "mt_queue.h"       // Include the MT-safe queue header
#include "thread_utils.h"   // Include thread utility functions

// Adjusts signature of produce and consume functions to be compatible with pthreads
static void *produce(void *arg) {
  ThreadArgs *args = (ThreadArgs *)arg;
  for (int i = 0; i < args->n; i++) {
    Mole m = mole_new(args->l, 0, 0);
    mtq_enqueue(args->q, m);  // Enqueue the mole using the MT-safe queue
  }
  return NULL;
}

static void *consume(void *arg) {
  ThreadArgs *args = (ThreadArgs *)arg;
  for (int i = 0; i < args->n; i++) {
    Mole m = mtq_dequeue(args->q);  // Dequeue the mole using the MT-safe queue
    if (m) {
      mole_whack(m);  // Act on the mole
    }
  }
  return NULL;
}

int main() {
  srandom(time(0));
  const int n = 10;
  const size_t max_capacity = 4;  // max capacity of 4
  Lawn lawn = lawn_new(0, 0);

  MtQueue mt_moleQueue = mtq_new(max_capacity);  // Initialize the MT-safe queue
  pthread_t producer_threads[n];
  pthread_t consumer_threads[n];

  // Prepare arguments for the threads
  ThreadArgs args = {mt_moleQueue, lawn, 1}; // 1 because each thread will act once per call

  // Create producer and consumer threads
  create_threads(producer_threads, produce, &args, n);
  create_threads(consumer_threads, consume, &args, n);

  // Join the producer and consumer threads
  join_threads(producer_threads, n);
  join_threads(consumer_threads, n);

  // Clean up the MT-safe queue and lawn
  mtq_del(mt_moleQueue, (void (*)(void *))mole_whack); 
  lawn_free(lawn);

  return 0;
}
