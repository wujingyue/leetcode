#include <iostream>
#include <vector>

using namespace std;

struct Rectangle {
  int left;
  int height;
};

class Solution {
 public:
  int MaxRectangleInHistogram(const vector<int>& h) {
    int n = h.size();
    int max_area = 0;
    vector<Rectangle> stack;
    for (int y = 0; y < n; ++y) {
      int left = y;
      while (!stack.empty() && stack.back().height >= h[y]) {
        max_area = max(max_area, (y - stack.back().left) * stack.back().height);
        left = stack.back().left;
        stack.pop_back();
      }
      stack.push_back(Rectangle{left, h[y]});
    }
    while (!stack.empty()) {
      max_area = max(max_area, (n - stack.back().left) * stack.back().height);
      stack.pop_back();
    }
    return max_area;
  }

  int maximalRectangle(vector<vector<char>>& matrix) {
    int m = matrix.size();
    if (m == 0) {
      return 0;
    }
    int n = matrix[0].size();

    int max_area = 0;
    vector<int> h(n);
    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < n; ++y) {
        if (matrix[x][y] == '1') {
          h[y]++;
        } else {
          h[y] = 0;
        }
      }
      max_area = max(max_area, MaxRectangleInHistogram(h));
    }
    return max_area;
  }
};

int main() {
  string line;
  vector<vector<char>> matrix;
  while (getline(cin, line)) {
    matrix.push_back(vector<char>(line.begin(), line.end()));
  }

  Solution solution;
  cout << solution.maximalRectangle(matrix) << endl;
}
