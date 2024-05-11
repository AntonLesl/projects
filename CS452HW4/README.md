CS 452/552 (S24) - Homework #4: Whack-a-Mole and Race Conditions
Issued: Tuesday, February 27
Due: Tuesday, March 26
Author: Anton Leslie

Purpose
The purpose of this assignment is to learn and practice single-process multi-thread (MT) programming, focusing on the design and implementation of MT-safe functions and data structures. You'll be working on a program that simulates the old arcade game "Whack-a-Mole" graphically.

Compilation:

How to Run
Navigate to the CS452HW4/ directory.

cd hw4/
then run the commands below 

Build the program using the make command:

make 

compile the code using this 

make run or ./wam

valgrind command and results 

[antonleslie@onyx hw4]$ make valgrind
gcc -o deq.o -c deq.c -pthread -g -Wall -MMD -D_GNU_SOURCE
gcc -o mt_queue.o -c mt_queue.c -pthread -g -Wall -MMD -D_GNU_SOURCE
gcc -o main.o -c main.c -pthread -g -Wall -MMD -D_GNU_SOURCE
gcc -o mole.o -c mole.c -pthread -g -Wall -MMD -D_GNU_SOURCE
gcc -o lawn.o -c lawn.c -pthread -g -Wall -MMD -D_GNU_SOURCE
gcc -o thread_utils.o -c thread_utils.c -pthread -g -Wall -MMD -D_GNU_SOURCE
g++ -o lawnimp.o -c lawnimp.cc -pthread -g -Wall -MMD -D_GNU_SOURCE
gcc -o wam deq.o mt_queue.o main.o mole.o lawn.o thread_utils.o lawnimp.o -pthread -lX11 -lfltk -lstdc++ -g
valgrind --leak-check=full --show-leak-kinds=all ./wam 
==1184805== Memcheck, a memory error detector
==1184805== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==1184805== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==1184805== Command: ./wam
==1184805== 
(0,0) 1184805 lawnimp_new 
(0,0) 1184828 lawnimp_run 
(532,74) 1184853 lawnimp_mole creating
(420,581) 1184858 lawnimp_mole creating
(326,136) 1184859 lawnimp_mole creating
(337,586) 1184843 lawnimp_mole creating
(148,22) 1184860 lawnimp_mole creating
(584,444) 1184861 lawnimp_mole creating
(218,395) 1184862 lawnimp_mole creating
(299,122) 1184863 lawnimp_mole creating
(109,86) 1184865 lawnimp_mole creating
(126,177) 1184864 lawnimp_mole creating
(326,136) 1184859 lawnimp_mole created
(337,586) 1184843 lawnimp_mole created
(326,136) 1184867 lawnimp_whack whacking
(337,586) 1184866 lawnimp_whack whacking
(584,444) 1184861 lawnimp_mole created
(584,444) 1184868 lawnimp_whack whacking
(532,74) 1184853 lawnimp_mole created
(532,74) 1184871 lawnimp_whack whacking
(299,122) 1184863 lawnimp_mole created
(299,122) 1184870 lawnimp_whack whacking
(218,395) 1184862 lawnimp_mole created
(218,395) 1184877 lawnimp_whack whacking
(299,122) 1184870 lawnimp_whack whacked
(109,86) 1184865 lawnimp_mole created
(109,86) 1184872 lawnimp_whack whacking
(126,177) 1184864 lawnimp_mole created
(126,177) 1184878 lawnimp_whack whacking
(148,22) 1184860 lawnimp_mole created
(148,22) 1184880 lawnimp_whack whacking
(109,86) 1184872 lawnimp_whack whacked
(532,74) 1184871 lawnimp_whack whacked
(420,581) 1184858 lawnimp_mole created
(420,581) 1184885 lawnimp_whack whacking
(148,22) 1184880 lawnimp_whack whacked
(326,136) 1184867 lawnimp_whack whacked
(584,444) 1184868 lawnimp_whack whacked
(148,22) 1184880 lawnimp_whack expired
(337,586) 1184866 lawnimp_whack whacked
(109,86) 1184872 lawnimp_whack expired
(218,395) 1184877 lawnimp_whack whacked
(337,586) 1184866 lawnimp_whack expired
(126,177) 1184878 lawnimp_whack whacked
(299,122) 1184870 lawnimp_whack expired
(532,74) 1184871 lawnimp_whack expired
(420,581) 1184885 lawnimp_whack whacked
(326,136) 1184867 lawnimp_whack expired
(584,444) 1184868 lawnimp_whack expired
(126,177) 1184878 lawnimp_whack expired
(218,395) 1184877 lawnimp_whack expired
(420,581) 1184885 lawnimp_whack expired
==1184805== 
==1184805== HEAP SUMMARY:
==1184805==     in use at exit: 1,840 bytes in 4 blocks
==1184805==   total heap usage: 57 allocs, 53 frees, 83,452 bytes allocated
==1184805== 
==1184805== 16 bytes in 1 blocks are still reachable in loss record 1 of 4
==1184805==    at 0x4C38913: operator new(unsigned long) (vg_replace_malloc.c:472)
==1184805==    by 0x51E0B9D: Fl_Display_Device::display_device() (in /usr/lib64/libfltk.so.1.3)
==1184805==    by 0x51CFB6C: ??? (in /usr/lib64/libfltk.so.1.3)
==1184805==    by 0x4008F49: call_init.part.0 (dl-init.c:72)
==1184805==    by 0x4009049: call_init (dl-init.c:118)
==1184805==    by 0x4009049: _dl_init (dl-init.c:119)
==1184805==    by 0x401DCE9: ??? (in /usr/lib64/ld-2.28.so)
==1184805== 
==1184805== 40 bytes in 1 blocks are still reachable in loss record 2 of 4
==1184805==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1184805==    by 0x4E7D083: XInitThreads (in /usr/lib64/libX11.so.6.3.0)
==1184805==    by 0x40260E: lawn_new (lawn.c:36)
==1184805==    by 0x402221: main (main.c:38)
==1184805== 
==1184805== 40 bytes in 1 blocks are still reachable in loss record 3 of 4
==1184805==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1184805==    by 0x4E7D09C: XInitThreads (in /usr/lib64/libX11.so.6.3.0)
==1184805==    by 0x40260E: lawn_new (lawn.c:36)
==1184805==    by 0x402221: main (main.c:38)
==1184805== 
==1184805== 1,744 bytes in 1 blocks are still reachable in loss record 4 of 4
==1184805==    at 0x4C38913: operator new(unsigned long) (vg_replace_malloc.c:472)
==1184805==    by 0x51E0B79: Fl_Display_Device::display_device() (in /usr/lib64/libfltk.so.1.3)
==1184805==    by 0x51CFB6C: ??? (in /usr/lib64/libfltk.so.1.3)
==1184805==    by 0x4008F49: call_init.part.0 (dl-init.c:72)
==1184805==    by 0x4009049: call_init (dl-init.c:118)
==1184805==    by 0x4009049: _dl_init (dl-init.c:119)
==1184805==    by 0x401DCE9: ??? (in /usr/lib64/ld-2.28.so)
==1184805== 
==1184805== LEAK SUMMARY:
==1184805==    definitely lost: 0 bytes in 0 blocks
==1184805==    indirectly lost: 0 bytes in 0 blocks
==1184805==      possibly lost: 0 bytes in 0 blocks
==1184805==    still reachable: 1,840 bytes in 4 blocks
==1184805==         suppressed: 0 bytes in 0 blocks
==1184805== 
==1184805== For lists of detected and suppressed errors, rerun with: -s
==1184805== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


creates a ./wam run file 
then run it using 

./wam

