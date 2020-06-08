#include <algorithm>

#include "gtest/gtest.h"

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
};

class Solution {
 public:
  int rob(const TreeNode* root) { return MaxRob(root).second; }

 private:
  // Returns a pair of integers. The first integer means the max money robbed if
  // p's parent is robbed. The second integer means the max money robbed if p's
  // parent is not robbed.
  pair<int, int> MaxRob(const TreeNode* p) {
    if (p == nullptr) {
      return {0, 0};
    }

    pair<int, int> left_res = MaxRob(p->left);
    pair<int, int> right_res = MaxRob(p->right);
    const int parent_is_robbed = left_res.second + right_res.second;
    const int parent_is_not_robbed =
        max(parent_is_robbed, p->val + left_res.first + right_res.first);
    return {parent_is_robbed, parent_is_not_robbed};
  }
};