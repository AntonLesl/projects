/*
 * File: Jobs.c
 * Author: Anton Leslie
 * Description: This file contains functions to manage a list of background jobs.
 *              It provides functionality to add jobs to the list, get the size
 *              of the list, wait for the completion of all jobs, and manage the
 *              completion status of background processes in the job list.
 */

#include "Jobs.h"
#include "deq.h"
#include "error.h"
#include "Pipeline.h" // Include Pipeline.h for Pipeline type

#include <sys/wait.h>

// Define the Pipeline type if it's not already defined in Jobs.h
typedef void* Pipeline;

// Declare getPIDS function if it's not declared in Jobs.h
extern Deq getPIDS(Pipeline pipeline);

// Create a new list of jobs
extern Jobs newJobs() {
    return deq_new();
}

// Add a new job to the list
extern void addJobs(Jobs jobs, Pipeline pipeline) {
    if (jobs && pipeline) { // Check for NULL pointers
        deq_tail_put(jobs, pipeline);
    }
}

// Get the size of the list of jobs
extern int sizeJobs(Jobs jobs) {
    if (jobs) { // Check for NULL pointer
        return deq_len(jobs);
    }
    return 0;
}

// Free the memory allocated for the list of jobs
extern void freeJobs(Jobs jobs) {
    if (jobs) { // Check for NULL pointer
        deq_del(jobs, NULL); // No cleanup function needed for Jobs
    }
}

// Check if the list of jobs is empty
extern int isEmptyJobs(Jobs jobs) {
    if (sizeJobs(jobs) == 0) {
        return 1; // Jobs list is empty
    } else {
        return 0; // Jobs list is not empty
    }
}

// Wait for the completion of all jobs in the list
extern void waitJobs(Jobs jobs) {
    if (!jobs)
        return; // Check for NULL pointer

    // Iterate over all jobs
    for (int i = sizeJobs(jobs) - 1; i >= 0; i--) {
        Pipeline pipeline = deq_head_ith(jobs, i);

        // Get the PID queue for the current pipeline
        Deq pids = getPIDS(pipeline);

        if (!pids)
            continue; // Check for NULL pointer

        int sizePIDS = deq_len(pids); // Get the size of PID queue

        // Wait for each process in the PID queue
        for (int j = sizePIDS - 1; j >= 0; j--) {
            pid_t pid = (pid_t)(long)deq_head_ith(pids, j); // Corrected casting
            int status;
            waitpid(pid, &status, 0); // Wait for the process to finish
        }
    }
}

// Manage the completion status of background processes in the job list
extern void manageJobs(Jobs jobs) {
    if (!jobs) return; // Check for NULL pointer

    for (int i = sizeJobs(jobs) - 1; i >= 0; i--) {
        Pipeline pipeline = deq_head_ith(jobs, i);

        if (!pipeline) continue; // Check for NULL pointer

        Deq pids = getPIDS(pipeline); // Get the PID queue

        if (!pids) continue; // Check for NULL pointer

        int sizePIDS = deq_len(pids); // Get the size of PID queue

        for (int j = sizePIDS - 1; j >= 0; j--) {
            pid_t pid = (pid_t)(long)deq_head_ith(pids, j); // Corrected casting
            int status;
            pid_t result = waitpid(pid, &status, WNOHANG);
            if (result == -1) {
                // Handle waitpid error
                perror("waitpid");
            } else if (result > 0) {
                // Process has terminated
                deq_head_rem(pids, deq_head_ith(pids, j));
            }
        }

        // If the PID queue is empty after removing terminated processes, free the pipeline
        if (deq_len(pids) == 0) {
            // Remove the pipeline from the jobs list
            for (int k = sizeJobs(jobs) - 1; k >= 0; k--) {
                if (deq_head_ith(jobs, k) == pipeline) {
                    deq_head_rem(jobs, pipeline);
                    freePipeline(pipeline);
                    break; // Break out of the loop after freeing the pipeline
                }
            }
        }
    }
}
