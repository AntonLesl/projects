/*
    CS 331 Computer Security and Information Assurance
    Homework Assignment 2


    The change from using scanf() to fgets() in the vulnerable() function is effective in preventing buffer overflow attacks 
    because fgets() takes the size of the buffer as an argument, which limits the number of characters read from stdin 
    to the size of the buffer minus one for the null terminator. 

In contrast, scanf() does not limit the number of characters read and can cause buffer overflow 
if the input is larger than the size of the buffer. By using fgets(), 
the program reads input up to the size of the buffer and discards any extra characters, 
preventing the overflow of the buffer and the corruption of the stack.
*/
#include <stdio.h>
#include <string.h>

char globalBuf[100];

void vulnerable(int i)
{
   int whatEver = 987654321;
   double notNeeded = 1.23456789;
   char buf[26];

   printf("\n  Entering our vulnerable function.\n");
   printf("    Please enter a string: ");

   fgets(buf, sizeof(buf), stdin);

   strncpy(globalBuf, buf, 99);

   printf("\n whatEver is: %d", whatEver);
 
   printf("\n  Leaving our vulnerable function.\n");
   return;
}


int main()
{
   int n = 1;

   printf("Calling our vulnerable function.\n");
   vulnerable(n);

   printf("n = %d\n", n);

   if ( n )
   {
      printf("\nHere is what is in the buffer\n");
      printf("%s", globalBuf);
      printf("\nThat's it.\n");
   }
   else
      printf("We really shouldn't be able to ever see this output.\n");

   return 0;
}
