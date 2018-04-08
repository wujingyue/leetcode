package leetcode269;

import java.util.Arrays;

class AlienDictionarySolution {
	enum Color {
		WHITE, GRAY, BLACK,
	}

	public String alienOrder(String[] words) {
		boolean[][] order = collectOrders(words);

		boolean[] used = new boolean[26];
		for (int i = 0; i < words.length; ++i) {
			for (int j = 0; j < words[i].length(); ++j) {
				used[words[i].charAt(j) - 'a'] = true;
			}
		}

		Color[] marks = new Color[26];
		Arrays.fill(marks, Color.WHITE);
		StringBuilder postOrder = new StringBuilder();
		for (int i = 0; i < 26; ++i) {
			if (used[i]) {
				if (depthFirstSearch(i, order, marks, postOrder)) {
					return "";
				}
			}
		}

		return postOrder.reverse().toString();
	}

	boolean depthFirstSearch(int i, boolean[][] order, Color[] marks, StringBuilder postOrder) {
		if (marks[i] == Color.GRAY) {
			return true;
		}
		if (marks[i] == Color.BLACK) {
			return false;
		}

		assert marks[i] == Color.WHITE;
		marks[i] = Color.GRAY;
		for (int j = 0; j < 26; ++j) {
			if (order[i][j]) {
				if (depthFirstSearch(j, order, marks, postOrder)) {
					return true;
				}
			}
		}
		marks[i] = Color.BLACK;
		postOrder.append((char) ('a' + i));
		return false;
	}

	boolean[][] collectOrders(String[] words) {
		boolean[][] order = new boolean[26][26];
		for (int i = 0; i + 1 < words.length; ++i) {
			String a = words[i];
			String b = words[i + 1];
			int j = 0;
			while (j < a.length() && j < b.length() && a.charAt(j) == b.charAt(j)) {
				++j;
			}
			if (j >= a.length()) {
				continue;
			}

			assert j < a.length();
			assert j < b.length();
			order[a.charAt(j) - 'a'][b.charAt(j) - 'a'] = true;
		}
		return order;
	}
}
