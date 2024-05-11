/**

 A custom checked exception class for representing evaluation errors.
 */
public class EvalException extends Exception {

	/**

	 The position at which the evaluation error occurred.
	 */
	private int pos;
	/**

	 The error message associated with the evaluation error.
	 */
	private String msg;
	/**

	 Constructs an instance of EvalException with the specified position and message.
	 @param pos the position at which the evaluation error occurred
	 @param msg the error message associated with the evaluation error
	 */
	public EvalException(int pos, String msg) {
		this.pos=pos;
		this.msg=msg;
	}
	/**

	 Returns a string representation of this EvalException instance.
	 The string contains the error message, position, and additional information.
	 @return a string representation of this EvalException instance
	 */
	public String toString() {
		return "eval error"
				+", pos="+pos
				+", "+msg;
	}
}