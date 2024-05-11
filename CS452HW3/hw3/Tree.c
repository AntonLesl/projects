/*
 * File: Tree.c
 * Author: Anton Leslie
 * Description: This file contains functions for creating new tree nodes of various types
 *              such as sequences, pipelines, commands, words, and word lists.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tree.h"
#include "error.h"

// Macro for allocating memory for a tree node
#define ALLOC(t) \
  t v=malloc(sizeof(*v)); \
  if (!v) ERROR("malloc() failed"); \
  return memset(v,0,sizeof(*v));

// Function to create a new sequence node
extern T_sequence new_sequence() {ALLOC(T_sequence)}

// Function to create a new pipeline node
extern T_pipeline new_pipeline() {ALLOC(T_pipeline)}

// Function to create a new command node
extern T_command  new_command()  {ALLOC(T_command)}

// Function to create a new words node
extern T_words    new_words()    {ALLOC(T_words)}

// Function to create a new word node
extern T_word     new_word()     {ALLOC(T_word)}
