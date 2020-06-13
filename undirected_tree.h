#ifndef _UNDIRECTED_TREE_H
#define _UNDIRECTED_TREE_H

#include <vector>

class UndirectedTree {
 public:
  UndirectedTree(const std::vector<int>& prufer, int n);
  UndirectedTree(int n) : adj_(n) {}

  int size() const { return adj_.size(); }

  const std::vector<int>& Neighbors(const int x) const { return adj_.at(x); }

  void AddEdge(int x, int y) {
    adj_[x].push_back(y);
    adj_[y].push_back(x);
  }

  std::vector<int> ToPrufer() const;

  bool operator==(const UndirectedTree& other) const;

 private:
  std::vector<std::vector<int>> adj_;
};

#endif  // _UNDIRECTED_TREE_H
