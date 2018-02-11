package leetcode518;

import java.util.Arrays;

class CoinChangeSolution1 implements CoinChangeSolution {

	@Override
	public int change(int amount, int[] coins) {
		int[][] f = new int[coins.length + 1][amount + 1];
		Arrays.fill(f[0], 0);
		f[0][0] = 1;

		for (int i = 1; i <= coins.length; ++i) {
			for (int j = 0; j <= amount; ++j) {
				f[i][j] = 0;
				for (int k = 0; k * coins[i - 1] <= j; ++k) {
					f[i][j] += f[i - 1][j - k * coins[i - 1]];
				}
			}
		}

		for (int i = 0; i <= coins.length; ++i) {
			for (int j = 0; j <= amount; ++j) {
				System.err.print(f[i][j]);
				System.err.print(' ');
			}
			System.err.println();
		}
		return f[coins.length][amount];
	}

}
