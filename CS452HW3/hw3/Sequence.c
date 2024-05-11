/*
 * File: sequence.c
 * Author: Anton Leslie
 * Description: This file implements functions for managing sequences of pipelines.
 *              A sequence is represented as a deque (double-ended queue) of pipelines.
 */

#include "Sequence.h"
#include "deq.h"
#include "error.h"

// Creates a new sequence and returns it
extern Sequence newSequence() {
  return deq_new();
}

// Adds a pipeline to the end of the sequence
extern void addSequence(Sequence sequence, Pipeline pipeline) {
  deq_tail_put(sequence, pipeline);
}

// Frees memory allocated for the sequence and its pipelines
extern void freeSequence(Sequence sequence) {
  deq_del(sequence, freePipeline); // freePipeline is assumed to be defined elsewhere
}

// Executes each pipeline in the sequence until the end of the sequence is reached or an end-of-file condition is encountered
extern void execSequence(Sequence sequence, Jobs jobs, int *eof) {
  while (deq_len(sequence) && !*eof) // Loop through the sequence until it's empty or EOF is encountered
    execPipeline(deq_head_get(sequence), jobs, eof); // Execute the pipeline at the head of the sequence
  freeSequence(sequence); // Free memory allocated for the sequence and its pipelines
}
