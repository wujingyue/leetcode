package leetcode518;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class CoinChangeTest {
	private void testAllSolutions(int[] coins, int amount, int expected) {
		for (CoinChangeSolution solution : solutions) {
			assertEquals(expected, solution.change(amount, coins));
		}
	}

	@Test
	void testValid1() {
		int[] coins = { 1, 2, 5 };
		testAllSolutions(coins, 5, 4);
	}

	@Test
	void testValid2() {
		int[] coins = { 10 };
		testAllSolutions(coins, 10, 1);
	}	

	@Test
	void testInvalid() {
		int[] coins = { 3 };
		testAllSolutions(coins, 2, 0);
	}	

	private CoinChangeSolution[] solutions = { new CoinChangeSolution1(), new CoinChangeSolution2(),
			new CoinChangeSolution3() };
}
