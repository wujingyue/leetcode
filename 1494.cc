#include <climits>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

using Graph = vector<vector<int>>;

class DFSWithMemoization {
 public:
  DFSWithMemoization(const Graph& g, const int k)
      : g_(g),
        n_(g.size()),
        k_(k),
        incoming_edges_(n_),
        num_semesters_(1 << n_) {}

  int MinNumberSemesters() {
    fill(incoming_edges_.begin(), incoming_edges_.end(), 0);
    for (int x = 0; x < n_; x++) {
      for (const int y : g_[x]) {
        incoming_edges_[y]++;
      }
    }

    fill(num_semesters_.begin(), num_semesters_.end(), -1);
    return Search((1 << n_) - 1);
  }

 private:
  int Search(int remaining_nodes) {
    int& result = num_semesters_[remaining_nodes];
    if (result >= 0) {
      return result;
    }

    if (remaining_nodes == 0) {
      result = 0;
      return result;
    }

    int num_nodes_to_select = 0;
    for (int x = 0; x < n_ && num_nodes_to_select < k_; x++) {
      if ((remaining_nodes & (1 << x)) && incoming_edges_[x] == 0) {
        num_nodes_to_select++;
      }
    }
    assert(num_nodes_to_select > 0);

    result = INT_MAX;
    for (const int selection :
         ValidSelections(remaining_nodes, num_nodes_to_select)) {
      for (int x = 0; x < n_; x++) {
        if (selection & (1 << x)) {
          for (const int y : g_[x]) {
            incoming_edges_[y]--;
          }
        }
      }

      result = min(result, Search(remaining_nodes - selection) + 1);

      for (int x = 0; x < n_; x++) {
        if (selection & (1 << x)) {
          for (const int y : g_[x]) {
            incoming_edges_[y]++;
          }
        }
      }
    }

    assert(result < INT_MAX);
    return result;
  }

  vector<int> ValidSelections(int remaining_nodes, int num_nodes_to_select) {
    vector<int> valid_selections;
    SearchValidSelections(0, remaining_nodes, num_nodes_to_select, 0,
                          &valid_selections);
    return valid_selections;
  }

  void SearchValidSelections(const int x, const int remaining_nodes,
                             const int num_nodes_to_select, const int selection,
                             vector<int>* valid_selections) {
    if (num_nodes_to_select == 0) {
      valid_selections->push_back(selection);
      return;
    }

    if (x >= n_) {
      return;
    }

    SearchValidSelections(x + 1, remaining_nodes, num_nodes_to_select,
                          selection, valid_selections);
    if ((remaining_nodes & (1 << x)) && incoming_edges_[x] == 0) {
      SearchValidSelections(x + 1, remaining_nodes, num_nodes_to_select - 1,
                            selection | (1 << x), valid_selections);
    }
  }

  const Graph g_;
  const int n_;
  const int k_;
  vector<int> incoming_edges_;
  vector<int> num_semesters_;
};

class Solution {
 public:
  int minNumberOfSemesters(const int n, const vector<vector<int>>& edges,
                           const int k) {
    Graph g(n);
    for (const auto& edge : edges) {
      int x = edge[0] - 1;
      int y = edge[1] - 1;
      g[x].push_back(y);
    }

    DFSWithMemoization dfs(g, k);
    return dfs.MinNumberSemesters();
  }
};

TEST(SolutionTest, testSample) {
  Solution s;
  EXPECT_EQ(3, s.minNumberOfSemesters(4, {{2, 1}, {3, 1}, {1, 4}}, 2));
}
