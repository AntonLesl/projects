# CS 452/552 HW5: Driversity

## Author: Anton Leslie

### Description
This Linux kernel module implements a character device that provides a software abstraction called a scanner. The scanner helps applications split a sequence of characters into tokens based on separators, which can be customized via IOCTL commands. This device is designed to handle any data, including binary data containing NUL characters, and it treats them like regular data bytes rather than string terminators.



#### Setting Up Your Development Environment
To ensure safety and avoid any potential system crashes or data loss, it is strongly recommended to run and test this module within a virtual machine (VM) setup for kernel development and testing.

0. $ ~JBuffenb/classes/452/pub/bin/sshnode

1. Copy Command
cp ~jbuffenb/classes/452/pub/hw5/fedora.img . 

2. Script Execution Command
~jbuffenb/classes/452/pub/bin/hw5boot 

3. Secure Copy (SCP) Command
 scp -P 2222 -r \
 ~ANTONLESLIE/hw5Cs/Scanner \
 cs452@localhost:
 password: cs452hw4


 4. Secure Shell (SSH) Command
ssh -p 2222 cs452@localhost
 password: cs452hw4


### Compilation and Usage
5. Change Directory Command
cd Scanner/

6. Make compile Commands
 make
 make install
 make try
 chmod +x ./test_scanner.sh
 ./test_scanner.sh


7. Valgrind compile Commands

sudo yum install valgrind

valgrind ./test_scanner.sh

8. Kernel Command Log 
The dmesg command displays the contents of the kernel ring buffer. This buffer contains messages from the kernel, including boot processes, drivers loading, and warnings.
dmesg

Real-time Follow: To continuously monitor new kernel messages as they come in:

dmesg --follow

### demo for my script
[cs452@qemu Scanner]$  ./test_scanner.sh
Testing kernel module loading...
insmod: ERROR: could not load module scanner_module.ko: No such file or directory
Kernel module loaded.
Checking kernel log...
-------------------------------------
Testing device opening...
Device opened successfully.
Checking kernel log...
[  172.647153] Scanner: Device opened
-------------------------------------
Testing writing to the device...
Data written: Hello, Scanner
Checking kernel log...
[  172.647153] Scanner: Device opened
[  172.648615] Scanner: Wrote 14 bytes
-------------------------------------
Testing reading from the device...
Data read: Hello, Scanner
Checking kernel log...
[  172.647153] Scanner: Device opened
[  172.648615] Scanner: Wrote 14 bytes
[  172.650748] Scanner: Read 14 bytes
-------------------------------------
Test PASS: Read matches written.
Testing device release...
Device closed successfully.
Checking kernel log...
[  172.647153] Scanner: Device opened
[  172.648615] Scanner: Wrote 14 bytes
[  172.650748] Scanner: Read 14 bytes
[  172.652636] Scanner: Device closed
-------------------------------------
Testing kernel module unloading...
rmmod: ERROR: Module scanner_module is not currently loaded
Kernel module unloaded.
Checking kernel log...
[  172.647153] Scanner: Device opened
[  172.648615] Scanner: Wrote 14 bytes
[  172.650748] Scanner: Read 14 bytes
[  172.652636] Scanner: Device closed
-------------------------------------

[cs452@qemu Scanner]$ 


### Valgrind Results

Valgrind results:
[cs452@qemu Scanner]$ valgrind ./test_scanner.sh
==2332== Memcheck, a memory error detector
==2332== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2332== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==2332== Command: ./test_scanner.sh
==2332== 
Testing kernel module loading...
./test_scanner.sh: line 27: /usr/bin/sudo: Permission denied
==2333== 
==2333== HEAP SUMMARY:
==2333==     in use at exit: 61,947 bytes in 694 blocks
==2333==   total heap usage: 1,579 allocs, 885 frees, 112,680 bytes allocated
==2333== 
==2333== LEAK SUMMARY:
==2333==    definitely lost: 32 bytes in 1 blocks
==2333==    indirectly lost: 0 bytes in 0 blocks
==2333==      possibly lost: 0 bytes in 0 blocks
==2333==    still reachable: 61,915 bytes in 693 blocks
==2333==         suppressed: 0 bytes in 0 blocks
==2333== Rerun with --leak-check=full to see details of leaked memory
==2333== 
==2333== For lists of detected and suppressed errors, rerun with: -s
==2333== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
Kernel module loaded.
Checking kernel log...
[  134.198414] Scanner module initialized
[  140.923677] Scanner: Device opened
[  140.923681] Scanner: Separators updated
[  140.923683] Scanner: Wrote 38 bytes
[  140.923684] Scanner: Read 38 bytes
[  140.923958] Scanner: Device closed
[  163.715963] Scanner: Device opened
[  163.719816] Scanner: Wrote 14 bytes
[  163.724229] Scanner: Read 14 bytes
[  163.728271] Scanner: Device closed
-------------------------------------
Testing device opening...
Device opened successfully.
Checking kernel log...
[  140.923677] Scanner: Device opened
[  140.923681] Scanner: Separators updated
[  140.923683] Scanner: Wrote 38 bytes
[  140.923684] Scanner: Read 38 bytes
[  140.923958] Scanner: Device closed
[  163.715963] Scanner: Device opened
[  163.719816] Scanner: Wrote 14 bytes
[  163.724229] Scanner: Read 14 bytes
[  163.728271] Scanner: Device closed
[  298.572665] Scanner: Device opened
-------------------------------------
Testing writing to the device...
Data written: Hello, Scanner
Checking kernel log...
[  140.923681] Scanner: Separators updated
[  140.923683] Scanner: Wrote 38 bytes
[  140.923684] Scanner: Read 38 bytes
[  140.923958] Scanner: Device closed
[  163.715963] Scanner: Device opened
[  163.719816] Scanner: Wrote 14 bytes
[  163.724229] Scanner: Read 14 bytes
[  163.728271] Scanner: Device closed
[  298.572665] Scanner: Device opened
[  298.598058] Scanner: Wrote 14 bytes
-------------------------------------
Testing reading from the device...
==2340== 
==2340== HEAP SUMMARY:
==2340==     in use at exit: 150,425 bytes in 832 blocks
==2340==   total heap usage: 2,695 allocs, 1,863 frees, 226,098 bytes allocated
==2340== 
==2340== LEAK SUMMARY:
==2340==    definitely lost: 0 bytes in 0 blocks
==2340==    indirectly lost: 0 bytes in 0 blocks
==2340==      possibly lost: 0 bytes in 0 blocks
==2340==    still reachable: 150,425 bytes in 832 blocks
==2340==         suppressed: 0 bytes in 0 blocks
==2340== Rerun with --leak-check=full to see details of leaked memory
==2340== 
==2340== For lists of detected and suppressed errors, rerun with: -s
==2340== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
Data read: Hello, Scanner
Checking kernel log...
[  140.923683] Scanner: Wrote 38 bytes
[  140.923684] Scanner: Read 38 bytes
[  140.923958] Scanner: Device closed
[  163.715963] Scanner: Device opened
[  163.719816] Scanner: Wrote 14 bytes
[  163.724229] Scanner: Read 14 bytes
[  163.728271] Scanner: Device closed
[  298.572665] Scanner: Device opened
[  298.598058] Scanner: Wrote 14 bytes
[  298.640791] Scanner: Read 14 bytes
-------------------------------------
Test PASS: Read matches written.
Testing device release...
Device closed successfully.
Checking kernel log...
[  140.923684] Scanner: Read 38 bytes
[  140.923958] Scanner: Device closed
[  163.715963] Scanner: Device opened
[  163.719816] Scanner: Wrote 14 bytes
[  163.724229] Scanner: Read 14 bytes
[  163.728271] Scanner: Device closed
[  298.572665] Scanner: Device opened
[  298.598058] Scanner: Wrote 14 bytes
[  298.640791] Scanner: Read 14 bytes
[  298.691046] Scanner: Device closed
-------------------------------------
Testing kernel module unloading...
./test_scanner.sh: line 66: /usr/bin/sudo: Permission denied
==2346== 
==2346== HEAP SUMMARY:
==2346==     in use at exit: 151,528 bytes in 867 blocks
==2346==   total heap usage: 3,449 allocs, 2,582 frees, 244,907 bytes allocated
==2346== 
==2346== LEAK SUMMARY:
==2346==    definitely lost: 32 bytes in 1 blocks
==2346==    indirectly lost: 0 bytes in 0 blocks
==2346==      possibly lost: 0 bytes in 0 blocks
==2346==    still reachable: 151,496 bytes in 866 blocks
==2346==         suppressed: 0 bytes in 0 blocks
==2346== Rerun with --leak-check=full to see details of leaked memory
==2346== 
==2346== For lists of detected and suppressed errors, rerun with: -s
==2346== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
Kernel module unloaded.
Checking kernel log...
[  140.923684] Scanner: Read 38 bytes
[  140.923958] Scanner: Device closed
[  163.715963] Scanner: Device opened
[  163.719816] Scanner: Wrote 14 bytes
[  163.724229] Scanner: Read 14 bytes
[  163.728271] Scanner: Device closed
[  298.572665] Scanner: Device opened
[  298.598058] Scanner: Wrote 14 bytes
[  298.640791] Scanner: Read 14 bytes
[  298.691046] Scanner: Device closed
-------------------------------------

==2332== 
==2332== HEAP SUMMARY:
==2332==     in use at exit: 154,104 bytes in 867 blocks
==2332==   total heap usage: 3,651 allocs, 2,784 frees, 246,196 bytes allocated
==2332== 
==2332== LEAK SUMMARY:
==2332==    definitely lost: 0 bytes in 0 blocks
==2332==    indirectly lost: 0 bytes in 0 blocks
==2332==      possibly lost: 0 bytes in 0 blocks
==2332==    still reachable: 154,104 bytes in 867 blocks
==2332==         suppressed: 0 bytes in 0 blocks
==2332== Rerun with --leak-check=full to see details of leaked memory
==2332== 
==2332== For lists of detected and suppressed errors, rerun with: -s
==2332== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
[cs452@qemu Scanner]$ 
