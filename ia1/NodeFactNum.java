public class NodeFactNum extends NodeFact {

	private final String num;

	public NodeFactNum(String num) {
		this.num=num;
	}

	public double eval(Environment env) throws EvalException {
		return Integer.parseInt(num);
	}

	public String code() { return num; }

}
