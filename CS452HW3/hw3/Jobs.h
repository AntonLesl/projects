#ifndef JOBS_H
#define JOBS_H

#include "deq.h"

typedef void* Jobs;

extern Jobs newJobs();
extern void addJobs(Jobs jobs, void* pipeline);
extern int sizeJobs(Jobs jobs);
extern void freeJobs(Jobs jobs);

extern int isEmptyJobs(Jobs jobs);
extern void waitJobs(Jobs jobs);
extern void manageJobs(Jobs jobs);

#endif /* JOBS_H */
