public class NodeStmt extends Node {

	private final NodeAssn assn;

	public NodeStmt(NodeAssn assn) {
		this.assn=assn;
	}

	public double eval(Environment env) throws EvalException {
		return assn.eval(env);
	}

	public String code() { return assn.code(); }

}
