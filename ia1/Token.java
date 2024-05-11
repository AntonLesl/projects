public class Token {

	private final String token; // "id"
	private final String lexeme; // "x"

	public Token(String token, String lexeme) {
		this.token=token;
		this.lexeme=lexeme;
	}

	public Token(String token) {
		this(token,token);
	}

	public String tok() { return token; }

	public String lex() { return lexeme; }

	public boolean equals(Token t) {
		return token.equals(t.token);
	}

	public String toString() {
		return "<"+tok()+","+lex()+">";
	}

}