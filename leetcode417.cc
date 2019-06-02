#include <iostream>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& matrix) {
    int m = matrix.size();
    if (m == 0) {
      return std::vector<std::vector<int>>();
    }
    int n = matrix[0].size();
    if (n == 0) {
      return std::vector<std::vector<int>>();
    }

    std::vector<std::vector<bool>> reachable_from_pacific(m, std::vector<bool>(n));
    for (int x = 0; x < m; ++x) {
      DFS(x, 0, m, n, matrix, &reachable_from_pacific);
    }
    for (int y = 0; y < n; ++y) {
      DFS(0, y, m, n, matrix, &reachable_from_pacific);
    }

    std::vector<std::vector<bool>> reachable_from_atlantic(m, std::vector<bool>(n));
    for (int x = 0; x < m; ++x) {
      DFS(x, n - 1, m, n, matrix, &reachable_from_atlantic);
    }
    for (int y = 0; y < n; ++y) {
      DFS(m - 1, y, m, n, matrix, &reachable_from_atlantic);
    }

    std::vector<std::vector<int>> answer;
    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < n; ++y) {
        if (reachable_from_pacific[x][y] && reachable_from_atlantic[x][y]) {
          answer.push_back({x, y});
        }
      }
    }
    return answer;
  }

 private:
  void DFS(int x, int y, int m, int n, const std::vector<std::vector<int>>& matrix, std::vector<std::vector<bool>>* reachable) {
    if ((*reachable)[x][y]) {
      return;
    }
    (*reachable)[x][y] = true;
    for (int dir = 0; dir < 4; ++dir) {
      int x2 = x + kDx[dir];
      int y2 = y + kDy[dir];
      if (x2 >= 0 && x2 < m && y2 >= 0 && y2 < n) {
        if (matrix[x2][y2] >= matrix[x][y]) {
          DFS(x2, y2, m, n, matrix, reachable);
        }
      }
    }
  }

  const int kDx[4] = {-1, 0, 1, 0};
  const int kDy[4] = {0, 1, 0, -1};
};

int main() {
  std::vector<std::vector<int>> matrix;
  matrix.push_back({1, 2, 2, 3, 5});
  matrix.push_back({3, 2, 3, 4, 4});
  matrix.push_back({2, 4, 5, 3, 1});
  matrix.push_back({6, 7, 1, 4, 5});
  matrix.push_back({5, 1, 1, 2, 4});

  Solution solution;
  auto answer = solution.pacificAtlantic(matrix);
  for (const auto& pair : answer) {
    std::cout << pair[0] << ' ' << pair[1] << std::endl;
  }
}
