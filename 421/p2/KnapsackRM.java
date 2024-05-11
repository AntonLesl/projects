
/* Author: Anton Leslie
* The "KnapsackRM" class provides an implementation of the Knapsack problem solution using the bottom-up dynamic programming approach. 
* The program aims to maximize the total value of items that can be placed into a knapsack while considering the knapsack's weight capacity. 
* The class is designed to be run from the command-line and accepts specific arguments to perform the computation efficiently.
*/
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.Collections;
import java.util.Arrays; 
import java.io.FileWriter;
import java.io.BufferedWriter;


public class KnapsackRM {
    private static int tableReferences; // Variable to count the number of table references
    private static int[][] memo; // 2D table to store intermediate results
    private static boolean[][] selectedItemsMemo; // 2D table to track selected items

    /**
     * Solves the knapsack problem using recursive memoization.
     *
     * @param n       The number of items.
     * @param W       The maximum capacity of the knapsack.
     * @param weights An array of item weights.
     * @param values  An array of item values.
     * @return The maximum value that can be obtained from items with the given weights and values within the knapsack capacity.
     */
   public static int knapsack(int n, int W, int[] weights, int[] values) {
        memo = new int[n + 1][W + 1];
        selectedItemsMemo = new boolean[n + 1][W + 1];
        for (int[] row : memo) {
            Arrays.fill(row, -1); // Initialize memo array with -1 (indicating unprocessed state)
        }

        tableReferences = 0; // Initialize the tableReferences variable to 0 before starting the computation.
        return helper(n, W, weights, values);
    }

    /**
     * Helper function to solve the knapsack problem using recursive memoization.
     *
     * @param n       The current item index being considered.
     * @param W       The remaining capacity of the knapsack.
     * @param weights An array of item weights.
     * @param values  An array of item values.
     * @return The maximum value that can be obtained from items with the given weights and values within the knapsack capacity.
     */
    private static int helper(int n, int W, int[] weights, int[] values) {
       tableReferences++;
        if (n == 0 || W == 0) return 0; // Base case: If no items are left or the knapsack has no capacity, return 0.

        if (memo[n][W] != -1) {
            // tableReferences++2; // Counting table references (1 reference per cell accessed)
            return memo[n][W];
        }

        if (weights[n - 1] <= W) {
            // If the current item can fit in the knapsack, choose the maximum value between including and excluding it.
            int includeValue = values[n - 1] + helper(n - 1, W - weights[n - 1], weights, values);
            int excludeValue = helper(n - 1, W, weights, values);

            if (includeValue > excludeValue) {
                memo[n][W] = includeValue;
                selectedItemsMemo[n][W] = true;
            } else {
                memo[n][W] = excludeValue;
            }
        } else {
            // If the current item is too large to fit in the knapsack, exclude it.
            memo[n][W] = helper(n - 1, W, weights, values);
        }

        return memo[n][W];
    }


    /**
     * Reconstructs the optimal solution (selected items) based on the memoization table.
     *
     * @param n             The number of items.
     * @param W             The maximum capacity of the knapsack.
     * @param weights       An array of item weights.
     * @param selectedItems An ArrayList to store the indices of selected items.
     */
    private static void reconstructSolution(int n, int W, int[] weights, List<Integer> selectedItems) {
        while (n > 0 && W > 0) {
            if (selectedItemsMemo[n][W]) {
                selectedItems.add(n); // Add the index of the selected item to the list.
                W -= weights[n - 1]; // Reduce the remaining capacity by the weight of the selected item.
            }
            n--;
        }

        // Reverse the list to get the original order of selected items.
        Collections.reverse(selectedItems);
    }

    public static void main(String[] args) {
        if (args.length < 5) {
            System.out.println("Usage: java KnapsackRM <n> <W> <w.txt> <v.txt> <debug level>");
            return;
        }

        int n = Integer.parseInt(args[0]);
        int W = Integer.parseInt(args[1]);

        int[] weights = new int[n];
        int[] values = new int[n];

        try {
            BufferedReader weightReader = new BufferedReader(new FileReader(args[2]));
            BufferedReader valueReader = new BufferedReader(new FileReader(args[3]));

            for (int i = 0; i < n; i++) {
                StringTokenizer weightTokenizer = new StringTokenizer(weightReader.readLine());
                StringTokenizer valueTokenizer = new StringTokenizer(valueReader.readLine());

                weights[i] = Integer.parseInt(weightTokenizer.nextToken());
                values[i] = Integer.parseInt(valueTokenizer.nextToken());
            }

            weightReader.close();
            valueReader.close();
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        List<Integer> selectedItems = new ArrayList<>(); // List to store the indices of selected items.
        tableReferences = 0; // Reset the tableReferences variable.
        int optimalValue = knapsack(n, W, weights, values); // Solve the knapsack problem and get the optimal value.
        reconstructSolution(n, W, weights, selectedItems); // Reconstruct the selected items based on the memoization table.

        int debugLevel = Integer.parseInt(args[4]);
        if (debugLevel >= 0) {
            // Print the optimal solution if the debug level is greater than or equal to 0.
            System.out.println("Optimal solution:");
            System.out.print("{");
            boolean isFirst = true;
            for (int item : selectedItems) {
                if (!isFirst) {
                    System.out.print(",");
                }
                System.out.print(item);
                isFirst = false;
            }
            System.out.println("}");

            System.out.println("Total Weight: " + W);
            System.out.println("Optimal Value: " + optimalValue);
            System.out.println("Number of table references: " + tableReferences);

            if (debugLevel >= 1) {
                // Optionally, you can print the optimal value table and decision table here.
                printTables(memo, selectedItemsMemo, n, W);
            }
        }
    }

    private static void printTables(int[][] memo, boolean[][] selectedItemsMemo, int n, int W) {
        try {
            BufferedWriter valueTableWriter = new BufferedWriter(new FileWriter("KnapsackRM-VTable"));
            BufferedWriter decisionTableWriter = new BufferedWriter(new FileWriter("KnapsackRM-DTable"));

            // Print the optimal value table
            valueTableWriter.write("Optimal Value Table:\n");
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= W; j++) {
                    valueTableWriter.write(memo[i][j] + "\t");
                }
                valueTableWriter.write("\n");
            }
            valueTableWriter.close();

            // Print the decision table
            decisionTableWriter.write("Decision Table (1 for selected items, 0 for not selected):\n");
            for (int i = 1; i <= n; i++) {
                for (int j = 0; j <= W; j++) {
                    decisionTableWriter.write(selectedItemsMemo[i][j] ? "1\t" : "0\t");
                }
                decisionTableWriter.write("\n");
            }
            decisionTableWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}