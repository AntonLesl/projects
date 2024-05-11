/**

 The KnightTour class is the entry point of the Knight's Tour program.

 It takes command-line arguments to determine the search option, board size, and initial position.

 The program creates an instance of the KnightBoard class and solves the Knight's Tour problem based on the specified options.

 Author: Anton Leslie.
 */
public class KnightTour {
    public static void main(String[] args) {
        if (args.length < 4) {
            System.out.println("Invalid number of arguments. Usage: java KnightTour <0/1/2> <n> <x> <y>");
            return;
        }

        int option = Integer.parseInt(args[0]);
        int n = Integer.parseInt(args[1]);
        int x = Integer.parseInt(args[2]);
        int y = Integer.parseInt(args[3]);

        KnightBoard knightBoard = new KnightBoard(n, x, y, option);
    }
}
