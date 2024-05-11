/*
 * This C program serves as a comprehensive test suite for a doubly-ended queue (deque) implementation.
 * It includes various tests to validate the functionality of the deque operations, such as adding and
 * retrieving elements from both ends, checking the length, removing items, and creating a string
 * representation of the deque. The code also ensures proper memory cleanup after testing.
 *
 * Author: Anton Leslie
 */


#include <stdio.h>
#include <stdlib.h>

#include "deq.h"
#include "error.h"
void printElement(Data d);

int main() {

  // Test 1 - Check that new deque is empty
  Deq q = deq_new();
  printf("Test 1: New Deque Length = %d (expected: 0)\n\n", deq_len(q));
  
  // Test 2 - Add items to head and tail, verify that the length changes as expected
  deq_head_put(q, (Data)"Head1");
  deq_tail_put(q, (Data)"Tail1");
  printf("Test 2: Deque Length after 2 puts = %d (expected: 2)\n\n", deq_len(q));
  
  // Test 3 4- Retrieve items from head and tail, verify that they match expected outcome
  Data headData = deq_head_get(q);
  printf("Test 3: Get from Head = %s (expected: Head1)\n\n", (char*)headData);
  Data tailData = deq_tail_get(q);
  printf("Test 4: Get from Tail = %s (expected: Tail1)\n\n", (char*)tailData);
  
  // Test 5 - Another deque length check
  printf("Test 5: Deque Length after 2 gets = %d (expected: 0)\n\n", deq_len(q));
  
  // Test 6 7 8 - Add items and retrieve by index, verify that they match expected outcome
  deq_head_put(q, (Data)"Item1");
  deq_head_put(q, (Data)"Item2");
  deq_tail_put(q, (Data)"Item3");
  printf("Test 6: 1st item from head = %s (expected: Item2)\n\n", (char*)deq_head_ith(q, 0));
  printf("Test 7: 2nd item from head = %s (expected: Item1)\n\n", (char*)deq_head_ith(q, 1));
  printf("Test 8: 1st item from tail = %s (expected: Item3)\n\n", (char*)deq_tail_ith(q, 0));

  // Test 9 - Remove item and make sure length matches as expected
  deq_head_rem(q, (Data)"Item2");
  printf("Test 9: Deque Length after removing Item2 = %d (expected: 2)\n\n", deq_len(q));

  // Test 10 11 - Add more items and check the string representation of the deque
  deq_head_put(q, (Data)"NewHead");
  deq_tail_put(q, (Data)"NewTail");
  printf("Test 10: Deque Length after adding 2 more items = %d (expected: 4)\n\n", deq_len(q));
  char *stringRepresentation = deq_str(q, 0);
  printf("Test 11: Deque String Representation: %s (expected: Item1 Item3 NewHead NewTail)\n\n", stringRepresentation);
  free(stringRepresentation);

  // Test 12- Remove an item from the tail and check the length
  deq_tail_rem(q, (Data)"NewTail");
  printf("Test 12: Deque Length after removing NewTail = %d (expected: 3)\n\n", deq_len(q));

  // Test 13 - Remove an item from the head and check the length
  deq_head_rem(q, (Data)"NewHead");
  printf("Test 13: Deque Length after removing NewHead = %d (expected: 2)\n\n", deq_len(q));

// Test 14 - Test deq_map function
    printf("Test 14: Applying deq_map function to print each element:\n");
    deq_map(q, printElement);
    printf("(expected: Item1 Item3)\n\n");

// Test 15 - Index out of bounds for ith function
int indexOutOfBounds = deq_len(q) + 1; // Assuming the deque length is not sufficient
printf("Test 15: Attempting to access element at index %d (expected: Index out of bounds)\n", indexOutOfBounds);
Data outOfBoundsData = deq_tail_ith(q, indexOutOfBounds); // Corrected from deq_head_ith
if (outOfBoundsData == NULL) {
    printf("Test 15: Index out of bounds as expected\n\n");
} else {
    printf("Test 15: Unexpected result - Element retrieved: %s\n\n", (char*)outOfBoundsData);
}

deq_del(q, NULL); // NULL as the second argument because no custom deletion function is provided

}
// Definition of the printElement function
void printElement(Data d) {
    printf("%s ", (char*)d);
}
