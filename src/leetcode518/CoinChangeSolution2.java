package leetcode518;

import java.util.Arrays;

public class CoinChangeSolution2 implements CoinChangeSolution {

	@Override
	public int change(int amount, int[] coins) {
		int[][] f = new int[coins.length + 1][amount + 1];
		Arrays.fill(f[0], 0);
		f[0][0] = 1;

		for (int i = 1; i <= coins.length; ++i) {
			for (int j = 0; j <= amount; ++j) {
				f[i][j] = f[i - 1][j] + (coins[i - 1] <= j ? f[i][j - coins[i - 1]] : 0);
			}
		}

		return f[coins.length][amount];
	}

}
