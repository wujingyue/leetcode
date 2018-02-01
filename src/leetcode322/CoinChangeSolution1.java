package leetcode322;

import java.util.Arrays;

class CoinChangeSolution1 implements CoinChangeSolution {

	@Override
	public int coinChange(int[] coins, int amount) {
		// f[i][j] indicates the minimum number of coins needed to make up amount j with
		// only coins[i..coins.length-1].
		int[][] f = new int[coins.length + 1][amount + 1];
		Arrays.fill(f[coins.length], Integer.MAX_VALUE);
		f[coins.length][0] = 0;

		for (int i = coins.length - 1; i >= 0; --i) {
			for (int j = 0; j <= amount; ++j) {
				f[i][j] = f[i + 1][j];
				int maxK = j / coins[i];
				for (int k = 1; k <= maxK; ++k) {
					int prev = f[i + 1][j - k * coins[i]];
					if (prev < Integer.MAX_VALUE) {
						f[i][j] = Integer.min(f[i][j], prev + k);
					}
				}
			}
		}

		return (f[0][amount] == Integer.MAX_VALUE ? -1 : f[0][amount]);
	}
}
