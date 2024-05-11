import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;




/* Overview Comment:

This code is a Java implementation of the Critical Path Method (CPM),
which is a project management technique used to determine the critical path in a network of activities
 and identify the minimum time required to complete a project.
  author Anton Leslie.
 */

public class CriticalPath {
    private static final ArrayList<String> node1 = new ArrayList<String>();
    private static final ArrayList<Integer> matrixValues = new ArrayList<Integer>();
    //Format for the final string output
    private static final String format = "%1$-20s %2$-6s %3$-9s %4$-5s\n";
    private static List<String>[] affectedNode;
    private static int[] mainVal;
    private static int maxCost;

    public static void main(String[] args) {
        // Check if the user provided the input file name as a command-line argument
        if (args.length != 1) {
            System.out.println("Please input the activity-node graph file.");
            System.exit(0);
        }

        // Read the input file and parse the data to initialize the graph
        File input = new File(args[0]);
        parseFile(input);

        // Create a set to store all task nodes (activities) in the graph
        HashSet<Node> tasks = new HashSet<Node>();

        // Create an array of Node objects to represent all the tasks
        Node[] nodes = new Node[node1.size()];

        // Initialize each Node object with its name and duration
        for (int i = 0; i < node1.size(); i++) {
            nodes[i] = new Node(node1.get(i), mainVal[i]);
        }

        // Populate the dependencies of each Node
        for (int i = 0; i < node1.size(); i++) {
            Node[] nodeList = new Node[affectedNode[i].size()];
            for (int j = 0; j < affectedNode[i].size(); j++) {
                for (int k = 0; k < node1.size(); k++) {
                    if (affectedNode[i].get(j) == nodes[k].getName()) {
                        nodeList[j] = nodes[k];
                    }
                }
            }
            nodes[i].setDependsOn(nodeList);
            tasks.add(nodes[i]);
        }

        // Find the critical path in the project using the criticalPath method
        Node[] result = criticalPath(tasks);

        // Print the critical path details in the specified format
        print(result);

        // Indicate that the output is printed in alphabetical order of task names
        System.out.println("\n");
    }


    private static Node[] criticalPath(Set<Node> nodes) {
        // Initialize two sets to keep track of processed and remaining nodes
        HashSet<Node> done = new HashSet<Node>();
        HashSet<Node> remaining = new HashSet<Node>(nodes);

        // Variable to track if progress has been made in the while loop
        boolean progress = false;

        // Main loop to find the critical path using forward pass technique
        while (!remaining.isEmpty()) {
            progress = false;
            // Iterate over the remaining nodes
            for (Iterator<Node> iter = remaining.iterator(); iter.hasNext(); ) {
                Node node = iter.next();
                // If all dependencies of the node are processed, calculate the critical cost
                if (done.containsAll(node.dependsOn)) {
                    int crit = 0;
                    // Find the maximum critical cost among its dependencies
                    for (Node n : node.dependsOn) {
                        if (n.critCost > crit) {
                            crit = n.critCost;
                        }
                    }
                    // Set the critical cost for the current node and mark it as done
                    node.critCost = crit + node.cost;
                    done.add(node);
                    iter.remove();
                    progress = true;
                }
            }
            // If no progress is made in a pass, there might be a negative cycle in the graph
            if (!progress) {
                throw new RuntimeException("Negative Cycle, program has been stopped.");
            }
        }

        // Calculate the maximum cost (total duration) of the project and set latest start/finish times
        maxCost(nodes);

        // Find the initial nodes (nodes with no dependencies) for backward pass
        HashSet<Node> initNodes = initials(nodes);

        // Calculate early start and finish times for each initial node and its dependencies
        earlyCalc(initNodes);

        // Convert the set of processed nodes into an array and sort it alphabetically
        Node[] sol = done.toArray(new Node[0]);
        Arrays.sort(sol, new Comparator<Node>() {
            public int compare(Node x, Node y) {
                return x.name.compareTo(y.name);
            }
        });

        return sol;
    }

    private static void parseFile(File file) {
        try {
            // Create a Scanner to read the input file
            Scanner scan = new Scanner(file);

            // Create another Scanner to parse the first line containing node names
            Scanner nameScan = new Scanner(scan.nextLine());

            // Extract node names from the first line and add them to the nodeNames ArrayList
            while (nameScan.hasNext()) {
                if (!node1.contains(nameScan.hasNext())) {
                    node1.add(nameScan.next());
                }
            }

            // Read the rest of the input file to extract the matrix values (activity durations)
            while (scan.hasNextLine()) {
                // Loop through each node name
                for (int i = 0; i < node1.size(); i++) {
                    // Create a new Scanner to parse the values in the current line
                    Scanner valueScan = new Scanner(scan.nextLine());
                    valueScan.next(); // Skip the node name
                    // Loop through the remaining values, representing the activity durations
                    while (valueScan.hasNext()) {
                        // Convert the value to an integer and add it to the allMatrixValues ArrayList
                        matrixValues.add(Integer.parseInt(valueScan.next()));
                    }
                }
            }

            // Create a temporary ArrayList and copy allMatrixValues into it
            ArrayList<Integer> temp = new ArrayList<Integer>(matrixValues);
            // Assign the temporary ArrayList back to allMatrixValues (unnecessary assignment)
            temp = matrixValues;

            // Call the parseArray method to populate the dependentNodes and mainVal arrays
            parseArray(temp);

        } catch (FileNotFoundException e) {
            // Handle the case where the input file is not found
            e.printStackTrace();
            System.out.println("File Not Found.");
            System.exit(0);
        }
    }


    @SuppressWarnings("unchecked")
    private static void parseArray(ArrayList input) {
        // Initialize variables for processing
        int index = 0;
        int mod = node1.size();

        // Create the dependentNodes and mainVal arrays to store node dependencies and durations

        affectedNode = new List[node1.size()];
        mainVal = new int[node1.size()];

        // Loop through each node in the nodeNames ArrayList
        for (int i = 0; i < node1.size(); i++) {
            // Initialize an ArrayList to store the dependent nodes for the current node
            affectedNode[i] = new ArrayList<>();

            // Loop through each node in the nodeNames ArrayList again (for matrix processing)
            for (int j = 0; j < node1.size(); j++) {
                // Check if the matrix value is not -1 (indicating a dependency)
                if (matrixValues.get(index) != -1) {
                    // For all nodes except the first one (index 0), add the dependent node to the ArrayList
                    if (i != 0) {
                        affectedNode[i].add(node1.get(j));
                    }
                    // Assign the mainVal for the current node based on the matrix value
                    mainVal[index % mod] = matrixValues.get(index);
                }
                // Move to the next matrix value
                index++;
            }
        }
    }

    private static void earlyCalc(HashSet<Node> initialNodes) {
        // Calculate the early start and early finish times for each initial node (activity)
        for (Node inits : initialNodes) {
            // The early start time for an initial node is always 0
            inits.earlyStart = 0;
            // The early finish time for an initial node is its cost (duration) itself
            inits.earlyFinish = inits.cost;
            // Call the setEarly method to calculate the early start/finish times for dependencies
            setEarly(inits);
        }
    }


    private static void setEarly(Node initialNode) {
        // Calculate the early start/finish times for a node and its dependencies recursively
        int compTime = initialNode.earlyFinish;
        for (Node n : initialNode.dependsOn) {
            // Check if the dependency's early start time is less than or equal to the current completion time
            if (compTime >= n.earlyStart) {
                // Update the early start time for the dependency node
                n.earlyStart = compTime;
                // Update the early finish time for the dependency node
                n.earlyFinish = compTime + n.cost;
            }
            // Recursively call setEarly for the dependency node to handle its dependencies
            setEarly(n);
        }
    }


    private static HashSet<Node> initials(Set<Node> nodes) {
        // Find the initial nodes (activities with no dependencies) in the graph
        HashSet<Node> remaining = new HashSet<Node>(nodes);
        for (Node n : nodes) {
            for (Node nd : n.dependsOn) {
                // Remove the dependency node from the remaining set since it is not initial
                remaining.remove(nd);
            }
        }
        // Return the set of initial nodes
        return remaining;
    }


    protected static void maxCost(Set<Node> nodes) {
        // Find the maximum critical cost (total duration) among all nodes in the graph
        int max = -1;
        for (Node n : nodes) {
            if (n.critCost > max) {
                max = n.critCost;
            }
        }
        // Update the maxCost variable with the calculated maximum cost
        maxCost = max;

        // Calculate the latest start and finish times for each node in the graph
        for (Node n : nodes) {
            // Set the latest start and finish times for each node based on the critical path
            n.setLatest();
            // If the node is the first one (index 0) in nodeNames, set its latest start time
            if (n.name == node1.get(0)) {
                n.setLatestStart();
            }
        }
    }


    // This method prints the critical path analysis results for the project activities.
// The critical path is determined by sorting the nodes based on earlyFinish time and then alphabetically by name.
    protected static void print(Node[] nodes) {
        // Sort nodes based on earlyFinish and then alphabetically by name
        Arrays.sort(nodes, new Comparator<Node>() {
            public int compare(Node x, Node y) {
                int lateFinishComparison = Integer.compare(x.lateFinish, y.lateFinish);
                if (lateFinishComparison != 0) {
                    return lateFinishComparison;
                }
                int earlyFinishComparison = Integer.compare(x.earlyFinish, y.earlyFinish);
                if (earlyFinishComparison != 0) {
                    return earlyFinishComparison;
                }
                return x.name.compareTo(y.name);
            }
        });

        // Print the header for the critical path analysis table
        System.out.println("Activity Node   EC     LC   SlackTime");
        System.out.println("-------------------------------------");
        // Print the details of each activity in the critical path analysis table
        for (Node n : nodes) {
            System.out.format(format, (Object[]) n.toStringArray());
        }
    }

    // Nested class representing an activity node in the project.
    protected static class Node {
        private final int cost;
        private final String name;
        private final HashSet<Node> dependsOn = new HashSet<>();
        private int critCost;
        private int earlyStart;
        private int earlyFinish;
        private int lateStart;
        private int lateFinish;

        // Constructor to initialize the activity with its name and duration
        private Node(String name, int cost) {
            this.name = name;
            this.cost = cost;
            this.earlyFinish = -1; // Default earlyFinish value
        }

        // Get the name of the activity
        private String getName() {
            return this.name;
        }

        // Set the dependencies of the activity
        private void setDependsOn(Node... dependencies) {
            Collections.addAll(this.dependsOn, dependencies);
        }

        // Check if this activity depends on a specific node, recursively checking dependencies
        private boolean isDependent(Node n) {
            if (dependsOn.contains(n)) {
                return true;
            }
            for (Node depNode : dependsOn) {
                if (depNode.isDependent(n)) {
                    return true;
                }
            }
            return false;
        }

        // Calculate and set the latest start and finish times for the activity
        private void setLatest() {
            lateStart = maxCost - critCost;
            lateFinish = lateStart + cost;
        }

        // Set the latest start and finish times for the first activity (index 0)
        private void setLatestStart() {
            lateFinish = 0;
            lateStart = 0;
        }

        // Convert the activity details to a string array for printing
        private String[] toStringArray() {
            String[] toString = {name, earlyFinish + "", lateFinish + "", lateStart - earlyStart + ""};
            return toString;
        }
    }
}