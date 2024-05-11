import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

// Author Anton Leslie
//The KnapsackDP class is a Java implementation of solving the knapsack problem using a bottom-up dynamic programming approach. 
// The program takes command-line arguments, including the number of items, the maximum capacity of the knapsack, 
// and the file names containing item weights and values. 
// It also provides an optional debug level argument to control the level of output.

public class KnapsackDP {
    public static void main(String[] args) {
        // Check the number of command-line arguments
        if (args.length < 4 || args.length > 5) {
            System.out.println("Usage: java KnapsackDP <n> <W> <w.txt> <v.txt> [<debug level>]");
            return;
        }

        int n = Integer.parseInt(args[0]); // Number of items
        int W = Integer.parseInt(args[1]); // Maximum capacity of the knapsack
        String wFile = args[2]; // File name containing item weights
        String vFile = args[3]; // File name containing item values
        int debugLevel = 0;

        // If provided, read the debug level from command-line arguments
        if (args.length == 5) {
            debugLevel = Integer.parseInt(args[4]);
        }

        int[] weights = new int[n + 1]; // Array to store item weights
        int[] values = new int[n + 1]; // Array to store item values

        try {
            // Read item weights and values from the provided files
            BufferedReader wReader = new BufferedReader(new FileReader(wFile));
            BufferedReader vReader = new BufferedReader(new FileReader(vFile));

            for (int i = 1; i <= n; i++) {
                weights[i] = Integer.parseInt(wReader.readLine());
                values[i] = Integer.parseInt(vReader.readLine());
            }

            wReader.close();
            vReader.close();
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        int[][] dp = new int[n + 1][W + 1];
        boolean[][] decisionTable = new boolean[n + 1][W + 1];
        int tableReferences = 0;

        // Bottom-up dynamic programming approach to solve the knapsack problem
        for (int i = 1; i <= n; i++) {
            for (int w = 1; w <= W; w++) {
                if (weights[i] <= w) {
                    int valuePrevRow = dp[i - 1][w];
                    int valueWithItem = dp[i - 1][w - weights[i]] + values[i];
                    tableReferences += 2; // Increment tableReferences for the two cell accesses

                    if (valueWithItem >= valuePrevRow) {
                        dp[i][w] = valueWithItem;
                        decisionTable[i][w] = true; // Mark the item as taken in the decision table
                    } else {
                        dp[i][w] = valuePrevRow;
                    }
                } else {
                    dp[i][w] = dp[i - 1][w];
                    tableReferences++; // Increment tableReferences for the cell access
                }
            }
        }

        // Retrieve the optimal solution (selected items)
        List<Integer> selectedItems = new ArrayList<>();
        int totalWeight = W;
        int optimalValue = dp[n][W];

        for (int i = n; i > 0 && optimalValue > 0; i--) {
            if (dp[i][totalWeight] != dp[i - 1][totalWeight]) {
                selectedItems.add(i); // Add the item number (index + 1) to the selectedItems list
                totalWeight -= weights[i];
                optimalValue -= values[i];
            }
        }

        // Print results based on the debug level
         switch (debugLevel) {
            case 1:
                saveTableToFile(dp, "KnapsackDP-VTable"); // Save the value table to a file
                saveTableToFile(decisionTable, "KnapsackDP-DTable"); // Save the decision table to a file
                printSummary(selectedItems, W, dp[n][W], tableReferences); // Print the summary of the optimal solution
                break;
            case 0:
            default:
                printSummary(selectedItems, W, dp[n][W], tableReferences); // Print the summary of the optimal solution
                break;
        }
    }

    // Method to save a 2D table to a file
    private static void saveTableToFile(int[][] table, String fileName) {
        try {
            FileWriter writer = new FileWriter(fileName);
            int rows = table.length;
            int cols = table[0].length;

            for (int i = 1; i < rows; i++) {
                for (int j = 1; j < cols; j++) {
                    // For the first column, add extra spaces based on the row number
                    String formattedValue = String.format("%3d", table[i][j]);
                    writer.write(formattedValue + " ");
                }
                writer.write("\n");
            }

            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Method to save the decision table to a file
    private static void saveTableToFile(boolean[][] decisionTable, String fileName) {
        try {
            FileWriter writer = new FileWriter(fileName);
            int rows = decisionTable.length;
            int cols = decisionTable[0].length;

            for (int i = 1; i < rows; i++) {
                for (int j = 1; j < cols; j++) {
                    String formattedValue = decisionTable[i][j] ? "1" : "0";
                    writer.write(formattedValue + "   ");
                }
                writer.write("\n");
            }

            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    // Method to print the summary of the optimal solution
    private static void printSummary(List<Integer> selectedItems, int totalWeight, int optimalValue, int tableReferences) {
        System.out.println("Optimal solution:");
        System.out.print("{");
        boolean isFirst = true;

        // Sort the selected items list
        selectedItems.sort(Integer::compareTo);

        // Print the selected items
        for (int item : selectedItems) {
            if (!isFirst) {
                System.out.print(",");
            }
            System.out.print(item);
            isFirst = false;
        }

        System.out.println("}");
        System.out.println("Total Weight: " + totalWeight);
        System.out.println("Optimal Value: " + optimalValue);
        System.out.println("Number of table references: " + tableReferences);
    }
}
