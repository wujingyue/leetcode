#include <iostream>
#include <vector>

class NodeIterator {
 public:
  NodeIterator(std::vector<TreeNode*> path): path_(std::move(path)) {}

  TreeNode* Get() const {
    assert(!path_.empty());
    return path_.back();
  }

  bool Increment() {
    TreeNode* cur = Get();
    if (cur->right) {
      cur = cur->right;
      path_.push_back(cur);
      while (cur->left) {
        cur = cur->left;
        path_.push_back(cur);
      }
      return true;
    }

    while (true) {
      path_.pop_back();
      if (path_.empty()) {
        return false;
      }
      TreeNode* parent = path_.back();
      if (parent->left == cur) {
        return true;
      }
      cur = parent;
    }
  }

 private:
  std::vector<TreeNode*> path_;
};

class Solution {
 public:
  std::vector<int> inorderTraversal(TreeNode* root) {
    if (root == nullptr) {
      return std::vector<int>();
    }

    std::vector<TreeNode*> path;
    while (root) {
      path.push_back(root);
      root = root->left;
    }

    std::vector<int> answer;
    NodeIterator iter(std::move(path));
    do {
      answer.push_back(iter.Get()->val);
    } while (iter.Increment());
    return answer;
  }
};
