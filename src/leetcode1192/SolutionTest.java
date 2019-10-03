package leetcode1192;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.List;

import org.junit.jupiter.api.Test;

class SolutionTest {

  @Test
  void test() {
    List<List<Integer>> criticalConnections = s.criticalConnections(4,
        toList(new int[][] { { 0, 1 }, { 1, 2 }, { 2, 0 }, { 1, 3 } }));
    assertEquals(criticalConnections.size(), 1);

    List<Integer> criticalConnection = criticalConnections.get(0);
    assertTrue((criticalConnection.get(0) == 1
        && criticalConnection.get(1) == 3)
        || (criticalConnection.get(0) == 3 && criticalConnection.get(1) == 1));
  }

  private List<List<Integer>> toList(int[][] connections) {
    List<List<Integer>> list = new ArrayList<>();
    for (int[] connection : connections) {
      List<Integer> sublist = new ArrayList<Integer>(2);
      sublist.add(connection[0]);
      sublist.add(connection[1]);
      list.add(sublist);
    }
    return list;
  }

  private Solution s = new Solution();
}
