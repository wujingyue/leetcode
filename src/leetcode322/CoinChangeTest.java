package leetcode322;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class CoinChangeTest {
	void testAllSolutions(int[] coins, int amount, int expected) {
		for (CoinChangeSolution solution : coinChangeSolutions) {
			assertEquals(expected, solution.coinChange(coins, amount));
		}
	}

	@Test
	void testValid() {
		int[] coins = { 1, 2, 5 };
		testAllSolutions(coins, 11, 3);
	}

	@Test
	void testInvalid() {
		int[] coins = { 2 };
		testAllSolutions(coins, 3, -1);
	}

	@Test
	void testZeroAmount() {
		int[] coins = { 2 };
		testAllSolutions(coins, 0, 0);
	}

	@Test
	void testZeroCoins() {
		int[] coins = {};
		testAllSolutions(coins, 0, 0);
	}

	private CoinChangeSolution[] coinChangeSolutions = { new CoinChangeSolution1(), new CoinChangeSolution2(),
			new CoinChangeSolution3(), new CoinChangeSolution4() };
}
