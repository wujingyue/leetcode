#include "gtest/gtest.h"

using namespace std;

using Graph = vector<vector<int>>;

class Solution {
 public:
  int minReorder(const int n, const vector<vector<int>>& edges) {
    Graph g(n);
    for (const vector<int>& e : edges) {
      const int x = e[0];
      const int y = e[1];
      g[x].push_back(y);
      g[y].push_back(x);
    }

    vector<int> parent(n, -1);
    parent[0] = 0;
    DFS(g, 0, parent);

    int num_changes = 0;
    for (const vector<int>& e : edges) {
      const int x = e[0];
      const int y = e[1];
      if (x == parent[y]) {
        num_changes++;
      }
    }
    return num_changes;
  }

 private:
  void DFS(const Graph& g, const int x, vector<int>& parent) {
    for (const int y : g[x]) {
      if (parent[y] != -1) {
        continue;
      }
      parent[y] = x;
      DFS(g, y, parent);
    }
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(2, s.minReorder(5, {{1, 0}, {1, 2}, {3, 2}, {3, 4}}));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(0, s.minReorder(3, {{1, 0}, {2, 0}}));
}
