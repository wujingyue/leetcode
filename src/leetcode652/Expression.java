package leetcode652;

class Expression {
	Expression(int rootValue, int leftNumber, int rightNumber) {
		this.rootValue = rootValue;
		this.leftNumber = leftNumber;
		this.rightNumber = rightNumber;
	}

	@Override
	public int hashCode() {
		int hashcode = 17;
		hashcode = hashcode * 31 + rootValue;
		hashcode = hashcode * 31 + leftNumber;
		hashcode = hashcode * 31 + rightNumber;
		return hashcode;
	}

	@Override
	public boolean equals(Object other) {
		if (!(other instanceof Expression)) {
			return false;
		}
		Expression otherExpression = (Expression) other;
		return rootValue == otherExpression.rootValue && leftNumber == otherExpression.leftNumber
				&& rightNumber == otherExpression.rightNumber;
	}

	private final int rootValue;
	private final int leftNumber;
	private final int rightNumber;
}
