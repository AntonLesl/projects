public class NodeAddop extends Node {

	// Defining a private final instance variable called addop
	private final String addop;

	// Defining a constructor that takes two arguments - an int called pos and a String called addop
	public NodeAddop(int pos, String addop) {
		this.pos = pos;
		this.addop = addop;
	}

	// Defining a method called op that takes two double arguments and throws an EvalException if addop is invalid
	public double op(double o1, double o2) throws EvalException {

		// If addop is "+", return the sum of o1 and o2
		if (addop.equals("+")) {
			return o1 + o2;
		}

		// If addop is "-", return the difference of o1 and o2
		if (addop.equals("-")) {
			return o1 - o2;
		}

		// If addop is not "+" or "-", throw an EvalException with a message
		throw new EvalException(pos, "bogus addop: " + addop);
	}

	// Defining a method called code that returns the addop instance variable as a String
	public String code() {
		return addop;
	}


}
