public class NodeFactExpr extends NodeFact {

	private final NodeExpr expr;

	public NodeFactExpr(NodeExpr expr) {
		this.expr=expr;
	}

	public double eval(Environment env) throws EvalException {
		return expr.eval(env);
	}

	public String code() { return "("+expr.code()+")"; }

}