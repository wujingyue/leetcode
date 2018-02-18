package leetcode654;

import java.util.ArrayDeque;
import java.util.Deque;

class MaximumBinaryTreeSolution2 implements MaximumBinaryTreeSolution {

	@Override
	public TreeNode constructMaximumBinaryTree(int[] nums) {
		Deque<TreeNode> stack = new ArrayDeque<TreeNode>();
		for (int cur : nums) {
			TreeNode lastPopped = null;
			while (!stack.isEmpty() && stack.peek().val < cur) {
				lastPopped = stack.pop();
			}

			TreeNode curNode = new TreeNode(cur);
			curNode.left = lastPopped;
			if (!stack.isEmpty()) {
				stack.peek().right = curNode;
			}
			stack.push(curNode);
		}
		return stack.getLast();
	}
}
