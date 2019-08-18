#include <algorithm>
#include <iostream>
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

    vector<int> reverse_postorder;
    if (!ReversePostorder(a, reverse_postorder)) {
      return {};
    }
    return reverse_postorder;
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