/**

 The Position class represents a position on the chessboard.

 It holds the x and y coordinates, as well as additional properties

 like the distance to the board's border and the count of onward moves.

 Author: Anton Leslie.
 */
public class Position {
    private final int x;
    private final int y;
    private final int distanceToBorder;
    private final int onwardMoves;

    /**

     Constructs a Position object with the given coordinates and properties.
     @param x the x coordinate
     @param y the y coordinate
     @param distanceToBorder the distance to the board's border
     @param onwardMoves the count of onward moves
     */
    public Position(int x, int y, int distanceToBorder, int onwardMoves) {
        this.x = x;
        this.y = y;
        this.distanceToBorder = distanceToBorder;
        this.onwardMoves = onwardMoves;
    }
    /**

     Returns the x coordinate of the position.
     @return the x coordinate
     */
    public int getX() {
        return x;
    }
    /**

     Returns the y coordinate of the position.
     @return the y coordinate
     */
    public int getY() {
        return y;
    }
    /**

     Returns the distance to the board's border from the position.
     @return the distance to the border
     */
    public int getDistanceToBorder() {
        return distanceToBorder;
    }
    /**

     Returns the count of onward moves from the position.
     @return the count of onward moves
     */
    public int getOnwardMoves() {
        return onwardMoves;
    }
}
