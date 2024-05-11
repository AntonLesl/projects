
/*
* Author: Anton Leslie
* The "ShuffleRM" class provides functionality to determine whether a given target string Z is a valid shuffle of two input strings X and Y. 
* The class uses a dynamic programming approach to efficiently compute and store intermediate results in a 2D table (dp).
*/

import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;

public class ShuffleRM {
    private static int tableReferences; // Variable to count the number of table references
    private static int[][] dp; // 2D table to store intermediate results

    /**
     * Checks if a string Z is a valid shuffle of strings X and Y using dynamic programming.
     *
     * @param X The first input string.
     * @param Y The second input string.
     * @param Z The target string to check if it is a valid shuffle of X and Y.
     * @return true if Z is a valid shuffle of X and Y, false otherwise.
     */
    public static boolean isShuffle(String X, String Y, String Z) {
        int m = X.length();
        int n = Y.length();
        if (m + n != Z.length()) return false; // If the lengths of X and Y don't add up to the length of Z, they cannot be a valid shuffle.

        dp = new int[m + 1][n + 1];

        // Initialize the entire dp array with -1 (indicating unprocessed state)
        for (int i = 0; i <= m; i++) {
            Arrays.fill(dp[i], -1);
        }

        return isShuffleHelper(X, Y, Z, m, n) == 1;
    }

    private static int isShuffleHelper(String X, String Y, String Z, int m, int n) {
        if (dp[m][n] != -1) {
            // If the state is already computed, return the result from the table
            tableReferences++;
            return dp[m][n];
        }

        if (m == 0 && n == 0) {
            dp[m][n] = 1; // Base case: empty X and Y can form an empty Z.
            tableReferences++;
            return 1;
        }

        char zChar = Z.charAt(m + n - 1); // The character in Z that we are trying to form.

        if (m > 0 && X.charAt(m - 1) == zChar && isShuffleHelper(X, Y, Z, m - 1, n) == 1) {
            dp[m][n] = 1;
            tableReferences++;
            return 1; // Mark the state as valid (1) if X contributes to the current Z character.
        }

        if (n > 0 && Y.charAt(n - 1) == zChar && isShuffleHelper(X, Y, Z, m, n - 1) == 1) {
            dp[m][n] = 1;
            tableReferences++;
            return 1; // Mark the state as valid (1) if Y contributes to the current Z character.
        }

        dp[m][n] = 0;
        tableReferences++;
        return 0; // Mark the state as neither invalid nor valid contribution (0).
    }

    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Usage: java ShuffleRM <X> <Y> <Z> [<debug level>]");
            return;
        }

        String X = args[0];
        String Y = args[1];
        String Z = args[2];

        if (X.length() + Y.length() != Z.length()) {
            System.out.println("The input strings are not compatible.");
            return;
        }

        tableReferences = 0; // Reset the tableReferences variable.
        boolean result = isShuffle(X, Y, Z); // Call the isShuffle function to check if X and Y are valid shuffles of Z.

        int debugLevel = 0;
        if (args.length >= 4) {
            debugLevel = Integer.parseInt(args[3]);
        }

        if (debugLevel >= 0) {
            // Print the DP table if the debug level is greater than or equal to 0.
            for (int i = 0; i <= X.length(); i++) {
                for (int j = 0; j <= Y.length(); j++) {
                    System.out.printf("%2d ", dp[i][j]);
                }
                System.out.println();
            }
        }

        if (debugLevel == 1) {
            // Write the DP table to a file "ShuffleRM-Table.txt"
            try {
                FileWriter writer = new FileWriter("ShuffleRM-Table.txt");
                for (int i = 0; i <= X.length(); i++) {
                    for (int j = 0; j <= Y.length(); j++) {
                        writer.write(dp[i][j] + " ");
                    }
                    writer.write("\n");
                }
                writer.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        System.out.println(result ? "yes" : "no"); // Print the final result (whether X and Y are valid shuffles of Z).
        System.out.println("Number of table references: " + tableReferences); // Print the total number of table references.
    }
}
