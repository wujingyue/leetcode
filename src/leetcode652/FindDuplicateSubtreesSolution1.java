package leetcode652;

import java.util.ArrayList;
import java.util.List;

class FindDuplicateSubtreesSolution1 implements FindDuplicateSubtreesSolution {

	void collectAllNodes(TreeNode root, List<TreeNode> allNodes) {
		if (root == null) {
			return;
		}
		allNodes.add(root);
		collectAllNodes(root.left, allNodes);
		collectAllNodes(root.right, allNodes);
	}

	@Override
	public List<TreeNode> findDuplicateSubtrees(TreeNode root) {
		List<TreeNode> allNodes = new ArrayList<TreeNode>();
		collectAllNodes(root, allNodes);
		return FindDuplicateSubtreesSolution.collectDuplicatedNodes(allNodes);
	}
}
