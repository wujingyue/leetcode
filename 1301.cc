#include <algorithm>
#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  vector<int> pathsWithMaxScore(const vector<string>& a) {
    const int m = a.size();
    const int n = a[0].size();

    vector<vector<int>> s(m, vector<int>(n, INT_MIN));
    vector<vector<int>> paths(m, vector<int>(n, 0));
    s[m - 1][n - 1] = 0;
    paths[m - 1][n - 1] = 1;
    for (int x = m - 1; x >= 0; x--) {
      for (int y = n - 1; y >= 0; y--) {
        if (s[x][y] == INT_MIN) {
          continue;
        }
        for (int dir = 0; dir < 3; dir++) {
          const int x2 = x + kDx[dir];
          const int y2 = y + kDy[dir];
          if (x2 < 0 || y2 < 0 || a[x2][y2] == 'X') {
            continue;
          }
          const int new_s = s[x][y] + Score(a[x2][y2]);
          if (new_s > s[x2][y2]) {
            s[x2][y2] = new_s;
            paths[x2][y2] = paths[x][y];
          } else if (new_s == s[x2][y2]) {
            constexpr int kModulo = 1000000007;
            paths[x2][y2] = (paths[x2][y2] + paths[x][y]) % kModulo;
          }
        }
      }
    }

    return {s[0][0] == INT_MIN ? 0 : s[0][0], paths[0][0]};
  }

 private:
  int Score(const char c) {
    if (isdigit(c)) {
      return c - '0';
    }
    return 0;
  }

  const int kDx[3] = {-1, 0, -1};
  const int kDy[3] = {0, -1, -1};
};

TEST(SolutionTest, example1) {
  Solution s;
  EXPECT_EQ(vector<int>({7, 1}), s.pathsWithMaxScore({"E23", "2X2", "12S"}));
}

TEST(SolutionTest, example2) {
  Solution s;
  EXPECT_EQ(vector<int>({4, 2}), s.pathsWithMaxScore({"E12", "1X1", "21S"}));
}

TEST(SolutionTest, example3) {
  Solution s;
  EXPECT_EQ(vector<int>({0, 0}), s.pathsWithMaxScore({"E11", "XXX", "11S"}));
}