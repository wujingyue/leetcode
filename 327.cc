#include <algorithm>
#include <cassert>
#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

template <class T>
struct Node {
  T value;
  int size;  // The size of the subtree rooted at the node.
};

template <class T>
class OrderedMultiset {
 public:
  // Construct a complete binary search tree with a list of pre-defined values.
  OrderedMultiset(const vector<T>& sorted_values);

  // The caller must make sure `value` was in the constructor's `sorted_values`.
  void Insert(const T& value);

  // Unlike `Insert`, `value` doesn't have to be in `sorted_values`.
  int CountLessThan(const T& value) const;

 private:
  void BuildCompleteBinarySearchTree(const vector<T>& sorted_values,
                                     int index, int left, int right);

  vector<Node<T>> nodes_;
};

template <class T>
OrderedMultiset<T>::OrderedMultiset(const vector<T>& sorted_values) {
  const int n = sorted_values.size();
  nodes_.resize(n);
  BuildCompleteBinarySearchTree(sorted_values, 0, 0, n - 1);
}

template <class T>
void OrderedMultiset<T>::BuildCompleteBinarySearchTree(
    const vector<T>& sorted_values, const int index, const int low,
    const int high) {
  const int size = high - low + 1;
  if (size == 0) {
    return;
  }

  if (size == 1) {
    nodes_[index].value = sorted_values[low];
    return;
  }

  // height = floor(log_2(size)) + 1
  const int height = sizeof(int) * CHAR_BIT - __builtin_clz(size);
  // assert(height >= 2 && "height >= 2 because size >= 2");
  int left_size = (1 << (height - 2)) - 1;
  int right_size = left_size;
  const int remaining = size - 1 - left_size - right_size;
  if (remaining <= (1 << (height - 2))) {
    left_size += remaining;
  } else {
    left_size += (1 << (height - 2));
    right_size += remaining - (1 << (height - 2));
  }

  nodes_[index].value = sorted_values[low + left_size];
  BuildCompleteBinarySearchTree(sorted_values, index * 2 + 1, low,
                                low + left_size - 1);
  BuildCompleteBinarySearchTree(sorted_values, index * 2 + 2,
                                low + left_size + 1, high);
}

template <class T>
void OrderedMultiset<T>::Insert(const T& value) {
  int i = 0;
  while (true) {
    // assert(i < (int)nodes_.size() &&
    //        "Otherwise `value` was not passed into the constructor.");
    nodes_[i].size++;
    const T curr = nodes_[i].value;
    if (value == curr) {
      break;
    }
    if (value < curr) {
      i = i * 2 + 1;
    } else {
      i = i * 2 + 2;
    }
  }
}

template <class T>
int OrderedMultiset<T>::CountLessThan(const T& value) const {
  const int n = nodes_.size();
  int count = 0;
  int i = 0;
  while (i < n) {
    const T& curr = nodes_[i].value;
    if (value <= curr) {
      i = i * 2 + 1;
    } else {
      const int right = i * 2 + 2;
      count += nodes_[i].size - (right < n ? nodes_[right].size : 0);
      i = right;
    }
  }
  return count;
}

class Solution {
 public:
  int countRangeSum(const vector<int>& nums, const int lower, const int upper) {
    const int n = nums.size();

    vector<int64_t> prefix_sums;
    prefix_sums.reserve(n);

    int64_t prefix_sum = 0;
    for (const int num : nums) {
      prefix_sums.push_back(prefix_sum);
      prefix_sum += num;
    }
    sort(prefix_sums.begin(), prefix_sums.end());
    prefix_sums.erase(unique(prefix_sums.begin(), prefix_sums.end()),
                      prefix_sums.end());

    OrderedMultiset<int64_t> ordered_multiset(prefix_sums);

    int count = 0;
    prefix_sum = 0;
    for (const int num : nums) {
      // Insert last prefix sum.
      ordered_multiset.Insert(prefix_sum);
      prefix_sum += num;
      // Find the number of previous prefix sums that satisfy
      //   lower <= prefix_sum - previous_prefix_sum <= upper
      // i.e.
      //   prefix_sum - upper <= previous_prefix_sum < prefix_sum - lower + 1
      count += ordered_multiset.CountLessThan(prefix_sum - lower + 1) -
               ordered_multiset.CountLessThan(prefix_sum - upper);
    }
    return count;
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(s.countRangeSum({-2, 5, -1}, -2, 2), 3);
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(s.countRangeSum({0}, 0, 0), 1);
}