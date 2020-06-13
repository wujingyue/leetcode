#include <climits>

using namespace std;

class Solution {
 public:
  int goodNodes(const TreeNode* root) {
    return DFS(root, INT_MIN);
  }

 private:
  int DFS(const TreeNode* root, int max_before) {
    if (root == nullptr) {
      return 0;
    }

    int answer = 0;
    if (root->val >= max_before) {
      answer++;
      max_before = root->val;
    }

    answer += DFS(root->left, max_before);
    answer += DFS(root->right, max_before);
    return answer;
  }
};
