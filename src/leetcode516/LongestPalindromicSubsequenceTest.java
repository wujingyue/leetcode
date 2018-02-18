package leetcode516;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class LongestPalindromicSubsequenceTest {

	void verifyAllSolutions(int expected, String input) {
		for (LongestPalindromicSubsequenceSolution solution : solutions) {
			assertEquals(expected, solution.longestPalindromicSubseq(input));
		}
	}

	@Test
	void testSample() {
		verifyAllSolutions(4, "bbbab");
		verifyAllSolutions(2, "cbbd");
	}

	private LongestPalindromicSubsequenceSolution[] solutions = { new LongestPalindromicSubsequenceSolution1() };
}
