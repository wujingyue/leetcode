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
  int rob(const TreeNode* root) {
    pair<int, int> res = MaxRob(root);
    return max(res.first, res.second);
  }

 private:
  // Returns a pair of integers. The first integer means the max money robbed if
  // p is robbed. The second integer means the max money robbed if p is not
  // robbed.
  pair<int, int> MaxRob(const TreeNode* p) {
    if (p == nullptr) {
      return {0, 0};
    }

    pair<int, int> left_res = MaxRob(p->left);
    pair<int, int> right_res = MaxRob(p->right);
    const int robbed = p->val + left_res.second + right_res.second;
    const int not_robbed = max(left_res.first, left_res.second) +
                           max(right_res.first, right_res.second);
    return {robbed, not_robbed};
  }
};