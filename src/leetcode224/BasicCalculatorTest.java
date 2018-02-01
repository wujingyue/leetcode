package leetcode224;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class BasicCalculatorTest {

	@BeforeAll
	static void setUpBeforeClass() throws Exception {
		calculator = new BasicCalculator();
	}

	@Test
	void testValidExpressions() {
		assertEquals(-10, calculator.calculate("12+34-56"));
		assertEquals(-10, calculator.calculateNoParentheses("12+34-56"));

		assertEquals(2, calculator.calculate("1 + 1"));
		assertEquals(2, calculator.calculateNoParentheses("1 + 1"));

		assertEquals(3, calculator.calculate(" 2-1 + 2 "));
		assertEquals(3, calculator.calculateNoParentheses(" 2-1 + 2 "));

		assertEquals(23, calculator.calculate("(1+(4+5+2)-3)+(6+8)"));

		assertEquals(-4, calculator.calculate("1-(2+3)"));

		assertEquals(-4, calculator.calculate("1-2-3"));
	}

	private static BasicCalculator calculator;
}
