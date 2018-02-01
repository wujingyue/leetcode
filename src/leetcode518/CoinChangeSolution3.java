package leetcode518;

import java.util.Arrays;

public class CoinChangeSolution3 implements CoinChangeSolution {

	@Override
	public int change(int amount, int[] coins) {
		int[] g = new int[amount + 1];
		Arrays.fill(g, 0);
		g[0] = 1;

		for (int i = 1; i <= coins.length; ++i) {
			for (int j = 0; j <= amount; ++j) {
				if (coins[i - 1] <= j) {
					g[j] += g[j - coins[i - 1]];
				}
			}
		}

		return g[amount];
	}

}
