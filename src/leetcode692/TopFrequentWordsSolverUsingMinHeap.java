package leetcode692;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Iterator;
import java.util.PriorityQueue;

class TopFrequentWordsSolverUsingMinHeap extends TopFrequentWordsSolver {

	@Override
	protected List<String> topKFrequentWordsFromWordCounts(HashMap<String, Integer> wordCounts, int k) {
		PriorityQueue<Map.Entry<String, Integer>> q = new PriorityQueue<Map.Entry<String, Integer>>(k,
				byDescendingFrequency.reversed());
		Iterator<Map.Entry<String, Integer>> iter = wordCounts.entrySet().iterator();
		for (int i = 0; i < k; ++i) {
			q.add(iter.next());
		}

		for (int i = k; i < wordCounts.size(); ++i) {
			Map.Entry<String, Integer> wordCount = iter.next();
			if (byDescendingFrequency.compare(wordCount, q.peek()) < 0) {
				q.remove();
				q.add(wordCount);
			}
		}

		List<String> result = new ArrayList<String>();
		while (!q.isEmpty()) {
			result.add(q.remove().getKey());
		}
		Collections.reverse(result);
		return result;
	}

}
