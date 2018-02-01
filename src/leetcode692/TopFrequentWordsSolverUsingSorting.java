package leetcode692;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class TopFrequentWordsSolverUsingSorting extends TopFrequentWordsSolver {

	@Override
	protected List<String> topKFrequentWordsFromWordCounts(HashMap<String, Integer> wordCounts, int k) {
		List<Map.Entry<String, Integer>> flatWordCounts = new ArrayList<Map.Entry<String, Integer>>(
				wordCounts.entrySet());
		Collections.sort(flatWordCounts, byDescendingFrequency);

		List<String> result = new ArrayList<String>();
		for (int i = 0; i < k; ++i) {
			result.add(flatWordCounts.get(i).getKey());
		}
		return result;
	}
}
