package leetcode516;

public class LongestPalindromicSubsequenceSolution2 implements LongestPalindromicSubsequenceSolution {

	@Override
	public int longestPalindromeSubseq(String s) {
		int n = s.length();
		if (n == 0) {
			return 0;
		}

		int[] f = new int[n];
		for (int i = n - 1; i >= 0; --i) {
			f[i] = 1;
			int mIPlusOneJMinusOne = 0;
			for (int j = i + 1; j < n; ++j) {
				int mIJ;
				if (s.charAt(i) == s.charAt(j)) {
					mIJ = 2 + mIPlusOneJMinusOne;
				} else {
					mIJ = Math.max(f[j - 1], f[j]);
				}
				mIPlusOneJMinusOne = f[j];
				f[j] = mIJ;
			}
		}
		return f[n - 1];
	}

}
