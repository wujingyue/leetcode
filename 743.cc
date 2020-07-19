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

struct NodeInfo {
  int d;
  int pos_in_pq;

  bool operator<(const NodeInfo& other) const { return d < other.d; }
};

using Graph = vector<vector<Neighbor>>;

class PriorityQueue {
 public:
  PriorityQueue(vector<NodeInfo>&& nodes) { nodes_.swap(nodes); }
  PriorityQueue(const PriorityQueue&) = delete;
  PriorityQueue& operator=(const PriorityQueue&) = delete;
  PriorityQueue(PriorityQueue&&) = default;

  NodeInfo* GetNode(const int x) { return &nodes_[x]; }

  void Insert(const int x) {
    const int i = order_.size();
    order_.push_back(x);
    nodes_[x].pos_in_pq = i;
    PercolateUp(i);
  }

  int Pop() {
    const int x = order_[0];
    nodes_[x].pos_in_pq = -1;

    const int y = order_.back();
    order_.pop_back();

    if (!order_.empty()) {
      order_[0] = y;
      nodes_[y].pos_in_pq = 0;
      PercolateDown(0);
    }

    return x;
  }

  bool Empty() const { return order_.empty(); }

  void Adjust(const int i) {
    PercolateUp(i);
    PercolateDown(i);
  }

 private:
  bool SatisfiesHeapOrder(const int x, const int y) {
    return !(nodes_[y] < nodes_[x]);
  }

  void PercolateUp(int j) {
    int y = order_[j];
    while (j > 0) {
      int i = (j - 1) / 2;
      int x = order_[i];
      if (SatisfiesHeapOrder(x, y)) {
        break;
      }
      order_[j] = x;
      nodes_[x].pos_in_pq = j;
      j = i;
    }
    order_[j] = y;
    nodes_[y].pos_in_pq = j;
  }

  void PercolateDown(int i) {
    const int n = order_.size();

    int x = order_[i];
    while (i * 2 + 1 < n) {
      int j = i * 2 + 1;
      if (j + 1 < (int)order_.size() &&
          nodes_[order_[j + 1]] < nodes_[order_[j]]) {
        j++;
      }
      int y = order_[j];
      if (SatisfiesHeapOrder(x, y)) {
        break;
      }
      order_[i] = y;
      nodes_[y].pos_in_pq = i;
      i = j;
    }
    order_[i] = x;
    nodes_[x].pos_in_pq = i;
  }

  vector<int> order_;
  vector<NodeInfo> nodes_;
};

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

    PriorityQueue pq = Dijkstra(g, start);
    int max_d = INT_MIN;
    for (int x = 0; x < n; x++) {
      max_d = max(max_d, pq.GetNode(x)->d);
    }
    return max_d == INT_MAX ? -1 : max_d;
  }

 private:
  PriorityQueue Dijkstra(const Graph& g, const int start) {
    const int n = g.size();

    vector<NodeInfo> nodes;
    nodes.reserve(n);
    for (int x = 0; x < n; x++) {
      nodes.push_back(NodeInfo{x == start ? 0 : INT_MAX, -1});
    }

    PriorityQueue pq(std::move(nodes));
    pq.Insert(start);

    while (!pq.Empty()) {
      const int x = pq.Pop();

      for (const Neighbor& neighbor : g[x]) {
        NodeInfo* node_y = pq.GetNode(neighbor.y);
        const int new_d = pq.GetNode(x)->d + neighbor.d;
        if (new_d < node_y->d) {
          node_y->d = new_d;
          const int j = node_y->pos_in_pq;
          if (j == -1) {
            pq.Insert(neighbor.y);
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
