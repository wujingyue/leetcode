package leetcode269;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class AlienDictionaryTest {

	@Test
	void testSample1() {
		String[] words = { "wrt", "wrf", "er", "ett", "rftt" };
		assertEquals("wertf", solution.alienOrder(words));
	}

	@Test
	void testSample2() {
		String[] words = { "z", "x" };
		assertEquals("zx", solution.alienOrder(words));
	}

	@Test
	void testSample3() {
		String[] words = { "z", "x", "z" };
		assertEquals("", solution.alienOrder(words));
	}
	
	@Test
	void testUsedChars() {
		String[] words = { "a", "abc" };
		assertEquals(3, solution.alienOrder(words).length());
	}

	private AlienDictionarySolution solution = new AlienDictionarySolution();
}
