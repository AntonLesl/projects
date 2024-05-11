#!/bin/bash

# Author: Anton Leslie
# Description: This script is designed to test the basic functionality of the Scanner device driver.
# It performs the following operations:
# 0. Loads and unloads the kernel module to test init and exit functions.
# 1. Opens the Scanner device.
# 2. Writes a predefined test string to the device.
# 3. Reads the string back from the device.
# 4. Compares the written and read strings to verify correct operation.
# 5. Closes the device.
# Each step logs actions and outcomes to the console and checks the kernel log.

DEVICE="/dev/Scanner"
TEST_STRING="Hello, Scanner"
MODULE="scanner_module"  # Replace with the actual name of your kernel module

# Display last few lines of kernel log
function check_dmesg {
    echo "Checking kernel log..."
    dmesg | tail -10  # Adjust the number of lines as necessary
    echo "-------------------------------------"
}

# Test loading the kernel module
echo "Testing kernel module loading..."
sudo insmod $MODULE.ko
echo "Kernel module loaded."
check_dmesg

# Test opening the device
echo "Testing device opening..."
exec 3<>$DEVICE  # Open the device for reading and writing using file descriptor 3.
echo "Device opened successfully."
check_dmesg

# Test writing to the device
echo "Testing writing to the device..."
echo -n "$TEST_STRING" >&3  # Write the test string to the device using file descriptor 3.
echo "Data written: $TEST_STRING"
check_dmesg

# Test reading from the device
echo "Testing reading from the device..."
OUTPUT=$(head -n 1 <&3)  # Read back the first line of data from the device using file descriptor 3.
echo "Data read: $OUTPUT"
check_dmesg

# Compare output
if [[ "$OUTPUT" == "$TEST_STRING" ]]; then
    echo "Test PASS: Read matches written."
else
    echo "Test FAIL: Read does not match written."
    echo "Expected: $TEST_STRING"
    echo "Got: $OUTPUT"
fi

# Test closing the device
echo "Testing device release..."
exec 3>&-  # Close file descriptor 3, thus releasing the device.
echo "Device closed successfully."
check_dmesg

# Test unloading the kernel module
echo "Testing kernel module unloading..."
sudo rmmod $MODULE
echo "Kernel module unloaded."
check_dmesg

# Add newline for better readability in output
echo ""
