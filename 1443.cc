#include <vector>

#include "gtest/gtest.h"

using namespace std;

struct Node {
  int id = -1;
  int num_apples_under = 0;
  vector<Node*> children;
};

using Graph = vector<vector<int>>;

class Solution {
 public:
  int minTime(const int n, const vector<vector<int>>& edges,
              const vector<bool>& has_apple) {
    Graph g = BuildGraph(n, edges);
    Node* root = BuildTree(g, 0, -1);
    PopulateApples(has_apple, root);
    int answer = DFS(root);
    DeleteRecursively(root);
    return answer;
  }

 private:
  Graph BuildGraph(const int n, const vector<vector<int>>& edges) {
    Graph g(n);
    for (const vector<int>& edge : edges) {
      const int x = edge[0];
      const int y = edge[1];
      g[x].push_back(y);
      g[y].push_back(x);
    }
    return g;
  }

  Node* BuildTree(const Graph& g, const int id, const int parent_id) {
    Node* p = new Node();
    p->id = id;

    for (const int neighbor : g[id]) {
      if (neighbor == parent_id) {
        continue;
      }
      Node* child = BuildTree(g, neighbor, id);
      p->children.push_back(child);
    }

    return p;
  }

  void DeleteRecursively(Node* p) {
    for (Node* child : p->children) {
      DeleteRecursively(child);
    }
    delete p;
  }

  void PopulateApples(const vector<bool>& has_apple, Node* p) {
    if (has_apple[p->id]) {
      p->num_apples_under++;
    }

    for (Node* child : p->children) {
      PopulateApples(has_apple, child);
      p->num_apples_under += child->num_apples_under;
    }
  }

  int DFS(const Node* p) {
    int steps = 0;
    for (const Node* child : p->children) {
      if (child->num_apples_under > 0) {
        steps += DFS(child) + 2;
      }
    }
    return steps;
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  int answer = s.minTime(7, {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}},
                         {false, false, true, false, true, true, false});
  EXPECT_EQ(8, answer);
}

TEST(SolutionTest, testSample2) {
  Solution s;
  int answer = s.minTime(7, {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}},
                         {false, false, true, false, false, true, false});
  EXPECT_EQ(6, answer);
}
