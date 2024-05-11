CS 452/552 (S24) - Homework #3: Execution Integrity
Issued: Tuesday, February 6
Due: Tuesday, February 27

Author: Anton Leslie

Description
This assignment asks you to learn about and practice multiprocess programming, including the design and implementation of a simple Unix shell. It will support sequences, pipelines, and I/O redirection. CS 552 students will add compound commands, subshells, and job control (e.g., fg and bg).

Compilation:

How to Run

Navigate to the CS452HW3/ directory.

cd hw3/

then run the commands below 

Build the program using the make command:

make 

compile the code using this :

make run 

compile the test using this :

make test

valgrind command 

make valgrind

valgrind results:

[antonleslie@onyx hw3]$ make valgrind
valgrind --leak-check=full --show-leak-kinds=all ./shell 
==1312922== Memcheck, a memory error detector
==1312922== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==1312922== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==1312922== Command: ./shell
==1312922== 
$ ls
Command.c    grammar.txt    Parser.c    Scanner.d   Shell.o
Command.d    Interpreter.c  Parser.d    Scanner.h   Test
Command.h    Interpreter.d  Parser.h    Scanner.o   Tree.c
Command.o    Interpreter.h  Parser.o    Sequence.c  Tree.d
deq.c        Interpreter.o  Pipeline.c  Sequence.d  Tree.h
deq.d        Jobs.c         Pipeline.d  Sequence.h  Tree.o
deq.h        Jobs.d         Pipeline.h  Sequence.o  try
deq.o        Jobs.h         Pipeline.o  shell       vg
error.h      Jobs.o         rl.supp     Shell.c
GNUmakefile  libdeq.so      Scanner.c   Shell.d
$ cd ..
$ pwd
/home/ANTONLESLIE/CS452HW3
$ cd -
$ ls
$ Command.c    grammar.txt    Parser.c  Scanner.d   Shell.o
Command.d    Interpreter.c  Parser.d    Scanner.h   Test
Command.h    Interpreter.d  Parser.h    Scanner.o   Tree.c
Command.o    Interpreter.h  Parser.o    Sequence.c  Tree.d
deq.c        Interpreter.o  Pipeline.c  Sequence.d  Tree.h
deq.d        Jobs.c         Pipeline.d  Sequence.h  Tree.o
deq.h        Jobs.d         Pipeline.h  Sequence.o  try
deq.o        Jobs.h         Pipeline.o  shell       vg
error.h      Jobs.o         rl.supp     Shell.c
GNUmakefile  libdeq.so      Scanner.c   Shell.d
pwd
/home/ANTONLESLIE/CS452HW3/hw3
$ history
Command History:
2: ls
3: exit
4: ls
5: exit
6: ls
7: cd ..
8: pwd
9: cd -
10: ls
11: pwd
$ exit
==1312922== 
==1312922== HEAP SUMMARY:
==1312922==     in use at exit: 140,252 bytes in 247 blocks
==1312922==   total heap usage: 592 allocs, 345 frees, 185,289 bytes allocated
==1312922== 
==1312922== 3 bytes in 1 blocks are still reachable in loss record 1 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E61347: rl_set_prompt (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E62735: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 3 bytes in 1 blocks are still reachable in loss record 2 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E716E3: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E71CD5: rl_expand_prompt (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6136B: rl_set_prompt (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E62735: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 8 bytes in 1 blocks are still reachable in loss record 3 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x558F67D: strdup (in /usr/lib64/libc-2.28.so)
==1312922==    by 0x52DE24D: _nc_trim_sgr0 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7451: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 13 bytes in 1 blocks are still reachable in loss record 4 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6F0D4: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E62521: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 14 bytes in 1 blocks are still reachable in loss record 5 of 55
==1312922==    at 0x4C3D3D7: realloc (vg_replace_malloc.c:1649)
==1312922==    by 0x52D4286: _nc_doalloc (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D8BD9: tparm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDFC4: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DE23F: _nc_trim_sgr0 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7451: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 15 bytes in 1 blocks are still reachable in loss record 6 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x558F67D: strdup (in /usr/lib64/libc-2.28.so)
==1312922==    by 0x52D6DAD: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 16 bytes in 1 blocks are still reachable in loss record 7 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E625E4: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 18 bytes in 1 blocks are still reachable in loss record 8 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x558F67D: strdup (in /usr/lib64/libc-2.28.so)
==1312922==    by 0x52D3A55: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D3D4A: _nc_first_db (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDB97: _nc_read_entry2 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D69E5: _nc_setup_tinfo (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D62: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 20 bytes in 1 blocks are still reachable in loss record 9 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6C9E3: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6EB49: rl_parse_and_bind (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6F031: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E62521: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 24 bytes in 1 blocks are definitely lost in loss record 10 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x402D0A: deq_new (deq.c:134)
==1312922==    by 0x401113: newJobs (Jobs.c:15)
==1312922==    by 0x4031DE: main (Shell.c:17)
==1312922== 
==1312922== 30 bytes in 1 blocks are still reachable in loss record 11 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x52D464C: _nc_home_terminfo (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D3D34: _nc_first_db (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDB97: _nc_read_entry2 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D69E5: _nc_setup_tinfo (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D62: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 38 bytes in 10 blocks are indirectly lost in loss record 12 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x558F67D: strdup (in /usr/lib64/libc-2.28.so)
==1312922==    by 0x4022D8: getargs (Command.c:131)
==1312922==    by 0x4023D2: newCommand (Command.c:142)
==1312922==    by 0x401CC3: i_command (Interpreter.c:19)
==1312922==    by 0x401CF3: i_pipeline (Interpreter.c:26)
==1312922==    by 0x401D5C: i_sequence (Interpreter.c:34)
==1312922==    by 0x401DC7: interpretTree (Interpreter.c:43)
==1312922==    by 0x4032A8: main (Shell.c:37)
==1312922== 
==1312922== 40 bytes in 1 blocks are still reachable in loss record 13 of 55
==1312922==    at 0x4C3D1C3: calloc (vg_replace_malloc.c:1554)
==1312922==    by 0x52D3E4B: _nc_first_db (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDB97: _nc_read_entry2 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D69E5: _nc_setup_tinfo (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D62: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 47 bytes in 1 blocks are still reachable in loss record 14 of 55
==1312922==    at 0x4C3D3D7: realloc (vg_replace_malloc.c:1649)
==1312922==    by 0x52D4286: _nc_doalloc (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DD2C9: _nc_read_termtype (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DD6AC: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDA96: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDBC4: _nc_read_entry2 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D69E5: _nc_setup_tinfo (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D62: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922== 
==1312922== 47 bytes in 1 blocks are still reachable in loss record 15 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x52D238D: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D79: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 70 (32 direct, 38 indirect) bytes in 2 blocks are definitely lost in loss record 16 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x40232B: newCommand (Command.c:139)
==1312922==    by 0x401CC3: i_command (Interpreter.c:19)
==1312922==    by 0x401CF3: i_pipeline (Interpreter.c:26)
==1312922==    by 0x401D5C: i_sequence (Interpreter.c:34)
==1312922==    by 0x401DC7: interpretTree (Interpreter.c:43)
==1312922==    by 0x4032A8: main (Shell.c:37)
==1312922== 
==1312922== 80 bytes in 1 blocks are still reachable in loss record 17 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x52D2400: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D79: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 91 bytes in 1 blocks are still reachable in loss record 18 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x52D3DB3: _nc_first_db (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDB97: _nc_read_entry2 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D69E5: _nc_setup_tinfo (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D62: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 94 bytes in 1 blocks are still reachable in loss record 19 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x52D848E: _nc_tparm_analyze (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D8713: tparm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDFC4: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DE23F: _nc_trim_sgr0 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7451: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 96 bytes in 6 blocks are indirectly lost in loss record 20 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x40232B: newCommand (Command.c:139)
==1312922==    by 0x401CC3: i_command (Interpreter.c:19)
==1312922==    by 0x401CF3: i_pipeline (Interpreter.c:26)
==1312922==    by 0x401D5C: i_sequence (Interpreter.c:34)
==1312922==    by 0x401DC7: interpretTree (Interpreter.c:43)
==1312922==    by 0x4032A8: main (Shell.c:37)
==1312922== 
==1312922== 144 bytes in 6 blocks are indirectly lost in loss record 21 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x402D0A: deq_new (deq.c:134)
==1312922==    by 0x4014AE: newPipeline (Pipeline.c:23)
==1312922==    by 0x401D42: i_sequence (Interpreter.c:33)
==1312922==    by 0x401DC7: interpretTree (Interpreter.c:43)
==1312922==    by 0x4032A8: main (Shell.c:37)
==1312922== 
==1312922== 144 bytes in 6 blocks are indirectly lost in loss record 22 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x402D0A: deq_new (deq.c:134)
==1312922==    by 0x4014C2: newPipeline (Pipeline.c:24)
==1312922==    by 0x401D42: i_sequence (Interpreter.c:33)
==1312922==    by 0x401DC7: interpretTree (Interpreter.c:43)
==1312922==    by 0x4032A8: main (Shell.c:37)
==1312922== 
==1312922== 144 bytes in 6 blocks are indirectly lost in loss record 23 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x40283E: put (deq.c:38)
==1312922==    by 0x402EE1: deq_tail_put (deq.c:166)
==1312922==    by 0x4015A3: addPipeline (Pipeline.c:56)
==1312922==    by 0x401D05: i_pipeline (Interpreter.c:26)
==1312922==    by 0x401D5C: i_sequence (Interpreter.c:34)
==1312922==    by 0x401DC7: interpretTree (Interpreter.c:43)
==1312922==    by 0x4032A8: main (Shell.c:37)
==1312922== 
==1312922== 144 bytes in 8 blocks are indirectly lost in loss record 24 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4021FF: getargs (Command.c:125)
==1312922==    by 0x4023D2: newCommand (Command.c:142)
==1312922==    by 0x401CC3: i_command (Interpreter.c:19)
==1312922==    by 0x401CF3: i_pipeline (Interpreter.c:26)
==1312922==    by 0x401D5C: i_sequence (Interpreter.c:34)
==1312922==    by 0x401DC7: interpretTree (Interpreter.c:43)
==1312922==    by 0x4032A8: main (Shell.c:37)
==1312922== 
==1312922== 160 bytes in 1 blocks are still reachable in loss record 25 of 55
==1312922==    at 0x4C3D3D7: realloc (vg_replace_malloc.c:1649)
==1312922==    by 0x52D4286: _nc_doalloc (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DD2E7: _nc_read_termtype (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DD6AC: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDA96: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDBC4: _nc_read_entry2 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D69E5: _nc_setup_tinfo (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D62: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922== 
==1312922== 256 bytes in 1 blocks are still reachable in loss record 26 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E62716: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 280 bytes in 1 blocks are still reachable in loss record 27 of 55
==1312922==    at 0x4C3D1C3: calloc (vg_replace_malloc.c:1554)
==1312922==    by 0x52D6D44: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 616 bytes in 1 blocks are still reachable in loss record 28 of 55
==1312922==    at 0x4C3D1C3: calloc (vg_replace_malloc.c:1554)
==1312922==    by 0x52DD546: _nc_read_termtype (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DD6AC: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDA96: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDBC4: _nc_read_entry2 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D69E5: _nc_setup_tinfo (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D62: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 616 bytes in 1 blocks are still reachable in loss record 29 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x52D24C9: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D79: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 816 (144 direct, 672 indirect) bytes in 6 blocks are definitely lost in loss record 30 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x401409: newPipeline (Pipeline.c:20)
==1312922==    by 0x401D42: i_sequence (Interpreter.c:33)
==1312922==    by 0x401DC7: interpretTree (Interpreter.c:43)
==1312922==    by 0x4032A8: main (Shell.c:37)
==1312922== 
==1312922== 883 bytes in 1 blocks are still reachable in loss record 31 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x52DD584: _nc_read_termtype (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DD6AC: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDA96: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDBC4: _nc_read_entry2 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D69E5: _nc_setup_tinfo (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D62: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 1,024 bytes in 1 blocks are still reachable in loss record 32 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E712DA: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E75E60: rl_redisplay (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E61447: readline_internal_setup (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6275E: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 1,024 bytes in 1 blocks are still reachable in loss record 33 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E712F0: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E75E60: rl_redisplay (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E61447: readline_internal_setup (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6275E: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 1,024 bytes in 1 blocks are still reachable in loss record 34 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E71335: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E75E60: rl_redisplay (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E61447: readline_internal_setup (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6275E: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 1,024 bytes in 1 blocks are still reachable in loss record 35 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E71354: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E75E60: rl_redisplay (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E61447: readline_internal_setup (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6275E: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 1,024 bytes in 1 blocks are still reachable in loss record 36 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7136C: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E75E60: rl_redisplay (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E61447: readline_internal_setup (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6275E: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 1,024 bytes in 1 blocks are still reachable in loss record 37 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E71384: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E75E60: rl_redisplay (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E61447: readline_internal_setup (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6275E: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 1,536 bytes in 1 blocks are still reachable in loss record 38 of 55
==1312922==    at 0x4C3D3D7: realloc (vg_replace_malloc.c:1649)
==1312922==    by 0x4E85111: xrealloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E660E7: rl_add_funmap_entry (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6614D: rl_initialize_funmap (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E62515: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 1,576 bytes in 1 blocks are still reachable in loss record 39 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x52DCC4F: _nc_read_termtype (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DD6AC: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDA96: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDBC4: _nc_read_entry2 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D69E5: _nc_setup_tinfo (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D62: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 2,032 bytes in 1 blocks are still reachable in loss record 40 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7B449: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 2,176 bytes in 136 blocks are still reachable in loss record 41 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E66090: rl_add_funmap_entry (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6614D: rl_initialize_funmap (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E62515: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 3,896 bytes in 1 blocks are still reachable in loss record 42 of 55
==1312922==    at 0x4C3D3D7: realloc (vg_replace_malloc.c:1649)
==1312922==    by 0x52D4286: _nc_doalloc (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DD305: _nc_read_termtype (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DD6AC: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDA96: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52DDBC4: _nc_read_entry2 (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D69E5: _nc_setup_tinfo (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D62: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922== 
==1312922== 3,896 bytes in 1 blocks are still reachable in loss record 43 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x52D23B0: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D6D79: _nc_setupterm (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7266: tgetent_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B21B: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 4,016 bytes in 1 blocks are still reachable in loss record 44 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7F18B: add_history (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E82B62: read_history_range (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403213: main (Shell.c:22)
==1312922== 
==1312922== 4,080 bytes in 1 blocks are still reachable in loss record 45 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7B469: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 4,112 bytes in 1 blocks are still reachable in loss record 46 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E66221: rl_make_bare_keymap (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6D172: rl_generic_bind (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7AA45: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7B357: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 7,952 bytes in 1 blocks are still reachable in loss record 47 of 55
==1312922==    at 0x4C3D1C3: calloc (vg_replace_malloc.c:1554)
==1312922==    by 0x52D31D7: ??? (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D397A: _nc_find_type_entry (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x52D7BEC: tgetstr_sp (in /usr/lib64/libtinfo.so.6.1)
==1312922==    by 0x4E7B25A: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 8,224 bytes in 2 blocks are still reachable in loss record 48 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E66221: rl_make_bare_keymap (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6D172: rl_generic_bind (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7AAB7: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7B357: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 8,224 bytes in 2 blocks are still reachable in loss record 49 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E66221: rl_make_bare_keymap (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6D172: rl_generic_bind (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7AA45: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7B363: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 8,224 bytes in 2 blocks are still reachable in loss record 50 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E66221: rl_make_bare_keymap (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6D172: rl_generic_bind (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7AAB7: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7B363: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 8,224 bytes in 2 blocks are still reachable in loss record 51 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E66221: rl_make_bare_keymap (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6D172: rl_generic_bind (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7AA45: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7B36F: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 8,224 bytes in 2 blocks are still reachable in loss record 52 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E66221: rl_make_bare_keymap (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6D172: rl_generic_bind (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7AAB7: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E7B36F: _rl_init_terminal_io (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E624F8: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 8,224 bytes in 2 blocks are still reachable in loss record 53 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E66221: rl_make_bare_keymap (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6D172: rl_generic_bind (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E62591: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 12,336 bytes in 3 blocks are still reachable in loss record 54 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E66221: rl_make_bare_keymap (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6D172: rl_generic_bind (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E625A4: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== 32,896 bytes in 8 blocks are still reachable in loss record 55 of 55
==1312922==    at 0x4C38185: malloc (vg_replace_malloc.c:431)
==1312922==    by 0x4E850DC: xmalloc (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E66221: rl_make_bare_keymap (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6D172: rl_generic_bind (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6EE32: rl_parse_and_bind (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6F031: ??? (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E62521: rl_initialize (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x4E6273A: readline (in /usr/lib64/libreadline.so.7.0)
==1312922==    by 0x403253: main (Shell.c:30)
==1312922== 
==1312922== LEAK SUMMARY:
==1312922==    definitely lost: 200 bytes in 9 blocks
==1312922==    indirectly lost: 710 bytes in 42 blocks
==1312922==      possibly lost: 0 bytes in 0 blocks
==1312922==    still reachable: 139,342 bytes in 196 blocks
==1312922==         suppressed: 0 bytes in 0 blocks
==1312922== 
==1312922== For lists of detected and suppressed errors, rerun with: -s
==1312922== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
[antonleslie@onyx hw3]$ 



