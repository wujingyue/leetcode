package leetcode269;

import java.util.Arrays;

class AlienDictionarySolution {
	enum Color {
		WHITE, GRAY, BLACK,
	}

	public String alienOrder(String[] words) {
		boolean[][] partialOrder = collectPartialOrders(words);

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
				if (depthFirstSearch(i, partialOrder, colors, postOrder)) {
					return "";
				}
			}
		}

		return postOrder.reverse().toString();
	}

	boolean depthFirstSearch(int i, boolean[][] partialOrder, Color[] colors, StringBuilder postOrder) {
		if (colors[i] == Color.GRAY) {
			return true;
		}
		if (colors[i] == Color.BLACK) {
			return false;
		}

		assert colors[i] == Color.WHITE;
		colors[i] = Color.GRAY;
		for (int j = 0; j < 26; ++j) {
			if (partialOrder[i][j]) {
				if (depthFirstSearch(j, partialOrder, colors, postOrder)) {
					return true;
				}
			}
		}
		colors[i] = Color.BLACK;
		postOrder.append((char) ('a' + i));
		return false;
	}

	boolean[][] collectPartialOrders(String[] words) {
		boolean[][] partialOrder = new boolean[26][26];
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
			partialOrder[a.charAt(j) - 'a'][b.charAt(j) - 'a'] = true;
		}
		return partialOrder;
	}
}
