/*
    CS 331 Computer Security and Information Assurance
    Homework Assignment 2


    The following function, vulnerable(), is susceptible
    to a "buffer overflow" attack. If scanf() reads in
    more than 25 characters, then the extra characters
    will overflow the array buf[] and corrupt the stack.
    (Remember that scanf always puts a null character at
    the end of the characters that it reads in. So if scanf
    reads in 25 characters, that plus the null character
    fills the 26 element array buf[].)


    Do not modify this file.
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
   scanf("%s", buf);

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
      printf( globalBuf );
      printf("\nThat's it.\n");
   }
   else
      printf("We really shouldn't be able to ever see this output.\n");

   return 0;
}
