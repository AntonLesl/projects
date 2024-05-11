/*
   Author: Anton Leslie
   Description: This file implements a deque (double-ended queue) data structure using linked lists. 
                It provides functions for creating a new deque, getting its length, adding and removing elements 
                from both ends (head and tail), accessing elements at specific indices, 
                searching for and removing specific elements, mapping a function over all elements, 
                deleting the deque along with its elements, and converting the deque to a string representation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

// indices and size of array of node pointers
typedef enum {Head,Tail,Ends} End;

// Node structure for the linked list
typedef struct Node {
  struct Node *np[Ends];   // next/prev neighbors
  Data data;
} *Node;

// Representation of the deque
typedef struct {
  Node ht[Ends];      // head/tail nodes
  int len;            // length of the deque
} *Rep;

// Retrieve the representation of the deque
static Rep rep(Deq q) {
  if (!q) ERROR("zero pointer");
  return (Rep)q;
}

// Append data to one of the deque ends (head - tail)
static void put(Rep r, End e, Data d) {
    // Allocate memory for the new node
    Node newNode = (Node)malloc(sizeof(struct Node));
    if (!newNode) ERROR("malloc() failed");
    // Initialize the node's data and pointers
    newNode->data = d;
    newNode->np[Head] = newNode->np[Tail] = NULL;

    // If the deque is empty, the new node becomes both head and tail
    if (!r->ht[Head]) {
        r->ht[Head] = r->ht[Tail] = newNode;
    } else {
        // Insert at head
        if (e == Head) {
            newNode->np[Tail] = r->ht[Head];
            r->ht[Head]->np[Head] = newNode;
            r->ht[Head] = newNode;
        // Insert at tail
        } else {
            newNode->np[Head] = r->ht[Tail];
            r->ht[Tail]->np[Tail] = newNode;
            r->ht[Tail] = newNode;
        }
    }
    // Increment the length of the deque
    r->len++;
}

// Returns the ith data from one of the deque ends
static Data ith(Rep r, End e, int i)  {
    if (i < 0 || i >= r->len) ERROR("Index out of range");
    // Start from head or tail and move forward
    Node curr = (e == Head) ? r->ht[Head] : r->ht[Tail];
    while (i--) {
        curr = (e == Head) ? curr->np[Tail] : curr->np[Head];
    }
    // Return data at the specified index
    return curr->data;
}

// Retrieves and removes data from one of the deque ends
static Data get(Rep r, End e)         {
    if (!r->ht[Head]) ERROR("Empty deque");

    Node toRemove;
    Data d;

    if (e == Head) {
        // Get data from head
        toRemove = r->ht[Head];
        r->ht[Head] = toRemove->np[Tail];
        if (r->ht[Head]) r->ht[Head]->np[Head] = NULL;
        else r->ht[Tail] = NULL;
    } else {
        // Get data from tail
        toRemove = r->ht[Tail];
        r->ht[Tail] = toRemove->np[Head];
        if (r->ht[Tail]) r->ht[Tail]->np[Tail] = NULL;
        else r->ht[Head] = NULL;
    }

    d = toRemove->data;
    free(toRemove);
    r->len--;
    return d;
}

// Searches and removes the data equal to the given data from the deque
static Data rem(Rep r, End e, Data d) {
    // Start with head or tail of the list depending on e value
    Node curr = r->ht[e];
    // Look through the list until found or end of the list
    while (curr && curr->data != d) {
        curr = (e == Head) ? curr->np[Tail] : curr->np[Head];
    }
    // If not found, return NULL
    if (!curr) return NULL;
    // Update pointer of the previous node to the current node
    if (curr->np[Head]) curr->np[Head]->np[Tail] = curr->np[Tail];
    else r->ht[Head] = curr->np[Tail];

    if (curr->np[Tail]) curr->np[Tail]->np[Head] = curr->np[Head];
    else r->ht[Tail] = curr->np[Head];

    // Save current node data and return data
    Data data = curr->data;
    free(curr);
    r->len--;
    return data;
}

// Create a new deque
extern Deq deq_new() {
  Rep r=(Rep)malloc(sizeof(*r));
  if (!r) ERROR("malloc() failed");
  r->ht[Head]=0;
  r->ht[Tail]=0;
  r->len=0;
  return r;
}

// Get the length of the deque
extern int deq_len(Deq q) { return rep(q)->len; }

// Add data to the head of the deque
extern void deq_head_put(Deq q, Data d) {        put(rep(q),Head,d); }
// Get data from the head of the deque
extern Data deq_head_get(Deq q)         { return get(rep(q),Head); }
// Get the ith data from the head of the deque
extern Data deq_head_ith(Deq q, int i)  { return ith(rep(q),Head,i); }
// Remove data from the head of the deque
extern Data deq_head_rem(Deq q, Data d) { return rem(rep(q),Head,d); }

// Add data to the tail of the deque
extern void deq_tail_put(Deq q, Data d) {        put(rep(q),Tail,d); }
// Get data from the tail of the deque
extern Data deq_tail_get(Deq q)         { return get(rep(q),Tail); }
// Get the ith data from the tail of the deque
extern Data deq_tail_ith(Deq q, int i)  { return ith(rep(q),Tail,i); }
// Remove data from the tail of the deque
extern Data deq_tail_rem(Deq q, Data d) { return rem(rep(q),Tail,d); }

// Map a function over all elements of the deque
extern void deq_map(Deq q, DeqMapF f) {
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail])
    f(n->data);
}

// Delete the deque along with its elements
extern void deq_del(Deq q, DeqMapF f) {
  if (f) deq_map(q,f);
  Node curr=rep(q)->ht[Head];
  while (curr) {
    Node next=curr->np[Tail];
    free(curr);
    curr=next;
  }
  free(q);
}

// Convert the deque to a string representation
extern Str deq_str(Deq q, DeqStrF f) {
  char *s=strdup("");
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail]) {
    char *d=f ? f(n->data) : n->data;
    char *t; asprintf(&t,"%s%s%s",s,(*s ? " " : ""),d);
    free(s); s=t;
    if (f) free(d);
  }
  return s;
}
