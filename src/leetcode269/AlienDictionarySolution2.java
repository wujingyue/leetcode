package leetcode269;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.stream.IntStream;

class AlienDictionarySolution2 implements AlienDictionarySolution {

	@Override
	public String alienOrder(String[] words) {
		boolean[][] constraints = collectConstraints(words);

		boolean[] used = new boolean[26];
		for (int i = 0; i < words.length; ++i) {
			for (int j = 0; j < words[i].length(); ++j) {
				used[words[i].charAt(j) - 'a'] = true;
			}
		}

		StringBuilder topologicalOrder = new StringBuilder();
		int[] incomingEdges = new int[26];
		Deque<Integer> nodesWithNoIncomingEdges = new ArrayDeque<Integer>();
		
		for (int y = 0; y < 26; ++y) {
			for (int x = 0; x < 26; ++x) {
				if (constraints[x][y]) {
					incomingEdges[y]++;
				}
			}
			if (incomingEdges[y] == 0 && used[y]) {
				nodesWithNoIncomingEdges.offer(y);
			}
		}
		
		while (!nodesWithNoIncomingEdges.isEmpty()) {
			int x = nodesWithNoIncomingEdges.remove();
			topologicalOrder.append((char)('a' + x));
			for (int y = 0; y < 26; ++y) {
				if (constraints[x][y]) {
					incomingEdges[y]--;
					if (incomingEdges[y] == 0) {
						nodesWithNoIncomingEdges.offer(y);
					}
				}
			}
		}
		
		if (IntStream.of(incomingEdges).sum() == 0) {
			return topologicalOrder.toString();
		} else {
			return "";
		}
	}

}
