package leetcode652;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class FindDuplicateSubtreesSolution2 implements FindDuplicateSubtreesSolution {

	int collectNodesAndHashcodes(TreeNode root, Map<Integer, List<TreeNode>> hashcodeToNodes) {
		if (root == null) {
			return 0;
		}
		int hashcode = 17;
		hashcode = hashcode * 31 + collectNodesAndHashcodes(root.left, hashcodeToNodes);
		hashcode = hashcode * 31 + root.val;
		hashcode = hashcode * 31 + collectNodesAndHashcodes(root.right, hashcodeToNodes);
		List<TreeNode> nodesWithHashcode = hashcodeToNodes.get(hashcode);
		if (nodesWithHashcode == null) {
			nodesWithHashcode = new ArrayList<TreeNode>();
			hashcodeToNodes.put(hashcode, nodesWithHashcode);
		}
		nodesWithHashcode.add(root);
		return hashcode;
	}

	@Override
	public List<TreeNode> findDuplicateSubtrees(TreeNode root) {
		Map<Integer, List<TreeNode>> hashcodeToNodes = new HashMap<Integer, List<TreeNode>>();
		collectNodesAndHashcodes(root, hashcodeToNodes);

		List<TreeNode> result = new ArrayList<TreeNode>();
		for (List<TreeNode> nodesWithSameHashcode : hashcodeToNodes.values()) {
			result.addAll(FindDuplicateSubtreesSolution.collectDuplicatedNodes(nodesWithSameHashcode));
		}
		return result;
	}
}
