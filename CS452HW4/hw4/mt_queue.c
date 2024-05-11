/*
   Author: Anton Leslie
   Description: This header file includes the necessary declarations for a multi-threaded queue (MtQueue) implementation, 
   along with functions to create, delete, enqueue, and dequeue elements from the queue while maintaining thread safety.
*/

#include <stdlib.h>
#include "mt_queue.h"

// Function to create a new multi-threaded queue (MtQueue) with a specified maximum capacity
MtQueue mtq_new(size_t max_capacity) {
    MtQueue mtq = malloc(sizeof(*mtq));  // Allocate memory for the MtQueue struct
    if (mtq == NULL) {
        // Handle memory allocation failure appropriately
    }

    mtq->queue = deq_new();                // Create an underlying deque for the queue
    mtq->max_capacity = max_capacity;      // Set the maximum capacity of the queue

    // Initialize synchronization primitives for thread safety
    pthread_mutex_init(&mtq->lock, NULL);          // Initialize the mutex
    pthread_cond_init(&mtq->not_full, NULL);       // Initialize condition variable for "not full"
    pthread_cond_init(&mtq->not_empty, NULL);      // Initialize condition variable for "not empty"

    return mtq;
}

// Function to delete an MtQueue, optionally freeing its elements
void mtq_del(MtQueue mtq, void (*free_func)(void *)) {
    // Destroy synchronization primitives
    pthread_mutex_destroy(&mtq->lock);
    pthread_cond_destroy(&mtq->not_full);
    pthread_cond_destroy(&mtq->not_empty);

    // Delete the underlying deque, potentially freeing its elements
    deq_del(mtq->queue, free_func);

    // Free the memory allocated for the MtQueue struct
    free(mtq);
}

// Function to enqueue data into the MtQueue, respecting capacity limits
void mtq_enqueue(MtQueue mtq, void *data) {
    pthread_mutex_lock(&mtq->lock);  // Acquire the mutex for thread safety

    // Wait if the queue has a maximum capacity and it's currently full
    while (mtq->max_capacity > 0 && deq_len(mtq->queue) >= mtq->max_capacity) {
        pthread_cond_wait(&mtq->not_full, &mtq->lock);  // Wait until the queue is not full
    }

    // Enqueue the data into the underlying deque
    deq_tail_put(mtq->queue, data);

    pthread_cond_signal(&mtq->not_empty);  // Signal that the queue is now not empty
    pthread_mutex_unlock(&mtq->lock);      // Release the mutex
}

// Function to dequeue data from the MtQueue
void *mtq_dequeue(MtQueue mtq) {
    pthread_mutex_lock(&mtq->lock);  // Acquire the mutex for thread safety

    // Wait if the queue is currently empty
    while (deq_len(mtq->queue) == 0) {
        pthread_cond_wait(&mtq->not_empty, &mtq->lock);  // Wait until the queue is not empty
    }

    void *data = deq_head_get(mtq->queue);  // Dequeue data from the underlying deque

    pthread_cond_signal(&mtq->not_full);   // Signal that the queue is now not full
    pthread_mutex_unlock(&mtq->lock);      // Release the mutex

    return data;  // Return the dequeued data
}
