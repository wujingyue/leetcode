package leetcode516;

public class LongestPalindromicSubsequenceSolution1 implements LongestPalindromicSubsequenceSolution {

	@Override
	public int longestPalindromicSubseq(String s) {
		int n = s.length();
		int[][] m = new int[n][n];
		for (int i = 0; i < n; ++i) {
			m[i][i] = 1;
		}
		for (int i = n - 1; i >= 0; --i) {
			for (int j = i + 1; j < n; ++j) {
				m[i][j] = Math.max(m[i + 1][j], m[i][j - 1]);
				if (s.charAt(i) == s.charAt(j)) {
					m[i][j] = Math.max(m[i][j], 2 + (i + 1 <= j - 1 ? m[i + 1][j - 1] : 0));
				}
			}
		}
		return m[0][n - 1];
	}

}
