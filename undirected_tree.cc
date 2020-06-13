#include "undirected_tree.h"

#include <algorithm>
#include <cassert>
#include <queue>

using namespace std;

UndirectedTree::UndirectedTree(const vector<int>& prufer, const int n)
    : adj_(n) {
  vector<int> degree(n, 1);
  for (const int x : prufer) {
    degree[x]++;
  }

  priority_queue<int, vector<int>, greater<int>> leaves;
  for (int x = 0; x < n; x++) {
    if (degree[x] == 1) {
      leaves.push(x);
    }
  }

  UndirectedTree tree(n);
  for (const int x : prufer) {
    const int y = leaves.top();
    leaves.pop();
    AddEdge(x, y);
    degree[x]--;
    if (degree[x] == 1) {
      leaves.push(x);
    }
  }

  assert(leaves.size() <= 2);
  if (leaves.size() == 2) {
    const int x = leaves.top();
    leaves.pop();
    const int y = leaves.top();
    AddEdge(x, y);
  }
}

vector<int> UndirectedTree::ToPrufer() const {
  const int n = size();
  vector<int> degree(n);
  priority_queue<int, vector<int>, greater<int>> leaves;
  for (int x = 0; x < n; x++) {
    degree[x] = adj_[x].size();
    if (degree[x] == 1) {
      leaves.push(x);
    }
  }

  vector<int> prufer;
  while ((int)prufer.size() + 2 < n) {
    const int x = leaves.top();
    leaves.pop();
    degree[x] = 0;
    for (const int y : adj_[x]) {
      if (degree[y] > 0) {
        prufer.push_back(y);
        degree[y]--;
        if (degree[y] == 1) {
          leaves.push(y);
        }
      }
    }
  }

  return prufer;
}

bool UndirectedTree::operator==(const UndirectedTree& other) const {
  const int n = size();
  if (n != other.size()) {
    return false;
  }

  for (int x = 0; x < n; x++) {
    vector<int> n1 = Neighbors(x);
    vector<int> n2 = other.Neighbors(x);
    sort(n1.begin(), n1.end());
    sort(n2.begin(), n2.end());
    if (n1 != n2) {
      return false;
    }
  }

  return true;
}
