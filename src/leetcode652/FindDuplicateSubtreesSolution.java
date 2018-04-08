package leetcode652;

import java.util.ArrayList;
import java.util.List;

interface FindDuplicateSubtreesSolution {
	static boolean areSameSubtrees(TreeNode p, TreeNode q) {
		if (p == null && q == null) {
			return true;
		}
		if (p == null || q == null) {
			return false;
		}
		if (p.val != q.val) {
			return false;
		}
		return areSameSubtrees(p.left, q.left) && areSameSubtrees(p.right, q.right);
	}
	
	static List<TreeNode> collectDuplicatedNodes(List<TreeNode> nodes) {
		List<TreeNode> duplicatedNodes = new ArrayList<TreeNode>();
		int n = nodes.size();
		boolean[] duplicated = new boolean[n];
		for (int i = 0; i < n; ++i) {
			if (duplicated[i])
				continue;
			for (int j = i + 1; j < n; ++j) {
				if (duplicated[j])
					continue;
				if (areSameSubtrees(nodes.get(i), nodes.get(j))) {
					duplicated[i] = true;
					duplicated[j] = true;
				}
			}
			if (duplicated[i]) {
				duplicatedNodes.add(nodes.get(i));
			}
		}
		return duplicatedNodes;
	}
	
	public List<TreeNode> findDuplicateSubtrees(TreeNode root);
}
