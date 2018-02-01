package leetcode692;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class TopFrequentWordsSolverUsingPartition extends TopFrequentWordsSolver {

	static int partition(ArrayList<Map.Entry<String, Integer>> a, int left, int right) {
		Map.Entry<String, Integer> pivot = a.get(right);
		int i = left;
		int j = right - 1;
		while (i <= j) {
			while (i <= j && byDescendingFrequency.compare(a.get(i), pivot) <= 0) {
				++i;
			}
			while (i <= j && byDescendingFrequency.compare(a.get(j), pivot) > 0) {
				--j;
			}
			if (i < j) {
				Collections.swap(a, i, j);
			}
		}
		Collections.swap(a, i, right);
		return i;
	}

	@Override
	protected List<String> topKFrequentWordsFromWordCounts(HashMap<String, Integer> wordCounts, int k) {
		ArrayList<Map.Entry<String, Integer>> flatWordCounts = new ArrayList<Map.Entry<String, Integer>>(
				wordCounts.entrySet());
		int low = 0;
		int high = flatWordCounts.size() - 1;
		while (low < high) {
			int pivotIndex = partition(flatWordCounts, low, high);
			if (pivotIndex == k - 1) {
				break;
			}
			if (pivotIndex < k - 1) {
				low = pivotIndex + 1;
			} else {
				high = pivotIndex - 1;
			}
		}

		Collections.sort(flatWordCounts.subList(0, k), byDescendingFrequency);

		ArrayList<String> result = new ArrayList<String>();
		for (int i = 0; i < k; ++i) {
			result.add(flatWordCounts.get(i).getKey());
		}
		return result;
	}

}
