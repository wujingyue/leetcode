#include "gtest/gtest.h"

using namespace std;

enum EdgeType {
  INCOMING,
  OUTGOING,
};

struct Edge {
  int neighbor;
  EdgeType type;
};

using Graph = vector<vector<Edge>>;

class Solution {
 public:
  int minReorder(const int n, const vector<vector<int>>& edges) {
    Graph g(n);
    for (const vector<int>& e : edges) {
      const int x = e[0];
      const int y = e[1];
      g[x].push_back(Edge{y, OUTGOING});
      g[y].push_back(Edge{x, INCOMING});
    }

    return DFS(g, 0, 0);
  }

 private:
  int DFS(const Graph& g, const int x, const int parent) {
    int changes = 0;
    for (const Edge& e : g[x]) {
      const int y = e.neighbor;
      if (y == parent) {
        continue;
      }
      if (e.type == OUTGOING) {
        changes++;
      }
      changes += DFS(g, y, x);
    }
    return changes;
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
