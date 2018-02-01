package leetcode322;

import java.util.Arrays;

class CoinChangeSolution4 implements CoinChangeSolution {

	@Override
	public int coinChange(int[] coins, int amount) {
		int[] g = new int[amount + 1];
		Arrays.fill(g, Integer.MAX_VALUE);
		g[0] = 0;

		for (int i = coins.length - 1; i >= 0; --i) {
			for (int j = 0; j <= amount; ++j) {
				if (j >= coins[i]) {
					int prev = g[j - coins[i]];
					if (prev < Integer.MAX_VALUE) {
						g[j] = Integer.min(g[j], prev + 1);
					}
				}
			}
		}

		return (g[amount] == Integer.MAX_VALUE ? -1 : g[amount]);
	}
}
