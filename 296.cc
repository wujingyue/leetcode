#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minTotalDistance(vector<vector<int>>& grid) {
    int m = grid.size();
    if (m == 0) {
      return 0;
    }
    int n = grid[0].size();
    if (n == 0) {
      return 0;
    }

    int num_points = 0;
    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < n; ++y) {
        if (grid[x][y]) {
          num_points++;
        }
      }
    }
    if (num_points == 0) {
      return 0;
    }

    int k = 0;
    int median_x = -1;
    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < n; ++y) {
        if (grid[x][y]) {
          if (k == num_points / 2) {
            median_x = x;
            break;
          }
          k++;
        }
      }
      if (median_x >= 0) {
        break;
      }
    }

    k = 0;
    int median_y = -1;
    for (int y = 0; y < n; ++y) {
      for (int x = 0; x < m; ++x) {
        if (grid[x][y]) {
          if (k == num_points / 2) {
            median_y = y;
            break;
          }
          k++;
        }
      }
      if (median_y >= 0) {
        break;
      }
    }

    int answer = 0;
    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < n; ++y) {
        if (grid[x][y]) {
          answer += abs(x - median_x) + abs(y - median_y);
        }
      }
    }
    return answer;
  }
};

int main() {
  vector<vector<int>> grid;
  grid.push_back({1, 0, 0, 0, 1});
  grid.push_back({0, 0, 0, 0, 0});
  grid.push_back({0, 0, 1, 0, 0});

  Solution s;
  cout << s.minTotalDistance(grid) << endl;
}
