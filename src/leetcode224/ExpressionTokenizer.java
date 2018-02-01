package leetcode224;

public class ExpressionTokenizer {
	public ExpressionTokenizer(String expression) {
		this.expression = expression;
		this.readPosition = 0;
	}

	public ExpressionToken nextToken() {
		// Skip spaces.
		while (readPosition < expression.length() && expression.charAt(readPosition) == ' ') {
			readPosition++;
		}

		// Return null if the stream ends.
		if (readPosition >= expression.length()) {
			return null;
		}

		char ch = expression.charAt(readPosition);
		readPosition++;
		if (Character.isDigit(ch)) {
			// Read consecutive digits that form a number.
			int number = ch - '0';
			while (readPosition < expression.length() && Character.isDigit(expression.charAt(readPosition))) {
				number = number * 10 + expression.charAt(readPosition) - '0';
				readPosition++;
			}
			return new ExpressionToken(number);
		}

		if (ch == '+' || ch == '-' || ch == '(' || ch == ')') {
			return new ExpressionToken(ch);
		}

		throw new IllegalArgumentException("Unexpected character '" + ch + "'");
	}

	private String expression;
	// The index of the character to be read next.
	private int readPosition;
}
