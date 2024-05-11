// This class, and its subclasses,
// collectively model parse-tree nodes.
// Each kind of node can be eval()-uated,
// and/or code()-generated.
public abstract class Node {


	// Defining a protected integer variable called "pos"
	protected int pos = 0;

	// Defining an abstract method called eval that takes an instance of the Environment class as a parameter and throws an EvalException
	public double eval(Environment env) throws EvalException {
		throw new EvalException(pos, "cannot eval() node!");
	}

	// Defining an abstract method called code that returns an empty string
	public String code() {
		return "";
	}

}
