/*
   File: Shell.c
   Author: Anton Leslie
   Description: This file implements a simple shell program in C. 
   It defines built-in commands such as exit, pwd, cd, and history. 
   The shell supports basic command execution, job control, and command history functionality.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h> // Include GNU History library
#include "Jobs.h"
#include "Command.h"
#include "error.h"

// Structure to represent a command
typedef struct {
  char *file;
  char **argv;
} *CommandRep;

#define MAX_HISTORY_SIZE 100

static char *history[MAX_HISTORY_SIZE];
static int history_count = 0;

// Define a built-in command function signature
#define BIARGS CommandRep r, int *eof, Jobs jobs
#define BINAME(name) bi_##name
#define BIDEFN(name) static void BINAME(name) (BIARGS)
#define BIENTRY(name) {#name,BINAME(name)}

static char *owd=0;
static char *cwd=0;

// Helper function to check arguments for built-in commands
static void builtin_args(CommandRep r, int n) {
  char **argv=r->argv;
  for (n++; *argv++; n--);
  if (n)
    ERROR("wrong number of arguments to builtin command"); // warn
}

// Implementation of the exit built-in command
BIDEFN(exit) {
    builtin_args(r,0);
    if (!isEmptyJobs(jobs)) {
        printf("Waiting for background jobs to finish...\n");
        waitJobs(jobs);
    }
    *eof=1; // Set EOF flag to exit the shell
}

// Implementation of the pwd built-in command
BIDEFN(pwd) {
    builtin_args(r,0);
    char *cwd = getcwd(NULL, 0);
    if (!cwd) {
        perror("getcwd() failed");
    } else {
        printf("%s\n", cwd);
        free(cwd); // Free dynamically allocated memory
    }
}

// Implementation of the cd built-in command
BIDEFN(cd) {
    if (r->argv[1] == NULL) {
        printf("cd: missing argument\n");
        return;
    }
    builtin_args(r,1);
    
    char *prevDir = getcwd(NULL, 0); // Get current directory before changing
    
    if (strcmp(r->argv[1],"-")==0) {
        if (owd == NULL) {
            printf("cd: no previous directory stored\n");
            return;
        }
        char *twd = cwd;
        cwd = owd;
        owd = twd;
    } else {
        if (owd) free(owd);
        owd = strdup(prevDir); // Store previous directory
        cwd = strdup(r->argv[1]);
    }
    
    if (!cwd || chdir(cwd) != 0) {
        perror("chdir() failed");
    }
    
    free(prevDir); // Free memory allocated by getcwd
}

// Implementation of the history built-in command
BIDEFN(history) {
    builtin_args(r,0);
    printf("Command History:\n");
    for (int i = history_base; i < history_length; i++) {
        printf("%d: %s\n", i + 1, history_get(i)->line);
    }
}

// Check if a command is a built-in command and execute it if so
static int builtin(BIARGS) {
  typedef struct {
    char *s;
    void (*f)(BIARGS);
  } Builtin;
  static const Builtin builtins[]={
    BIENTRY(exit),
    BIENTRY(pwd),
    BIENTRY(cd),
    BIENTRY(history), // Add history command entry
    {0,0}
  };
  int i;
  for (i=0; builtins[i].s; i++)
    if (!strcmp(r->file,builtins[i].s)) {
      builtins[i].f(r,eof,jobs);
      return 1;
    }
  return 0;
}

// Parse command line arguments and return an array of arguments
static char **getargs(T_words words) {
  int n=0;
  T_words p=words;
  while (p) {
    p=p->words;
    n++;
  }
  char **argv=(char **)malloc(sizeof(char *)*(n+1));
  if (!argv)
    ERROR("malloc() failed");
  p=words;
  int i=0;
  while (p) {
    argv[i++]=strdup(p->word->s);
    p=p->words;
  }
  argv[i]=0;
  return argv;
}

// Create a new command from parsed arguments
extern Command newCommand(T_words words) {
  CommandRep r=(CommandRep)malloc(sizeof(*r));
  if (!r)
    ERROR("malloc() failed");
  r->argv=getargs(words);
  r->file=r->argv[0];

  // Update history
  if (history_count < MAX_HISTORY_SIZE) {
    history[history_count++] = strdup(r->file);
  } else {
    free(history[0]);
    for (int i = 0; i < MAX_HISTORY_SIZE - 1; i++) {
      history[i] = history[i + 1];
    }
    history[MAX_HISTORY_SIZE - 1] = strdup(r->file);
  }

  return r;
}

// Execute a command
static void child(CommandRep r, int fg) {
  int eof=0;
  Jobs jobs=newJobs();
  if (builtin(r,&eof,jobs))
    return;
  execvp(r->argv[0],r->argv);
  ERROR("execvp() failed");
  exit(0);
}

// Execute a command and handle job control
extern void execCommand(Command command, Pipeline pipeline, Jobs jobs,
            int *jobbed, int *eof, int fg) {
  CommandRep r=command;
  if (fg && builtin(r,eof,jobs))
    return;
  if (!*jobbed) {
    *jobbed=1;
    addJobs(jobs,pipeline);
  }
  int pid=fork();
  if (pid==-1)
    ERROR("fork() failed");
  if (pid==0)
    child(r,fg);
}

// Free memory allocated for a command
extern void freeCommand(Command command) {
  CommandRep r=command;
  char **argv=r->argv;
  while (*argv)
    free(*argv++);
  free(r->argv);
  free(r);
}

// Free memory allocated for the shell state
extern void freestateCommand() {
  if (cwd) free(cwd);
  if (owd) free(owd);
  for (int i = 0; i < history_count; i++) {
    free(history[i]);
  }
}
