#include <algorithm>
#include <climits>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

struct Neighbor {
  int y;
  int d;
};

struct NodeDistance {
  int x;
  int d;

  bool operator<(const NodeDistance& other) const { return other.d < d; }
};

using Graph = vector<vector<Neighbor>>;

class Solution {
 public:
  int networkDelayTime(const vector<vector<int>>& edges, const int n,
                       int start) {
    start--;

    Graph g(n);
    for (const vector<int>& edge : edges) {
      const int x = edge[0] - 1;
      const int y = edge[1] - 1;
      g[x].push_back(Neighbor{y, edge[2]});
    }

    vector<int> d = Dijkstra(g, start);
    const int max_d = *max_element(d.begin(), d.end());
    return max_d == INT_MAX ? -1 : max_d;
  }

 private:
  vector<int> Dijkstra(const Graph& g, const int start) {
    const int n = g.size();
    vector<int> d(n, INT_MAX);
    priority_queue<NodeDistance> pq;
    vector<int> expanded(n, false);

    pq.push(NodeDistance{start, 0});
    d[start] = 0;

    while (!pq.empty()) {
      const NodeDistance top = pq.top();
      pq.pop();

      if (expanded[top.x]) {
        continue;
      }
      expanded[top.x] = true;

      for (const Neighbor& neighbor : g[top.x]) {
        const int new_d = top.d + neighbor.d;
        if (new_d < d[neighbor.y]) {
          d[neighbor.y] = new_d;
          pq.push(NodeDistance{neighbor.y, new_d});
        }
      }
    }

    return d;
  }
};

TEST(SolutionTest, testSample) {
  Solution s;
  EXPECT_EQ(2, s.networkDelayTime({{2, 1, 1}, {2, 3, 1}, {3, 4, 1}}, 4, 2));
}