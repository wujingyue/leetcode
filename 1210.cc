#include <cassert>
#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int minimumMoves(const vector<vector<int>>& a) {
    int n = a.size();
    assert(n >= 2);
    assert(n == (int)a[0].size());

    assert(a[0][0] == 0);
    assert(a[0][1] == 0);

    vector<vector<vector<int>>> m(
        n, vector<vector<int>>(n, vector<int>(2, INT_MAX)));
    m[0][0][0] = 0;
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < n; y++) {
        int d;
        if (x + 1 < n && y + 1 < n && a[x][y] == 0 && a[x][y + 1] == 0 &&
            a[x + 1][y] == 0 && a[x + 1][y + 1] == 0) {
          d = m[x][y][0];
          if (d < INT_MAX) {
            UpdateIfSmaller(m[x][y][1], d + 1);
          }
          d = m[x][y][1];
          if (d < INT_MAX) {
            UpdateIfSmaller(m[x][y][0], d + 1);
          }
        }
        {
          d = m[x][y][0];
          if (d < INT_MAX) {
            if (y + 2 < n && a[x][y + 2] == 0) {
              UpdateIfSmaller(m[x][y + 1][0], d + 1);
            }
            if (x + 1 < n && a[x + 1][y] == 0 && a[x + 1][y + 1] == 0) {
              UpdateIfSmaller(m[x + 1][y][0], d + 1);
            }
          }
        }
        {
          d = m[x][y][1];
          if (d < INT_MAX) {
            if (x + 2 < n && a[x + 2][y] == 0) {
              UpdateIfSmaller(m[x + 1][y][1], d + 1);
            }
            if (y + 1 < n && a[x][y + 1] == 0 && a[x + 1][y + 1] == 0) {
              UpdateIfSmaller(m[x][y + 1][1], d + 1);
            }
          }
        }
      }
    }

    int answer = m[n - 1][n - 2][0];
    if (answer == INT_MAX) {
      answer = -1;
    }
    return answer;
  }

 private:
  static void UpdateIfSmaller(int& a, int b) {
    if (b < a) {
      a = b;
    }
  }
};

class SolutionTest : public ::testing::Test {
 protected:
  Solution s_;
};

TEST_F(SolutionTest, testSample1) {
  vector<vector<int>> a({{0, 0, 0, 0, 0, 1},
                         {1, 1, 0, 0, 1, 0},
                         {0, 0, 0, 0, 1, 1},
                         {0, 0, 1, 0, 1, 0},
                         {0, 1, 1, 0, 0, 0},
                         {0, 1, 1, 0, 0, 0}});
  EXPECT_EQ(11, s_.minimumMoves(a));
}

TEST_F(SolutionTest, testSample2) {
  vector<vector<int>> a({{0, 0, 1, 1, 1, 1},
                         {0, 0, 0, 0, 1, 1},
                         {1, 1, 0, 0, 0, 1},
                         {1, 1, 1, 0, 0, 1},
                         {1, 1, 1, 0, 0, 1},
                         {1, 1, 1, 0, 0, 0}});
  EXPECT_EQ(9, s_.minimumMoves(a));
}
