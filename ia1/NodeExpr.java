public class NodeExpr extends Node {
	// Fields
	private final NodeTerm term;
	private NodeAddop addop;
	private NodeExpr expr;

	// Constructor
	public NodeExpr(NodeTerm term, NodeAddop addop, NodeExpr expr) {
		this.term = term;
		this.addop = addop;
		this.expr = expr;
	}

	// Methods
	/**
	 * Appends an expression node to the end of the current expression.
	 * If the current expression already has an expression node, the method is called recursively
	 * on the next expression node until an empty slot is found.
	 * @param expr The expression node to append.
	 */
	public void append(NodeExpr expr) {
		if (this.expr == null) {
			this.addop = expr.addop;
			this.expr = expr;
			expr.addop = null;
		} else {
			this.expr.append(expr);
		}
	}

	/**
	 * Evaluates the expression by recursively evaluating the term node and expression node (if any)
	 * using the addop node (if any).
	 * @param env The environment in which to evaluate the expression.
	 * @return The evaluated result.
	 * @throws EvalException if there is an error during evaluation.
	 */
	public double eval(Environment env) throws EvalException {
		return expr == null
				? term.eval(env)
				: addop.op(expr.eval(env), term.eval(env));
	}

	/**
	 * Returns the code representation of the expression in the form of a string.
	 * @return The code representation of the expression.
	 */
	public String code() {
		return (expr == null ? "" : expr.code() + addop.code()) + term.code();
	}
}

