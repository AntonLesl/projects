****************
* Project 2 - Knapsack and Shuffle Dynamic Programming
* CS421-Summer
* 07/27/2023
* Anton Leslie
**************** 

OVERVIEW:
Knapsack and Shuffle Dynamic Programming
This repository contains Java programs to solve two dynamic programming problems: Shuffle-ness and 0-1 Knapsack. Two approaches are used to solve each problem: dynamic programming bottom-up (DP) and dynamic programming top-down (recursion with memoization).

Files
The project consists of three Java files:

Shuffle.def: A text file containing the recursive definition of the boolean function t(i, j) for the Shuffle-ness problem. It outlines the base cases and recursive cases for determining whether a given string Z is a shuffle of two input strings X and Y.

ShuffleRM.java: A Java program implementing the recursion with memoization approach for the Shuffle-ness problem. It constructs the table in a top-down fashion based on the sequence of recursive calls.

ShuffleDP.java: A Java program implementing the dynamic programming bottom-up approach for the Shuffle-ness problem. It constructs the table in a bottom-up fashion, filling it iteratively based on the subproblems' solutions.

KnapsackRM.java: A Java program implementing the recursion with memoization approach for the 0-1 Knapsack problem. It constructs both the optimal value table and the decision table in a top-down fashion.

KnapsackDP.java: A Java program implementing the dynamic programming bottom-up approach for the 0-1 Knapsack problem. It constructs the optimal value table and provides an option to print the decision table.


  
COMPILING AND RUNNING:
  
javac *.java 
or 
javac ShuffleDP.java
javac ShuffleRM.java
javac KnapsackDP.java
javac KnapsackRM.java


java ShuffleDP <X> <Y> <Z> [<debug level>]
java ShuffleRM <X> <Y> <Z> [<debug level>]
java KnapsackDP <n> <W> <w.txt> <v.txt> [<debug level>]
java KnapsackRM <n> <W> <w.txt> <v.txt> [<debug level>]

  


	