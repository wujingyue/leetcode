package leetcode224;

public class ExpressionToken {
	enum Type {
		NUMBER, OPERATOR, PARENTHESIS
	}

	public ExpressionToken(char c) {
		this.type = (c == '(' || c == ')' ? Type.PARENTHESIS : Type.OPERATOR);
		this.charValue = c;
	}

	public ExpressionToken(int number) {
		this.type = Type.NUMBER;
		this.intValue = number;
	}

	public Type getType() {
		return type;
	}

	public int intValue() {
		if (type != Type.NUMBER) {
			throw new IllegalArgumentException(String.format("intValue is called on a token of type %d", type));
		}
		return intValue;
	}

	public char charValue() {
		if (type == Type.NUMBER) {
			throw new IllegalArgumentException(String.format("charValue is called on a token of type %d", type));
		}
		return charValue;
	}

	private Type type;
	private char charValue;
	private int intValue;
}
