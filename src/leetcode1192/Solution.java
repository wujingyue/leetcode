package leetcode1192;

import java.util.ArrayList;
import java.util.List;

class DepthFirstSearch {
  public DepthFirstSearch(List<List<Integer>> a) {
    this.a = a;
    discovery = new int[a.size()];
    low = new int[a.size()];
    clock = 0;
  }

  void search(int x, int parent, List<List<Integer>> criticalConnections) {
    assert discovery[x] == 0;
    clock++;
    discovery[x] = clock;
    low[x] = clock;
    for (int y : a.get(x)) {
      if (discovery[y] == 0) {
        search(y, x, criticalConnections);
        low[x] = Math.min(low[x], low[y]);
      } else if (y != parent) {
        low[x] = Math.min(low[x], discovery[y]);
      }
      if (low[y] > discovery[x]) {
        List<Integer> criticalConnection = new ArrayList<>(2);
        criticalConnection.add(x);
        criticalConnection.add(y);
        criticalConnections.add(criticalConnection);
      }
    }
  }

  private List<List<Integer>> a;
  private int[] discovery;
  private int[] low;
  private int clock;
}

public class Solution {
  public List<List<Integer>> criticalConnections(int n,
      List<List<Integer>> connections) {
    List<List<Integer>> a = new ArrayList<>(n);
    for (int i = 0; i < n; i++) {
      a.add(new ArrayList<Integer>());
    }
    for (List<Integer> connection : connections) {
      int x = connection.get(0);
      int y = connection.get(1);
      a.get(x).add(y);
      a.get(y).add(x);
    }

    List<List<Integer>> criticals = new ArrayList<>();
    DepthFirstSearch dfs = new DepthFirstSearch(a);
    dfs.search(0, -1, criticals);
    return criticals;
  }
}
