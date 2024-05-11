/*
 * This code defines a doubly-ended queue (deque) data structure and provides operations to manipulate it.
 * The deque supports adding and retrieving elements from both the head and tail, searching and removing
 * specific elements, getting the length, applying a function to each element, and converting the deque to a string.
 *
 * Author: Anton Leslie
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

// Definition of the doubly-ended queue (deque) data structure
typedef enum {Head, Tail, Ends} End;

typedef struct Node {
    struct Node *np[Ends];  // next/prev neighbors
    Data data;
} *Node;

typedef struct {
    Node ht[Ends];  // head/tail nodes
    int len;        // length of the deque
} *Rep;

// Function to get the representation of the deque
static Rep rep(Deq q) {
    if (!q) ERROR("zero pointer");
    return (Rep)q;
}

// Function to append data to one of the deque ends (head or tail)
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

// Function to return the ith data from one of the deque ends
static Data ith(Rep r, End e, int i) {
    if (i < 0 || i >= r->len) ERROR("Index out of range");
    
    // Start from head and move forward to the specified index
    Node curr = (e == Head) ? r->ht[Head] : r->ht[Tail];
    while (i--) {
        curr = (e == Head) ? curr->np[Tail] : curr->np[Head];
    }
    // Return the data at the specified index
    return curr->data;
}

// Function to retrieve and remove data from one of the deque ends
static Data get(Rep r, End e) {
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

// Function to search and remove data equal to the given data from the deque
static Data rem(Rep r, End e, Data d) {
    // Start with the head or tail of the list depending on the 'e' value
    Node curr = r->ht[e];

    // Look through the list until found or end of list
    while (curr && curr->data != d) {
        curr = (e == Head) ? curr->np[Tail] : curr->np[Head];
    }

    // If not found, return NULL
    if (!curr) return NULL;

    // Update the pointer of the previous node to the current node
    if (curr->np[Head]) curr->np[Head]->np[Tail] = curr->np[Tail];
    else r->ht[Head] = curr->np[Tail];

    if (curr->np[Tail]) curr->np[Tail]->np[Head] = curr->np[Head];
    else r->ht[Tail] = curr->np[Head];

    // Save the current node data and return the data
    Data data = curr->data;
    free(curr);
    r->len--;
    return data;
}

// Function to create a new deque
extern Deq deq_new() {
    Rep r = (Rep)malloc(sizeof(*r));
    if (!r) ERROR("malloc() failed");
    r->ht[Head] = 0;
    r->ht[Tail] = 0;
    r->len = 0;
    return r;
}

// Function to get the length of the deque
extern int deq_len(Deq q) {
    return rep(q)->len;
}

// Functions to manipulate the deque from the head
extern void deq_head_put(Deq q, Data d) {
    put(rep(q), Head, d);
}

extern Data deq_head_get(Deq q) {
    return get(rep(q), Head);
}

extern Data deq_head_ith(Deq q, int i) {
    return ith(rep(q), Head, i);
}

extern Data deq_head_rem(Deq q, Data d) {
    return rem(rep(q), Head, d);
}

// Functions to manipulate the deque from the tail
extern void deq_tail_put(Deq q, Data d) {
    put(rep(q), Tail, d);
}

extern Data deq_tail_get(Deq q) {
    return get(rep(q), Tail);
}

extern Data deq_tail_ith(Deq q, int i) {
    return ith(rep(q), Tail, i);
}

extern Data deq_tail_rem(Deq q, Data d) {
    return rem(rep(q), Tail, d);
}

// Function to apply a function to each element of the deque
extern void deq_map(Deq q, DeqMapF f) {
    for (Node n = rep(q)->ht[Head]; n; n = n->np[Tail])
        f(n->data);
}

// Function to delete the deque, applying a function to each element if provided
extern void deq_del(Deq q, DeqMapF f) {
    if (f) deq_map(q, f);

    Node curr = rep(q)->ht[Head];
    while (curr) {
        Node next = curr->np[Tail];
        free(curr);
        curr = next;
    }
    free(q);
    
}

// Function to convert the deque to a string, applying a function to each element if provided
extern Str deq_str(Deq q, DeqStrF f) {
    char *s = strdup("");
    for (Node n = rep(q)->ht[Head]; n; n = n->np[Tail]) {
        char *d = f ? f(n->data) : n->data;
        char *t;
        asprintf(&t, "%s%s%s", s, (*s ? " " : ""), d);
        free(s);
        s = t;
        if (f) free(d);
    }
    return s;
}
