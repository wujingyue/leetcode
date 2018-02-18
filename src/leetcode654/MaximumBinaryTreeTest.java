package leetcode654;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class MaximumBinaryTreeTest {

	void verifyAllSolutions(String expected, int[] nums) {
		for (MaximumBinaryTreeSolution solution : solutions) {
			assertEquals("(6,(3,(),(2,(),(1,(),()))),(5,(0,(),()),()))",
					solution.constructMaximumBinaryTree(nums).toString());
		}
	}

	@Test
	void testSample() {
		int[] nums = { 3, 2, 1, 6, 0, 5 };
		verifyAllSolutions("(6,(3,(),(2,(),(1,(),()))),(5,(0,(),()),()))", nums);
	}

	private MaximumBinaryTreeSolution[] solutions = { new MaximumBinaryTreeSolution1(),
			new MaximumBinaryTreeSolution2() };
}
