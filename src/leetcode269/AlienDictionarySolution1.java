package leetcode269;

import java.util.Arrays;

class AlienDictionarySolution1 implements AlienDictionarySolution {
	enum Color {
		WHITE, GRAY, BLACK,
	}

	@Override
	public String alienOrder(String[] words) {
		boolean[][] constraints = collectConstraints(words);

		boolean[] used = new boolean[26];
		for (int i = 0; i < words.length; ++i) {
			for (int j = 0; j < words[i].length(); ++j) {
				used[words[i].charAt(j) - 'a'] = true;
			}
		}

		Color[] colors = new Color[26];
		Arrays.fill(colors, Color.WHITE);
		StringBuilder postOrder = new StringBuilder();
		for (int i = 0; i < 26; ++i) {
			if (used[i]) {
				if (depthFirstSearch(i, constraints, colors, postOrder)) {
					return "";
				}
			}
		}

		return postOrder.reverse().toString();
	}

	boolean depthFirstSearch(int i, boolean[][] constraints, Color[] marks, StringBuilder postOrder) {
		if (marks[i] == Color.GRAY) {
			return true;
		}
		if (marks[i] == Color.BLACK) {
			return false;
		}

		assert marks[i] == Color.WHITE;
		marks[i] = Color.GRAY;
		for (int j = 0; j < 26; ++j) {
			if (constraints[i][j]) {
				if (depthFirstSearch(j, constraints, marks, postOrder)) {
					return true;
				}
			}
		}
		marks[i] = Color.BLACK;
		postOrder.append((char) ('a' + i));
		return false;
	}

}
