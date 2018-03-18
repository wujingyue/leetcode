package leetcode516;

public class LongestPalindromicSubsequenceSolution1 implements LongestPalindromicSubsequenceSolution {

	@Override
	public int longestPalindromeSubseq(String s) {
		int n = s.length();
		if (n == 0) {
			return 0;
		}

		int[][] m = new int[n][n];
		for (int i = 0; i < n; ++i) {
			m[i][i] = 1;
			if (i + 1 < n) {
				m[i + 1][i] = 0;
			}
		}
		for (int i = n - 1; i >= 0; --i) {
			for (int j = i + 1; j < n; ++j) {
				if (s.charAt(i) == s.charAt(j)) {
					m[i][j] = 2 + m[i + 1][j - 1];
				} else {
					m[i][j] = Math.max(m[i + 1][j], m[i][j - 1]);
				}
			}
		}
		return m[0][n - 1];
	}

}
