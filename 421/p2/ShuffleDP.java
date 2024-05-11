/*
* Author: Anton Leslie
* The "ShuffleDP" class provides functionality to check if a target string Z is a valid shuffle of two input strings X and Y. 
* The class utilizes dynamic programming to efficiently determine if the characters of Z are formed by interweaving characters from X and Y. 
* The program utilizes a 2D table (dp) to store intermediate results during the computation.
*/

import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;

public class ShuffleDP {
    private static int tableReferences;
    private static boolean[][] dp;

    /**
     * Checks if a string Z is a valid shuffle of strings X and Y.
     *
     * @param X The first input string.
     * @param Y The second input string.
     * @param Z The target string to check if it is a valid shuffle of X and Y.
     * @return true if Z is a valid shuffle of X and Y, false otherwise.
     */
 public static boolean isShuffle(String X, String Y, String Z) {
    int m = X.length();
    int n = Y.length();
    if (m + n != Z.length()) return false;

tableReferences = 0;
    dp = new boolean[m + 1][n + 1];
    dp[0][0] = true; // Base case: empty X and Y can form an empty Z.

// Filling the first row of the dp table
for (int i = 1; i <= m; i++) {
    if (X.charAt(i - 1) == Z.charAt(i - 1)) tableReferences++; // Count the reference when X.charAt(i - 1) == Z.charAt(i - 1) is true
    dp[i][0] = X.charAt(i - 1) == Z.charAt(i - 1) && dp[i - 1][0];
}


// Filling the first column of the dp table
for (int j = 1; j <= n; j++) {
    if (Y.charAt(j - 1) == Z.charAt(j - 1)) tableReferences++; // Count the reference when Y.charAt(j - 1) == Z.charAt(j - 1) is true
    dp[0][j] = Y.charAt(j - 1) == Z.charAt(j - 1) && dp[0][j - 1];
}

for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
        char zChar = Z.charAt(i + j - 1);
        
        boolean b1 = X.charAt(i - 1) == zChar;
        boolean b2 = Y.charAt(j - 1) == zChar;
        
        // Calculate dp[i][j] based on the given conditions
        dp[i][j] = (b1 && dp[i - 1][j]) || (b2 && dp[i][j - 1]);
        
        
        if (b1){
             tableReferences++;
             if(!dp[i-1][j] ){
                if(b2){
                    tableReferences++;
                }
             }
        }
        
           
        
        // If b2 is true and dp[i][j - 1] is false, increment the reference count
        else if (b2){
            tableReferences++;
        }
            
    }
}

    return dp[m][n];
}



    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Usage: java ShuffleDP <X> <Y> <Z> [<debug level>]");
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
                    System.out.printf("%-2d ", dp[i][j] ? 1 : 0);
                }
                System.out.println();
            }
        }

        if (debugLevel == 1) {
            // Write the DP table to a file "ShuffleDP-Table.txt"
            try {
                FileWriter writer = new FileWriter("ShuffleDP-Table.txt");
                for (int i = 0; i <= X.length(); i++) {
                    for (int j = 0; j <= Y.length(); j++) {
                        writer.write(dp[i][j] ? "1 " : "0 ");
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
