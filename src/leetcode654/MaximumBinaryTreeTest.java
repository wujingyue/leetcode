package leetcode654;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class MaximumBinaryTreeTest {

	@Test
	void testSample() {
		int[] nums = { 3, 2, 1, 6, 0, 5 };
		assertEquals("(6,(3,(),(2,(),(1,(),()))),(5,(0,(),()),()))",
				solution1.constructMaximumBinaryTree(nums).toString());
		assertEquals("(6,(3,(),(2,(),(1,(),()))),(5,(0,(),()),()))",
				solution2.constructMaximumBinaryTree(nums).toString());
	}

	private MaximumBinaryTreeSolution1 solution1 = new MaximumBinaryTreeSolution1();
	private MaximumBinaryTreeSolution2 solution2 = new MaximumBinaryTreeSolution2();
}
