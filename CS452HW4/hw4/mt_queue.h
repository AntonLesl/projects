
#ifndef MT_QUEUE_H
#define MT_QUEUE_H

#include "deq.h"
#include <pthread.h>

typedef struct mt_queue {
  Deq queue;
  pthread_mutex_t lock;
  size_t max_capacity;
  pthread_cond_t not_full;
  pthread_cond_t not_empty;
} *MtQueue;

MtQueue mtq_new(size_t max_capacity);
void mtq_del(MtQueue mtq, void (*free_func)(void *));
void mtq_enqueue(MtQueue mtq, void *data);
void *mtq_dequeue(MtQueue mtq);

#endif
