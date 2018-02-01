package leetcode692;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.util.List;

// For LeetCode submissions.
class Solution {
	public List<String> topKFrequent(String[] words, int k) {
		TopFrequentWordsSolver solver = new TopFrequentWordsSolverUsingSorting();
		return solver.topKFrequentWords(words, k);
	}
}

abstract class TopFrequentWordsSolver {

	public List<String> topKFrequentWords(String[] words, int k) {
		HashMap<String, Integer> wordCounts = countWords(words);
		return topKFrequentWordsFromWordCounts(wordCounts, Math.min(k, wordCounts.size()));
	}

	private HashMap<String, Integer> countWords(String[] words) {
		HashMap<String, Integer> wordCounts = new HashMap<String, Integer>();
		for (String word : words) {
			int count = wordCounts.getOrDefault(word, 0);
			wordCounts.put(word, count + 1);
		}
		return wordCounts;
	}

	protected abstract List<String> topKFrequentWordsFromWordCounts(HashMap<String, Integer> wordCounts, int k);

	protected static Comparator<Map.Entry<String, Integer>> byDescendingFrequency = Comparator
			.comparing(Map.Entry<String, Integer>::getValue).reversed()
			.thenComparing(Map.Entry<String, Integer>::getKey);
}
