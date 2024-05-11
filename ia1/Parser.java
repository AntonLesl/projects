// This class is a recursive-descent parser,
// modeled after the programming language's grammar.
// It constructs and has-a Scanner for the program
// being parsed.

public class Parser {

	private Scanner scanner;
	/**

	 Matches the current token with the input string s, and moves the scanner to the next token.
	 Throws a SyntaxException if the current token does not match s.
	 @param s The string to match with the current token
	 @throws SyntaxException if the current token does not match s
	 */
	private void match(String s) throws SyntaxException {
		scanner.match(new Token(s));
	}
	/**

	 Returns the current token without moving the scanner.
	 @return The current token
	 @throws SyntaxException if there is no current token
	 */
	private Token curr() throws SyntaxException {
		return scanner.curr();
	}
	/**

	 Returns the position of the current token in the input string.
	 @return The position of the current token
	 */
	private int pos() {
		return scanner.pos();
	}
/**

 Parses a multiplication or division operator and returns a NodeMulop.
 If the current token is "*", returns a NodeMulop representing multiplication.
 If the current token is "/", returns a NodeMulop representing division.
 If the current token is neither "*", nor "/", returns null.
 @return A NodeMulop representing the multiplication or division operator, or null if the current token is neither "*" nor "/"
 @throws SyntaxException if there is a syntax error in the input string
 */
	private NodeMulop parseMulop() throws SyntaxException {
		if (curr().equals(new Token("*"))) {
			match("*");
			return new NodeMulop(pos(), "*");
		}
		if (curr().equals(new Token("/"))) {
			match("/");
			return new NodeMulop(pos(), "/");
		}
		return null;
	}

	/**

	 Parses an addop (addition or subtraction) from the input stream.
	 @throws SyntaxException if the input stream does not contain a valid addop
	 @return a NodeAddop representing the parsed addop wasnt able to completely figure out
	 */
	private NodeAddop parseAddop() throws SyntaxException {
		if (curr().equals(new Token("+"))) {
			match("+"); // pos now 7
			return new NodeAddop(pos(), "+"); // creates and returns NodeAddop(7, "+")
		}
		if (curr().equals(new Token("-"))) {
			match("-");
			return new NodeAddop(pos(), "-");
		}
		return null;
	}





	private NodeFact parseFact() throws SyntaxException {

			if (curr().equals(new Token("("))) { // curr token "num" lexeme "1"
				match("(");
				NodeExpr expr = parseExpr();
				match(")");
				return new NodeFactExpr(expr);
			}
			if (curr().equals(new Token("id"))) {
				Token id = curr();
				match("id");
				return new NodeFactId(pos(), id.lex());
			}
			if (curr().equals(new Token("-"))) { // negative number
				Token negative = curr();
				match("-");
				NodeFact fact = parseFact();
				return new Fact(negative.lex(), fact);
			}
			Token num = curr();
			match("num");
			return new NodeFactNum(num.lex());
		}

	private NodeTerm parseTerm() throws SyntaxException {
		NodeFact fact = parseFact();
		NodeMulop mulop = parseMulop();
		if (mulop == null)
			return new NodeTerm(fact, null, null);
		NodeTerm term = parseTerm();
		term.append(new NodeTerm(fact, mulop, null));
		return term;
	}

	private NodeExpr parseExpr() throws SyntaxException {
		NodeTerm term = parseTerm();
		NodeAddop addop = parseAddop();
		if (addop == null)
			return new NodeExpr(term, null, null);
		NodeExpr expr = parseExpr();
		expr.append(new NodeExpr(term, addop, null));
		return expr;
	}

	private NodeAssn parseAssn() throws SyntaxException {
		Token id = curr();
		match("id");
		match("=");
		NodeExpr expr = parseExpr();
		NodeAssn assn = new NodeAssn(id.lex(), expr);
		return assn;
	}

	private NodeStmt parseStmt() throws SyntaxException {
		NodeAssn assn = parseAssn();
		match(";");
		NodeStmt stmt = new NodeStmt(assn);
		return stmt;
	}

	public Node parse(String program) throws SyntaxException {
		scanner = new Scanner(program);
		scanner.next();
		NodeStmt stmt = parseStmt();
		match("EOF");
		return stmt;
	}

}
