package leetcode224;

public class OperatorLevel {
	public OperatorLevel(char operator, int level) {
		this.operator = operator;
		this.level = level;
	}

	public char getOperator() {
		return operator;
	}

	public int getLevel() {
		return level;
	}

	private char operator;
	private int level;
}
