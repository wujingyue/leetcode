package leetcode692;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.HashMap;

class TopFrequentWordsSolverUsingMaxHeap extends TopFrequentWordsSolver {

	@Override
	protected List<String> topKFrequentWordsFromWordCounts(HashMap<String, Integer> wordCounts, int k) {
		List<String> result = new ArrayList<String>();
		PriorityQueue<Map.Entry<String, Integer>> q = new PriorityQueue<Map.Entry<String, Integer>>(wordCounts.size(),
				byDescendingFrequency);
		for (Map.Entry<String, Integer> entry : wordCounts.entrySet()) {
			q.add(entry);
		}
		for (int i = 0; i < k; ++i) {
			result.add(q.remove().getKey());
		}
		return result;
	}
}
