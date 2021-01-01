#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

void UpdateIfLarger(int& a, const int b) {
  if (b > a) {
    a = b;
  }
}

class Solution {
 public:
  int cherryPickup(const vector<vector<int>>& a) {
    const int r = a.size();
    const int c = a[0].size();

    int m[c][c];
    for (int i = 0; i < c; i++) {
      for (int j = 0; j < c; j++) {
        m[i][j] = INT_MIN;
      }
    }
    if (a[0][0] >= 0) {
      m[0][0] = a[0][0];
    }

    for (int x = 0; x < r; x++) {
      // Instead of considering one player going back and forth, let's consider
      // two players both walking from the upperleft corner to the lowerright.
      // This is equivalent to the original question.
      //
      // m[i][j] represents the maximum number of cherries taken when player 1
      // enters row x at column i and player 2 enters row x at
      // column j. At this point, player 1 must be to the left of player 2 or at
      // the same column. At this point, neither of the players have walked
      // within row x.
      //
      // Walk the first player.
      for (int i = 0; i < c; i++) {
        for (int j = 0; j < c; j++) {
          if (m[i][j] == INT_MIN) {
            continue;
          }
          if (i + 1 < c && a[x][i + 1] >= 0) {
            UpdateIfLarger(m[i + 1][j],
                           m[i][j] + (i + 1 != j ? a[x][i + 1] : 0));
          }
        }
      }

      // Walk the second player.
      for (int i = 0; i < c; i++) {
        for (int j = 0; j < c; j++) {
          if (m[i][j] == INT_MIN) {
            continue;
          }
          if (j + 1 < c && a[x][j + 1] >= 0) {
            // If the first player is to the right of the second player, don't
            // overcount cherries.
            UpdateIfLarger(m[i][j + 1], m[i][j] + (i <= j ? a[x][j + 1] : 0));
          }
        }
      }

      if (x + 1 < r) {
        // Propogate m to the next row.
        for (int i = 0; i < c; i++) {
          for (int j = 0; j < c; j++) {
            if (m[i][j] == INT_MIN) {
              continue;
            }

            if (i > j || a[x + 1][i] < 0 || a[x + 1][j] < 0) {
              m[i][j] = INT_MIN;
              continue;
            }

            m[i][j] += a[x + 1][i] + (i != j ? a[x + 1][j] : 0);
          }
        }
      }
    }

    int ans = m[c - 1][c - 1];
    if (ans == INT_MIN) {
      ans = 0;
    }
    return ans;
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(5, s.cherryPickup({{0, 1, -1}, {1, 0, -1}, {1, 1, 1}}));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(0, s.cherryPickup({{1, 1, -1}, {1, -1, 1}, {-1, 1, 1}}));
}

TEST(SolutionTest, testSample3) {
  Solution s;
  EXPECT_EQ(13, s.cherryPickup({{1, 1, 1, 1, 1},
                                {1, 1, -1, 1, 1},
                                {-1, -1, 1, 1, 1},
                                {1, 1, 1, 1, 1},
                                {-1, 1, 1, 1, 1}}));
}
