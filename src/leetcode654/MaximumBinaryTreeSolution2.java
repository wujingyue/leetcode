package leetcode654;

import java.util.ArrayDeque;
import java.util.Deque;

class MaximumBinaryTreeSolution2 {
	public TreeNode constructMaximumBinaryTree(int[] nums) {
		Deque<TreeNode> stack = new ArrayDeque<TreeNode>();
		for (int i = 0; i < nums.length; ++i) {
			TreeNode newNode = new TreeNode(nums[i]);
			while (!stack.isEmpty() && stack.peek().val < nums[i]) {
				stack.peek().right = newNode.left;
				newNode.left = stack.pop();
			}
			stack.push(newNode);
		}

		assert stack.size() >= 1;
		while (stack.size() > 1) {
			TreeNode x = stack.pop();
			stack.peek().right = x;
		}
		assert stack.size() == 1;

		return stack.peek();
	}
}
