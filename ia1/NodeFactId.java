public class NodeFactId extends NodeFact {

	private final String id;

	public NodeFactId(int pos, String id) {
		this.pos=pos;
		this.id=id;
	}

	public double eval(Environment env) throws EvalException {
		return env.get(id);
	}

	public String code() { return id; }

}
