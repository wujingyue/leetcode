package leetcode652;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class FindDuplicateSubtreesSolution3 implements FindDuplicateSubtreesSolution {

	private int numberNodes(TreeNode root, Map<TreeNode, Integer> nodeNumbering,
			Map<Expression, Integer> expressionNumbering) {
		if (root == null) {
			return 0;
		}
		int leftNumber = numberNodes(root.left, nodeNumbering, expressionNumbering);
		int rightNumber = numberNodes(root.right, nodeNumbering, expressionNumbering);
		Expression expression = new Expression(root.val, leftNumber, rightNumber);
		Integer rootNumber = expressionNumbering.get(expression);
		if (rootNumber == null) {
			rootNumber = nextNumber;
			nextNumber++;
			expressionNumbering.put(expression, rootNumber);
		}
		nodeNumbering.put(root, rootNumber);
		return rootNumber;
	}

	@Override
	public List<TreeNode> findDuplicateSubtrees(TreeNode root) {
		Map<TreeNode, Integer> nodeNumbering = new HashMap<TreeNode, Integer>();
		Map<Expression, Integer> expressionNumbering = new HashMap<Expression, Integer>();
		nextNumber = 1; // 0 is reserved for null
		numberNodes(root, nodeNumbering, expressionNumbering);

		// TODO: use a vector instead of a hashmap.
		Map<Integer, Integer> numNodesWithNumbering = new HashMap<Integer, Integer>();
		List<TreeNode> result = new ArrayList<TreeNode>();
		for (Map.Entry<TreeNode, Integer> entry : nodeNumbering.entrySet()) {
			TreeNode node = entry.getKey();
			int number = entry.getValue();
			int count = numNodesWithNumbering.getOrDefault(number, 0);
			if (count == 1) {
				result.add(node);
			}
			numNodesWithNumbering.put(number, count + 1);
		}
		return result;
	}

	private int nextNumber;
}
