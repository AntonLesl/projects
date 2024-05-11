/*
 * File: Parser.c
 * Author: Anton Leslie
 * Description: This file contains functions for parsing a sequence of commands and constructing a tree structure representing the parsed input.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser.h"
#include "Tree.h"
#include "Scanner.h"
#include "error.h"
// Scanner object for input
static Scanner scan;

// Macro to generate error messages
#undef ERROR
#define ERROR(s) ERRORLOC(__FILE__,__LINE__,"error","%s (pos: %d)",s,posScanner(scan))

// Function prototypes
static char *next()       { return nextScanner(scan); }
static char *curr()       { return currScanner(scan); }
static int   cmp(char *s) { return cmpScanner(scan,s); }
static int   eat(char *s) { return eatScanner(scan,s); }

// Parser functions
static T_word p_word();
static T_words p_words();
static T_command p_command();
static T_pipeline p_pipeline();
static T_sequence p_sequence();

// Parse a single word
static T_word p_word() {
  char *s = curr();
  if (!s)
    return NULL;
  T_word word = new_word();
  word->s = strdup(s);
  next();
  return word;
}

// Parse multiple words
static T_words p_words() {
  T_word word = p_word();
  if (!word)
    return NULL;
  T_words words = new_words();
  words->word = word;
    // If the next token is a command separator, return
  if (cmp("|") || cmp("&") || cmp(";"))
    return words;
  words->words = p_words();// Parse the remaining words
  return words;
}

// Parse a command
static T_command p_command() {
  T_words words = p_words(); // Parse words
  if (!words)
    return NULL;
  T_command command = new_command();
  command->words = words;
  return command;
}

// Parse a pipeline
static T_pipeline p_pipeline() {
  T_command command = p_command(); // Parse a command
  if (!command)
    return NULL;
  T_pipeline pipeline = new_pipeline();
  pipeline->command = command;
  // If the next token is a pipe, parse the next pipeline
  if (eat("|"))
    pipeline->pipeline = p_pipeline();
  return pipeline;
}

// Parse a sequence of commands
static T_sequence p_sequence() {
  T_pipeline pipeline = p_pipeline(); // Parse a pipeline
  if (!pipeline)
    return NULL;
  T_sequence sequence = new_sequence();
  sequence->pipeline = pipeline;
  // If the next token is a background or sequential operator, parse the next sequence
  if (eat("&")) {
    sequence->op = "&";
    sequence->sequence = p_sequence();
  }
  if (eat(";")) {
    sequence->op = ";";
    sequence->sequence = p_sequence();
  }
  return sequence;
}

// Parse input and construct the parse tree
extern Tree parseTree(char *s) {
  scan = newScanner(s); // Create a scanner for the input string
  Tree tree = p_sequence(); // Parse the input
  if (curr())
    ERROR("extra characters at end of input"); // Check for extra characters
  freeScanner(scan); // Free the scanner
  return tree;
}

// Free memory allocated for a word
static void f_word(T_word t) {
  if (!t)
    return;
  if (t->s)
    free(t->s); // Free the string
  free(t);
}

// Free memory allocated for words
static void f_words(T_words t) {
  if (!t)
    return;
  f_word(t->word);
  f_words(t->words);
  free(t);
}

// Free memory allocated for a command
static void f_command(T_command t) {
  if (!t)
    return;
  f_words(t->words);
  free(t);
}

// Free memory allocated for a pipeline
static void f_pipeline(T_pipeline t) {
  if (!t)
    return;
  f_command(t->command);
  f_pipeline(t->pipeline);
  free(t);
}

// Free memory allocated for a sequence of commands
static void f_sequence(T_sequence t) {
  if (!t)
    return;
  f_pipeline(t->pipeline);
  f_sequence(t->sequence);
  free(t);
}

// Free memory allocated for the parse tree
extern void freeTree(Tree t) {
  f_sequence(t); // Start freeing from the root sequence
}