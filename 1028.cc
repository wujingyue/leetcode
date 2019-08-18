#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
 public:
  TreeNode* recoverFromPreorder(string s) {
    vector<TreeNode*> path;
    int i = 0;
    while (i < (int)s.length()) {
      int depth = 0;
      while (s[i] == '-') {
        depth++;
        i++;
      }
      int value = 0;
      while (i < (int)s.length() && isdigit(s[i])) {
        value = value * 10 + s[i] - '0';
        i++;
      }
      while (depth < (int)path.size()) {
        path.pop_back();
      }
      TreeNode* parent = (path.empty() ? nullptr : path.back());
      TreeNode* cur = new TreeNode(value);
      if (parent != nullptr) {
        if (parent->left == nullptr) {
          parent->left = cur;
        } else {
          assert(parent->right == nullptr);
          parent->right = cur;
        }
      }
      path.push_back(cur);
    }

    assert(!path.empty());
    return path[0];
  }
};

void PrintTree(TreeNode* root) {
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    TreeNode* cur = q.front();
    q.pop();
    if (cur) {
      cout << cur->val << ", ";
      q.push(cur->left);
      q.push(cur->right);
    } else {
      cout << "null, ";
    }
  }
  cout << endl;
}

int main() {
  Solution sol;
  PrintTree(sol.recoverFromPreorder("1-2--3--4-5--6--7"));
  PrintTree(sol.recoverFromPreorder("1-2--3---4-5--6---7"));
}
