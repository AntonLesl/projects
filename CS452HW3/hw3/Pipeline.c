/*
 * Pipeline.c
 * Author: Anton Leslie
 * Description: This file contains functions to manage pipelines of commands.
 *              A pipeline represents a sequence of commands that are executed together,
 *              with each command's output feeding into the next command's input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "Pipeline.h"
#include "deq.h"
#include "error.h"

// Define PipelineRep structure
typedef struct {
    Deq processes;  // Commands in the pipeline
    Deq pids;       // Process IDs associated with the pipeline
    int fg;         // Flag indicating whether the pipeline is foreground or background
} *PipelineRep;

// Create a new pipeline
extern Pipeline newPipeline(int fg) {
    PipelineRep r = (PipelineRep)malloc(sizeof(*r));
    if (!r)
        ERROR("malloc() failed");
    r->processes = deq_new();
    r->pids = deq_new();
    r->fg = fg;
    return r;
}

// Get the PID queue associated with the pipeline
extern Deq getPIDS(Pipeline pipeline) {
    PipelineRep r = pipeline;
    return r->pids;
}

// Add a PID to the PID queue of the pipeline
extern void addPipePID(Pipeline pipeline, long pid) {
    PipelineRep r = pipeline;
    deq_head_put(r->pids, (Data)pid);
}

// Get and remove a PID from the PID queue of the pipeline
extern Data getPipePID(Pipeline pipeline) {
    PipelineRep r = pipeline;
    return deq_head_get(r->pids);
}

// Get the number of PIDs in the PID queue of the pipeline
extern int sizePipePIDS(Pipeline pipeline) {
    PipelineRep r = pipeline;
    return deq_len(r->pids);
}

// Add a command to the pipeline
extern void addPipeline(Pipeline pipeline, Command command) {
    PipelineRep r = (PipelineRep)pipeline;
    deq_tail_put(r->processes, command);
}

// Get the number of commands in the pipeline
extern int sizePipeline(Pipeline pipeline) {
    PipelineRep r = (PipelineRep)pipeline;
    return deq_len(r->processes);
}

// Execute the commands in the pipeline
static void execute(Pipeline pipeline, Jobs jobs, int *jobbed, int *eof) {
    PipelineRep r = (PipelineRep)pipeline;

    // Execute each command in the pipeline
    for (int i = 0; i < sizePipeline(r) && !*eof; i++) {
        Command cmd = deq_head_ith(r->processes, i);
        execCommand(cmd, pipeline, jobs, jobbed, eof, r->fg);
    }

    // If the pipeline has multiple commands and it's not a foreground job, wait for all processes to complete
    if (sizePipeline(r) > 1 && !(r->fg)) {
        while (sizePipePIDS(pipeline) > 0) {
            pid_t pid = (long)getPipePID(pipeline);
            waitpid(pid, NULL, 0);
        }
    }
}

// Execute the pipeline
extern void execPipeline(Pipeline pipeline, Jobs jobs, int *eof) {
    int jobbed = 0;
    execute(pipeline, jobs, &jobbed, eof);

    // If the pipeline is not a foreground job or it's not jobbed, remove it from the jobs list and free resources
    if (!jobbed || (sizePipePIDS(pipeline) == 0)) {
        // Remove the pipeline from the jobs list
        for (int i = 0; i < sizeJobs(jobs); i++) {
            if (deq_head_ith(jobs, i) == pipeline) {
                deq_head_rem(jobs, pipeline);
                freePipeline(pipeline); // Free the pipeline
                break; // Exit the loop once the pipeline is removed
            }
        }
    }
}

// Free the resources associated with the pipeline
extern void freePipeline(Pipeline pipeline) {
    PipelineRep r = (PipelineRep)pipeline;
    if (r) {
        deq_del(r->pids, NULL); // Delete the PID queue without cleanup
        deq_del(r->processes, NULL); // Delete the command queue without cleanup
        free(r); // Free the pipeline structure
    }
}
