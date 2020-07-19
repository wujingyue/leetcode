#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

#include <vector>

template <class Node>
class PriorityQueue {
 public:
  PriorityQueue(std::vector<Node>&& nodes) {
    pos_.resize(nodes.size(), -1);
    nodes_.swap(nodes);
  }
  PriorityQueue(const PriorityQueue&) = delete;
  PriorityQueue& operator=(const PriorityQueue&) = delete;
  PriorityQueue(PriorityQueue&&) = default;

  Node* GetNode(const int x) { return &nodes_[x]; }
  int GetPosition(const int x) const { return pos_[x]; }

  void Insert(const int x) {
    const int i = order_.size();
    order_.push_back(x);
    pos_[x] = i;
    PercolateUp(i);
  }

  int Pop() {
    const int x = order_[0];
    pos_[x] = -1;

    const int y = order_.back();
    order_.pop_back();

    if (!order_.empty()) {
      order_[0] = y;
      pos_[y] = 0;
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
      pos_[x] = j;
      j = i;
    }
    order_[j] = y;
    pos_[y] = j;
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
      pos_[y] = i;
      i = j;
    }
    order_[i] = x;
    pos_[x] = i;
  }

  std::vector<int> order_;
  std::vector<Node> nodes_;
  std::vector<int> pos_;
};

#endif  // _PRIORITY_QUEUE_H
