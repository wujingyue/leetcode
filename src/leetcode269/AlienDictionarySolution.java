package leetcode269;

interface AlienDictionarySolution {

	public String alienOrder(String[] words);

	default boolean[][] collectConstraints(String[] words) {
		boolean[][] constraints = new boolean[26][26];
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
			constraints[a.charAt(j) - 'a'][b.charAt(j) - 'a'] = true;
		}
		return constraints;
	}
}
