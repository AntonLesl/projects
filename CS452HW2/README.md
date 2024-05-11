CS 452/552 (S24) - Homework #2: Memory Hole

Author: Anton Leslie

Description
This assignment involves the development of a memory allocator utilizing the Buddy System scheme. Similar to the kmalloc() allocator in the Linux kernel or the malloc() allocator in the C library, your allocator will operate in user space, obtaining memory through mmap(). The main objective is to implement key functionalities like allocation, deallocation, size retrieval, and debugging information output.

Compilation:

How to Run
Navigate to the CS452HW2/ directory.

cd hw2/
then run the commands below 
Build the program using the make command:
compile the code using this 

gcc -o main main.c balloc.c freelist.c utils.c bbm.c bm.c -lm

valgrind command 

valgrind --leak-check=full --show-leak-kinds=all ./main

creates a ./main run file 
then run it using 

./main

