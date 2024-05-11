****************
* Project 1 - Knight's Tour
* CS421-Summer 2023.
* 07/1/2023
* Anton Leslie
**************** 

OVERVIEW:
Knight's Tour Problem Solver
This project aims to solve the Knight's Tour problem using an exhaustive search with backtracking technique. 
The Knight's Tour problem involves finding a sequence of moves for a knight on a 
chessboard to visit every position exactly once. 
The program offers three different search strategies to find the solution: basic search, heuristic I, and heuristic II.

Files
The project consists of three Java files:

KnightTour.java - The driver program that takes command-line arguments to determine the search option, board size, and initial position.
KnightBoard.java - Implements the logic for solving the Knight's Tour problem using the selected search strategy.
Position.java - Represents a position on the chessboard and provides information such as distance to the boarder and number of onward moves.
Sample_output- results compare 
run_test - run script used 

  
COMPILING AND RUNNING:
  
 From the directory containing all source files, compile the required classes with the commands:
 $ javac KnightBoard.java
 $ javac KnightTour.java
 or 
 Run the compiled driver class with the command with the given parameters:
java *.java
 java KnightTour <0/1/2 (no/heuristicI/heuristicII search)> <n> <x> <y>


REQUESTED RESULTS :


java KnightTour 0 7 1 1
Search Option 0 - Total Moves: 254727174
Solution for Search Option 0:
Table 0 here (
21 46 41 2  23 26 9  
40 1  22 27 10 3  24 
47 20 45 42 25 8  11 
44 39 34 19 28 15 4  
33 48 43 36 7  12 29 
38 35 18 31 14 5  16 
49 32 37 6  17 30 13 )

java KnightTour 1 7 1 1
Search Option 1 - Total Moves: 810
Solution for Search Option 1:
Table 1 here (
21 44 11 2  23 36 13 
10 1  22 43 12 3  24 
45 20 9  40 35 14 37 
8  33 42 49 38 25 4  
19 46 39 34 41 28 15 
32 7  48 17 30 5  26 
47 18 31 6  27 16 29 )

java KnightTour 2 7 1 1
Search Option 2 - Total Moves: 172
Solution for Search Option 2:

Table 2 here (
49 44 11 2  29 42 13 
10 1  46 43 12 3  28 
45 48 9  30 41 14 35 
8  25 40 47 36 27 4  
39 22 31 26 17 34 15 
24 7  20 37 32 5  18 
21 38 23 6  19 16 33 )