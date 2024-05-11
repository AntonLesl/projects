

public class Main {


	public static void main(String[] args) {

		// Instantiate a new Parser object
		Parser parser = new Parser();

		// Instantiate a new Environment object
		Environment env = new Environment();

		// Initialize an empty string to store the parsed code
		String code = "";

		// Loop through each argument passed in from the command line
		for (String prog : args) {

			try {
				// Parse the argument string and store the resulting node
				Node node = parser.parse(prog);

				// Evaluate the node in the given environment
				node.eval(env);

				// Append the generated code for this node to the overall code string
				code += node.code();

			} catch (Exception e) {
				// If there was an error during parsing or evaluation, print the error message
				System.err.println(e);
			}
		}

		// Instantiate a new Code object with the combined code string and environment
		new Code(code, env);
	}
}




