/*
   Author: Anton Leslie
   Description: This file implements a simple game called "Lawn Mole Whacking". 
                It uses FLTK (Fast Light Toolkit) library for GUI components. 
                The game involves moles popping up randomly on a lawn (window) and the player 
                has to "whack" them by clicking on them before they disappear. 
                The moles appear and disappear after random intervals of time.
*/

#include <stdio.h> // Standard input-output functions
#include <stdlib.h> // Standard library functions
#include <unistd.h> // Standard symbolic constants and types
#include <pthread.h> // POSIX threads
#include <sys/syscall.h> // System call declarations

#include <FL/Fl.H> // FLTK library main header
#include <FL/Fl_Window.H> // FLTK window class
#include <FL/Fl_Box.H> // FLTK box class

#define LAWNIMP
#include "lawnimp.h" // Header file defining interface functions
#undef LAWNIMP

using namespace std;

static void tsleep(int secs) {
  pthread_mutex_t mutex;
  pthread_cond_t cv;
  pthread_mutex_init(&mutex,0); // Initialize mutex
  pthread_cond_init(&cv,0); // Initialize condition variable

  struct timespec t;
  clock_gettime(CLOCK_REALTIME,&t);
  t.tv_sec+=secs;
  pthread_mutex_lock(&mutex);
  pthread_cond_timedwait(&cv,&mutex,&t); // Wait for condition variable with timeout
  pthread_mutex_unlock(&mutex);

  pthread_mutex_destroy(&mutex); // Destroy mutex
  pthread_cond_destroy(&cv); // Destroy condition variable
}

static int text() {
  char* v=getenv("DISPLAY");
  return !(v && *v); // Check if DISPLAY environment variable is set
}

#define gettid() ((pid_t)syscall(SYS_gettid)) // Macro to get thread ID
#define WR(X,Y,MSG) printf("(%d,%d) %d %s %s\n",X,Y, gettid(), __func__,MSG) // Macro for debug logging
#define WR0 { WR(0,0,""); return 0; } // Macro for debug logging and returning 0

// Function to create a new window representing the lawn
extern LINKAGE void* lawnimp_new(int lawnsize, int molesize) {
  if (text()) WR0; // Check if running in a text-only environment
  int size=lawnsize*molesize;
  Fl_Window* w=new Fl_Window(size,size); // Create FLTK window
  w->end();
  w->show(); // Show window
  Fl::lock(); // Lock FLTK
  return w;
}

// Function to start running the FLTK event loop
extern LINKAGE void* lawnimp_run(LawnRep l) {
  if (text()) WR0; // Check if running in a text-only environment
  Fl::run(); // Start FLTK event loop
  return 0;
}

// Function to create a new mole on the lawn
extern LINKAGE void* lawnimp_mole(MoleRep m) {
  if (text()) {
    WR(m->x,m->y,"creating");
    tsleep(m->vim0); // Sleep for a certain interval
    WR(m->x,m->y,"created");
    return 0;
  }
  LawnRep l=(LawnRep)m->lawn;
  Fl_Window* w=(Fl_Window*)l->window;
  tsleep(m->vim0); // Sleep for a certain interval
  Fl::lock();
  w->begin();
  Fl_Box* b=new Fl_Box(m->x,m->y,m->size,m->size);
  b->box(FL_OVAL_BOX);
  b->color(FL_GREEN);
  w->end();
  w->redraw();
  Fl::check();
  Fl::unlock();
  return b;
}

// Function to "whack" a mole
extern LINKAGE void lawnimp_whack(MoleRep m) {
  if (text()) {
    WR(m->x,m->y,"whacking");
    tsleep(m->vim1); // Sleep for a certain interval
    WR(m->x,m->y,"whacked");
    tsleep(m->vim2); // Sleep for a certain interval
    WR(m->x,m->y,"expired");
    return;
  }
  LawnRep l=(LawnRep)m->lawn;
  Fl_Window* w=(Fl_Window*)l->window;
  Fl_Box* b=(Fl_Box*)m->box;
  tsleep(m->vim1); // Sleep for a certain interval
  Fl::lock();
  b->color(FL_RED);
  w->redraw();
  Fl::check();
  Fl::unlock();
  tsleep(m->vim2); // Sleep for a certain interval
  Fl::lock();
  b->hide();
  w->redraw();
  Fl::check();
  Fl::unlock();
  w->remove(b);
  delete b;
}

// Function to free memory associated with the window
extern LINKAGE void lawnimp_free(void* w) {
  delete (Fl_Window*)w;
}
