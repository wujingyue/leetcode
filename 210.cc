#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
    vector<vector<int>> a(n);
    for (const auto& dependency : prerequisites) {
      // x depends on y.
      int x = dependency[0];
      int y = dependency[1];
      a[y].push_back(x);
    }

    vector<int> topological_order;
    constexpr int kUseReversePostorder = false;
    if (kUseReversePostorder) {
      if (!ReversePostorder(a, topological_order)) {
        return {};
      }
    } else {
      if (!TopologicalSort(a, topological_order)) {
        return {};
      }
    }
    return topological_order;
  }

 private:
  bool ReversePostorder(const vector<vector<int>>& a,
                        vector<int>& reverse_postorder) {
    int n = a.size();
    vector<bool> visited(n);
    vector<bool> in_stack(n);
    for (int x = 0; x < n; x++) {
      if (!Postorder(x, a, reverse_postorder, visited, in_stack)) {
        return false;
      }
    }
    reverse(reverse_postorder.begin(), reverse_postorder.end());
    return true;
  }

  bool Postorder(const int x, const vector<vector<int>>& a,
                 vector<int>& postorder, vector<bool>& visited,
                 vector<bool>& in_stack) {
    if (visited[x]) {
      return true;
    }
    visited[x] = true;
    in_stack[x] = true;
    for (int y : a[x]) {
      if (in_stack[y]) {
        return false;
      }
      if (!Postorder(y, a, postorder, visited, in_stack)) {
        return false;
      }
    }
    in_stack[x] = false;
    postorder.push_back(x);
    return true;
  }

  bool TopologicalSort(const vector<vector<int>>& a,
                       vector<int>& topological_order) {
    int n = a.size();
    vector<int> incoming_edges(n);
    for (int x = 0; x < n; x++) {
      for (int y : a[x]) {
        incoming_edges[y]++;
      }
    }

    queue<int> q;  // Nodes with no incoming edges.
    for (int x = 0; x < n; x++) {
      if (incoming_edges[x] == 0) {
        q.push(x);
      }
    }

    int num_expanded = 0;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      num_expanded++;
      topological_order.push_back(x);
      for (int y : a[x]) {
        incoming_edges[y]--;
        if (incoming_edges[y] == 0) {
          q.push(y);
        }
      }
    }
    return num_expanded == n;
  }
};

int main() {
  Solution s;
  vector<vector<int>> prerequisites;
  prerequisites.push_back({1, 0});
  for (int order : s.findOrder(2, prerequisites)) {
    cout << order << ' ';
  }
  cout << endl;

  prerequisites.clear();
  prerequisites.push_back({1, 0});
  prerequisites.push_back({2, 0});
  prerequisites.push_back({3, 1});
  for (int order : s.findOrder(4, prerequisites)) {
    cout << order << ' ';
  }
  cout << endl;

  prerequisites.clear();
  prerequisites.push_back({1, 0});
  prerequisites.push_back({0, 1});
  for (int order : s.findOrder(2, prerequisites)) {
    cout << order << ' ';
  }
  cout << endl;
}