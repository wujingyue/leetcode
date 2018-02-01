package leetcode692;

import static org.junit.jupiter.api.Assertions.*;

import java.util.List;

import org.junit.jupiter.api.Test;

class TopFrequentWordsSolverTest {

	void checkResultsFromAllSolversMatch(String[] words, int k) {
		List<String> result = null;
		for (TopFrequentWordsSolver solver : solvers) {
			List<String> currentResult = solver.topKFrequentWords(words, k);
			System.err.println(String.format("Testing %s...", solver.getClass().getName()));
			if (result == null) {
				result = currentResult;
			} else {
				assertIterableEquals(result, currentResult);
			}
		}
	}

	@Test
	void testSample() {
		String[] words = { "i", "love", "leetcode", "i", "love", "coding" };
		checkResultsFromAllSolversMatch(words, 2);
	}

	private TopFrequentWordsSolver[] solvers = { new TopFrequentWordsSolverUsingSorting(),
			new TopFrequentWordsSolverUsingMaxHeap(), new TopFrequentWordsSolverUsingMinHeap(),
			new TopFrequentWordsSolverUsingPartition() };
}
