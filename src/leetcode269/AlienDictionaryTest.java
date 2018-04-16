package leetcode269;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class AlienDictionaryTest {

	void verifyAllSolutions(String expectedOrder, String[] words) {
		for (AlienDictionarySolution solution : solutions) {
			assertEquals(expectedOrder, solution.alienOrder(words));
		}
	}
	
	@Test
	void testSample1() {
		String[] words = { "wrt", "wrf", "er", "ett", "rftt" };
		verifyAllSolutions("wertf", words);
	}

	@Test
	void testSample2() {
		String[] words = { "z", "x" };
		verifyAllSolutions("zx", words);
	}

	@Test
	void testSample3() {
		String[] words = { "z", "x", "z" };
		verifyAllSolutions("", words);
	}
	
	@Test
	void testUsedChars() {
		String[] words = { "a", "abc" };
		for (AlienDictionarySolution solution : solutions) {
			assertEquals(3, solution.alienOrder(words).length());
		}
	}

	private AlienDictionarySolution[] solutions = {new AlienDictionarySolution1(), new AlienDictionarySolution2()};
}
