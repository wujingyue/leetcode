#include <queue>
#include <vector>

#include "benchmark/benchmark.h"
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
    BFS(g, 0, parent);

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
  void BFS(const Graph& g, const int start, vector<int>& parent) {
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
      const int x = q.front();
      q.pop();
      for (const int y : g[x]) {
        if (parent[y] == -1) {
          parent[y] = x;
          q.push(y);
        }
      }
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

static void BM_Sample(benchmark::State& state) {
  Solution s;
  for (auto _ : state) {
    s.minReorder(5, {{1, 0}, {1, 2}, {3, 2}, {3, 4}});
  }
}
BENCHMARK(BM_Sample)->Unit(benchmark::kMillisecond);