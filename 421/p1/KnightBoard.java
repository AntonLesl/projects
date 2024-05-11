
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

/**

 The KnightBoard class represents a chessboard for the Knight's Tour problem.
 It provides methods to solve the Knight's Tour using different strategies.
 The class keeps track of the board state, the total number of moves, and provides
 utility methods for generating valid moves and checking safety of positions.

 Author: Anton Leslie.
 */
public class KnightBoard {
	private static final int[] xMoveList = {-2, -1, 1, 2, 2, 1, -1, -2};
	private static final int[] yMoveList = {1, 2, 2, 1, -1, -2, -2, -1};

	private final int n; // Size of the board
	private final int[][] grid; // Representation of the board
	private int total; // Total number of squares on the board
	private int moveCount; // Number of moves taken by the knight

	public KnightBoard(int n, int initX, int initY, int option) {
		this.n = n;
		this.grid = new int[n][n];
		this.total = n * n;
		this.moveCount = 0; // Initialize moveCount to 0

		// Initialize the board with -1 (unvisited squares)
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				grid[x][y] = -1;
			}
		}

		grid[initX][initY] = 1; // Set the initial position of the knight

		// Choose the solving method based on the option parameter
		if (option == 0) {
			solveKnightsTourBasic(initX, initY);
		} else if (option == 1) {
			solveKnightsTourHeuristicI(initX, initY);
		} else if (option == 2) {
			solveKnightsTourHeuristicII(initX, initY);
		} else {
			System.out.println("Invalid option. Available options: 0 (no search), 1 (heuristic I), 2 (heuristic II)");
			return;
		}
	}


	
private void solveKnightsTourBasic(int x, int y) {
    moveCount = 0; // Reset moveCount
    if (!solveKnightsTourBasicUtil(x, y, 1)) {
        System.out.println("No Solution.");
        System.out.println("The total number of moves is " + moveCount + "\n");
    } else {
        System.out.println("The total number of moves is " + moveCount);
        printGrid();
    }
}

private boolean solveKnightsTourBasicUtil(int x, int y, int count) {
    moveCount++; // Increment moveCount

    if (count == total) {
        return true;
    }

    for (int i = 0; i < 8; i++) {
        int nextX = x + xMoveList[i];
        int nextY = y + yMoveList[i];

        if (isSafe(nextX, nextY)) {
            grid[nextX][nextY] = count + 1;
            if (solveKnightsTourBasicUtil(nextX, nextY, count + 1)) {
                return true;
            } else {
                grid[nextX][nextY] = -1;
            }
        }
    }

    return false;
}






    /**
     * Solves the knight's tour using the heuristic I algorithm.
     *
     * @param x The current x-coordinate of the knight.
     * @param y The current y-coordinate of the knight.
     */
     private void solveKnightsTourHeuristicI(int x, int y) {
        moveCount = 0; // Reset moveCount
        if (!solveKnightsTourHeuristicIUtil(x, y, 1)) {
            System.out.println("No Solution.");
            System.out.println("The total number of moves is " + moveCount+ "\n");
        } else {
            System.out.println("The total number of moves is " + moveCount);
            printGrid();
        }
    }

    /**
     * Recursive utility function to solve the knight's tour using heuristic I algorithm.
     *
     * @param x     The current x-coordinate of the knight.
     * @param y     The current y-coordinate of the knight.
     * @param count The current move count.
     * @return True if a solution is found, false otherwise.
     */
   private boolean solveKnightsTourHeuristicIUtil(int x, int y, int count) {
         // Increment moveCount
		 moveCount++;
        if (count == total) {
            return true;
			
        }

        List<Position> moves = generateMoves(x, y);
        moves.sort(Comparator.comparingInt(Position::getDistanceToBorder));

        for (Position move : moves) {
            int nextX = move.getX();
            int nextY = move.getY();

            grid[nextX][nextY] = count + 1;

            if (solveKnightsTourHeuristicIUtil(nextX, nextY, count + 1)) {
                return true;
            } else {
                grid[nextX][nextY] = -1;
            }
        }

        return false;
    }

	 /**
	 * Solves the knight's tour using the heuristic II algorithm.
	 *
	 * @param x     The current x-coordinate of the knight.
	 * @param y     The current y-coordinate of the knight.
	 */
	private void solveKnightsTourHeuristicII(int x, int y) {
		if (!solveKnightsTourHeuristicIIUtil(x, y, 1)) {
			System.out.println("No Solution.");
			System.out.println("The total number of moves is " + moveCount+ "\n");

		} else {
			printGrid();
		}
	}

	/**
	 * Recursive utility function to solve the knight's tour using heuristic II algorithm.
	 *
	 * @param x     The current x-coordinate of the knight.
	 * @param y     The current y-coordinate of the knight.
	 * @param count The current move count.
	 * @return True if a solution is found, false otherwise.
	 */
	private boolean solveKnightsTourHeuristicIIUtil(int x, int y, int count) {
		moveCount++; // Increment moveCount
		if (count == total) {
			System.out.println("The total number of moves is " + moveCount);
			return true;
		}

		List<Position> moves = generateMoves(x, y);
		moves.sort(Comparator.comparingInt(Position::getOnwardMoves));

		for (Position move : moves) {
			int nextX = move.getX();
			int nextY = move.getY();

			grid[nextX][nextY] = count + 1;

			if (solveKnightsTourHeuristicIIUtil(nextX, nextY, count + 1)) {
				return true;
			} else {
				grid[nextX][nextY] = -1;
			}
		}

		return false;
	}

	/**
	 * Generates a list of valid moves for the knight from a given position.
	 *
	 * @param x The x-coordinate of the current position.
	 * @param y The y-coordinate of the current position.
	 * @return A list of valid moves as Position objects.
	 */
	private List<Position> generateMoves(int x, int y) {
		List<Position> moves = new ArrayList<>();

		for (int i = 0; i < 8; i++) {
			int nextX = x + xMoveList[i];
			int nextY = y + yMoveList[i];

			if (isSafe(nextX, nextY)) {
				int distance = Math.min(Math.abs(nextX - 0), Math.abs(nextX - (n - 1))) +
						Math.min(Math.abs(nextY - 0), Math.abs(nextY - (n - 1)));

				int onwardMoves = countOnwardMoves(nextX, nextY);

				moves.add(new Position(nextX, nextY, distance, onwardMoves));
			}
		}

		return moves;
	}

	/**
	 * Counts the number of onward moves from a given position.
	 *
	 * @param x The x-coordinate of the current position.
	 * @param y The y-coordinate of the current position.
	 * @return The count of valid onward moves.
	 */
	private int countOnwardMoves(int x, int y) {
		int count = 0;

		for (int i = 0; i < 8; i++) {
			int nextX = x + xMoveList[i];
			int nextY = y + yMoveList[i];

			if (isSafe(nextX, nextY) && grid[nextX][nextY] == -1) {
				count++;
			}
		}

		return count;
	}

	/**
	 * Checks if a given position is safe to move to.
	 *
	 * @param x The x-coordinate of the position.
	 * @param y The y-coordinate of the position.
	 * @return True if the position is safe, false otherwise.
	 */
	private boolean isSafe(int x, int y) {
		
		return (x >= 0 && x < n && y >= 0 && y < n && grid[x][y] == -1);
	}

	    /**
     * Prints the current state of the knight's tour grid.
     */
   /**
 * Prints the current state of the knight's tour grid.
 */
  private void printGrid() {
        int maxNumber = total;
        int digits = String.valueOf(maxNumber).length();

        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                System.out.printf("%-" + (digits + 1) + "d", grid[x][y]);
            }
            System.out.println();
        }
        System.out.println();
    }

}

