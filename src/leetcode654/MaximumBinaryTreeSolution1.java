package leetcode654;

class MaximumBinaryTreeSolution1 implements MaximumBinaryTreeSolution {

	@Override
	public TreeNode constructMaximumBinaryTree(int[] nums) {
		return construct(nums, 0, nums.length - 1);
	}

	private TreeNode construct(int[] nums, int left, int right) {
		if (left > right) {
			return null;
		}

		int maxI = left;
		for (int i = left + 1; i <= right; ++i) {
			if (nums[i] > nums[maxI]) {
				maxI = i;
			}
		}

		TreeNode node = new TreeNode(nums[maxI]);
		node.left = construct(nums, left, maxI - 1);
		node.right = construct(nums, maxI + 1, right);
		return node;
	}
}
