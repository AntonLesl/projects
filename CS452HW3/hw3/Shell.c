/*
   Author: Anton Leslie
   Description: This program is a simple shell that reads input from the user, parses it, 
   and interprets the commands accordingly. It supports job management and command history. 
   If input is from a terminal, it provides a command prompt, supports command line editing, 
   and saves command history to a file. Otherwise, it reads commands from stdin and suppresses terminal-specific features. 
   The main function initializes necessary data structures, reads input in a loop, parses each line into a tree structure representing the command, 
   interprets the command tree, and repeats until end-of-file or an exit command is encountered. 
   After processing, it saves command history (if applicable) and frees allocated memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "Jobs.h"
#include "Parser.h"
#include "Interpreter.h"
#include "error.h"

extern void freestateCommand();

int main() {
  int eof=0;
  Jobs jobs=newJobs();
  char *prompt=0;

  // Check if input is from a terminal
  if (isatty(fileno(stdin))) {
    // Setup command history
    using_history();
    read_history(".history");
    prompt="$ "; // Set prompt for terminal input
  } else {
    // Bind tab key for command line editing
    rl_bind_key('\t',rl_insert);
    rl_outstream=fopen("/dev/null","w"); // Redirect output to /dev/null
  }
  
  while (!eof) {
    // Read input line
    char *line=readline(prompt);
    if (!line)
      break;
    if (*line)
      add_history(line); // Add non-empty lines to history
    // Parse input into a command tree
    Tree tree=parseTree(line);
    free(line); // Free allocated memory for input line
    // Interpret command tree
    interpretTree(tree,&eof,jobs);
    freeTree(tree); // Free memory allocated for command tree
  }

  // Save command history and clean up
  if (isatty(fileno(stdin))) {
    write_history(".history"); // Save command history to file
    rl_clear_history(); // Clear command history
  } else {
    fclose(rl_outstream); // Close output stream
  }
  // Free allocated memory
  freestateCommand();
  return 0;
}
