/*
 * Program to Test the Scanner Device Driver
 *
 * Author : Anton Leslie
 * This program is designed to interact with the 'Scanner' device driver,
 * demonstrating basic operations such as open, write, read, and ioctl.
 * It sets custom separators for tokenization, writes a test string to the device,
 * reads back the processed output, and handles potential errors.
 *
 * The purpose is to ensure that the Scanner driver handles input/output operations
 * correctly and adheres to the specified behavior for token separation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define ERR(s) err(s,__FILE__,__LINE__)  // Macro to simplify error handling with detailed context.

// IOCTL code to set separator characters in the Scanner device.
#define SCANNER_MAGIC 's'
#define SCANNER_SET_SEP _IOW(SCANNER_MAGIC, 0, char*)  

// Function to handle and report errors with additional context (file and line number).
static void err(char *s, char *file, int line) {
    fprintf(stderr,"%s:%d: %s\n", file, line, s);
    exit(1);
}

int main() {
    enum { max = 100 };  // Maximum buffer size for reading from the device.
    char buf[max + 1];   // Buffer to hold data read from the device.
    int len;             // Variable to store the number of bytes read.

    // Open the Scanner device with read-write access.
    int scanner = open("/dev/Scanner", O_RDWR);
    if (scanner < 0)
        ERR("open() failed");  // Error handling if the device cannot be opened.

    // Attempt to set custom separators using an IOCTL command.
    char separators[] = ",;:.!?";  // Characters considered as separators.
    if (ioctl(scanner, SCANNER_SET_SEP, separators))
        ERR("ioctl() for separators failed");

    // Write a predefined test string to the Scanner device.
    char *testString = "Hello, world: this is a test! String;\n";
    if (write(scanner, testString, strlen(testString)) != strlen(testString))
        ERR("write() of data failed");

    // Read processed data from the device until there is none left.
    while ((len = read(scanner, buf, max)) > 0) {
        buf[len] = '\0';  // Ensure the string is null-terminated.
        printf("%s", buf);  // Output the data read from the device.
    }
    if (len < 0)
        ERR("read() failed");  // Handle read errors.

    // Close the device.
    close(scanner);
    return 0;
}
