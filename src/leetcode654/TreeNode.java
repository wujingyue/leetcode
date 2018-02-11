package leetcode654;

class TreeNode {
	public TreeNode(int x) {
		val = x;
		left = null;
		right = null;
	}

	public int val;
	public TreeNode left;
	public TreeNode right;

	public static String toString(TreeNode root) {
		if (root == null) {
			return "()";
		}
		return String.format("(%d,%s,%s)", root.val, toString(root.left), toString(root.right));
	}

	public String toString() {
		return toString(this);
	}
}