#include <vector>

#include "gtest/gtest.h"

using namespace std;

class BinarySearchTree {
 public:
  BinarySearchTree(std::vector<int> keys) {
    std::sort(keys.begin(), keys.end());
    keys.erase(std::unique(keys.begin(), keys.end()), keys.end());

    n_ = keys.size();
    nodes_.resize(n_);

    int key_index = 0;
    Build(keys, 0, &key_index);
  }

  void Insert(const int key, const int value) {
    int i = 0;
    while (i < n_) {
      nodes_[i].max_value = max(nodes_[i].max_value, value);
      if (key == nodes_[i].key) {
        nodes_[i].value = max(nodes_[i].value, value);
        break;
      }
      if (key < nodes_[i].key) {
        i = i * 2 + 1;
      } else {
        i = i * 2 + 2;
      }
    }
  }

  int MaxValueWithKeyLessThan(const int key) const {
    int max_value = 0;
    int i = 0;
    while (i < n_) {
      const int left = i * 2 + 1;
      const int right = i * 2 + 2;
      if (key < nodes_[i].key) {
        i = left;
      } else {
        if (left < n_) {
          max_value = max(max_value, nodes_[left].max_value);
        }
        if (key == nodes_[i].key) {
          break;
        }
        max_value = max(max_value, nodes_[i].value);
        i = right;
      }
    }
    return max_value;
  }

 private:
  struct TreeNode {
    int key;
    int value;
    int max_value;
  };

  void Build(const std::vector<int>& keys, const int i, int* key_index) {
    if (i >= n_) {
      return;
    }

    Build(keys, i * 2 + 1, key_index);

    TreeNode* node = &nodes_[i];
    node->key = keys[*key_index];
    node->value = 0;
    node->max_value = 0;
    (*key_index)++;

    Build(keys, i * 2 + 2, key_index);
  }

  std::vector<TreeNode> nodes_;
  int n_;
};

class Solution {
 public:
  int lengthOfLIS(const vector<int>& a) {
    BinarySearchTree bst(a);

    int longest = 0;
    for (int key : a) {
      int longest_smaller = bst.MaxValueWithKeyLessThan(key);
      longest = max(longest, longest_smaller + 1);
      bst.Insert(key, longest_smaller + 1);
    }
    return longest;
  }
};

TEST(SolutionTest, testSample) {
  Solution s;
  EXPECT_EQ(4, s.lengthOfLIS({10, 9, 2, 5, 3, 7, 101, 18}));
}
