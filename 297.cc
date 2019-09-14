#include <iostream>
#include <queue>
#include <sstream>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Codec {
 public:
  std::string serialize(TreeNode* root) {
    std::ostringstream os;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
      TreeNode* front = q.front();
      q.pop();
      if (front == nullptr) {
        os << " null";
      } else {
        os << ' ' << front->val;
        q.push(front->left);
        q.push(front->right);
      }
    }
    return os.str();
  }

  TreeNode* deserialize(std::string data) {
    TreeNode* root = nullptr;

    std::queue<TreeNode**> q;
    q.push(&root);

    std::istringstream is(data);
    std::string token;
    while (is >> token) {
      TreeNode** front = q.front();
      q.pop();
      if (token == "null") {
        *front = nullptr;
      } else {
        *front = new TreeNode(std::stoi(token));
        q.push(&((*front)->left));
        q.push(&((*front)->right));
      }
    }
    return root;
  }
};

int main() {
  Codec codec;
  std::string data = " 1 2 3 null null 4 5 null null null null";
  std::cout << data << std::endl;
  std::cout << codec.serialize(codec.deserialize(data)) << std::endl;
}
