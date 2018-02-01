package leetcode224;

import java.util.ArrayDeque;
import java.util.Deque;

public class BasicCalculator {
	private static void evaluateTopOperator(Deque<OperatorLevel> operatorStack, Deque<Integer> operandStack) {
		int rightOperand = operandStack.removeLast();
		int leftOperand = operandStack.removeLast();
		char op = operatorStack.removeLast().getOperator();

		int result = 0;
		switch (op) {
		case '+':
			result = leftOperand + rightOperand;
			break;
		case '-':
			result = leftOperand - rightOperand;
			break;
		default:
			assert false : String.format("Operator '%c' not supported.", op);
		}

		operandStack.addLast(result);
	}

	public int calculate(String expression) {
		Deque<OperatorLevel> operatorStack = new ArrayDeque<OperatorLevel>();
		Deque<Integer> operandStack = new ArrayDeque<Integer>();

		int parenthesisLevel = 0;
		ExpressionTokenizer tokenizer = new ExpressionTokenizer(expression);
		for (ExpressionToken token = tokenizer.nextToken(); token != null; token = tokenizer.nextToken()) {
			switch (token.getType()) {
			case NUMBER:
				operandStack.addLast(token.intValue());
				break;
			case PARENTHESIS:
				char parenthesis = token.charValue();
				if (parenthesis == '(') {
					parenthesisLevel++;
				} else {
					parenthesisLevel--;
				}
				break;
			case OPERATOR:
				while (!operatorStack.isEmpty() && operatorStack.getLast().getLevel() >= parenthesisLevel) {
					evaluateTopOperator(operatorStack, operandStack);
				}
				operatorStack.addLast(new OperatorLevel(token.charValue(), parenthesisLevel));
				break;
			}
		}
		while (!operatorStack.isEmpty()) {
			evaluateTopOperator(operatorStack, operandStack);
		}

		return operandStack.getLast();
	}

	public int calculateNoParentheses(String expression) {
		int result = 0;
		char lastOperator = '+';
		ExpressionTokenizer tokenizer = new ExpressionTokenizer(expression);
		for (ExpressionToken token = tokenizer.nextToken(); token != null; token = tokenizer.nextToken()) {
			if (token.getType() == ExpressionToken.Type.OPERATOR) {
				lastOperator = token.charValue();
			} else {
				if (lastOperator == '+') {
					result += token.intValue();
				} else {
					result -= token.intValue();
				}
			}
		}
		return result;
	}
}
