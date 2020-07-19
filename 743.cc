#include <algorithm>
#include <climits>
#include <queue>
#include <vector>

#include "gtest/gtest.h"
#include "priority_queue.h"

using namespace std;

struct Neighbor {
  int y;
  int d;
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

    PriorityQueue<int> pq = Dijkstra(g, start);
    int max_d = INT_MIN;
    for (int x = 0; x < n; x++) {
      max_d = max(max_d, *pq.GetNode(x));
    }
    return max_d == INT_MAX ? -1 : max_d;
  }

 private:
  PriorityQueue<int> Dijkstra(const Graph& g, const int start) {
    const int n = g.size();

    vector<int> distances;
    distances.reserve(n);
    for (int x = 0; x < n; x++) {
      distances.push_back(x == start ? 0 : INT_MAX);
    }

    PriorityQueue<int> pq(std::move(distances));
    pq.Insert(start);

    while (!pq.Empty()) {
      const int x = pq.Pop();
      const int dx = *pq.GetNode(x);

      for (const Neighbor& neighbor : g[x]) {
        const int y = neighbor.y;
        int* dy = pq.GetNode(y);
        const int new_d = dx + neighbor.d;
        if (new_d < *dy) {
          *dy = new_d;
          const int j = pq.GetPosition(y);
          if (j == -1) {
            pq.Insert(y);
          } else {
            pq.Adjust(j);
          }
        }
      }
    }

    return pq;
  }
};

TEST(SolutionTest, testSample) {
  Solution s;
  EXPECT_EQ(2, s.networkDelayTime({{2, 1, 1}, {2, 3, 1}, {3, 4, 1}}, 4, 2));
}

TEST(SolutionTest, testNotConnected) {
  Solution s;
  EXPECT_EQ(-1, s.networkDelayTime({}, 2, 1));
}
