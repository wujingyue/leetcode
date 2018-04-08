package leetcode652;

import static org.junit.jupiter.api.Assertions.*;

import java.util.List;

import org.junit.jupiter.api.Test;

class FindDuplicateSubtreesTest {

	@Test
	void test() {
		TreeNode x = new TreeNode(1);
		TreeNode y = new TreeNode(1);
		TreeNode z = new TreeNode(2);
		z.left = x;
		z.right = y;

		FindDuplicateSubtreesSolution solution = new FindDuplicateSubtreesSolution3();
		List<TreeNode> duplicatedNodes = solution.findDuplicateSubtrees(z);
		assertEquals(1, duplicatedNodes.size());
		assertEquals(1, duplicatedNodes.get(0).val);
	}

}
