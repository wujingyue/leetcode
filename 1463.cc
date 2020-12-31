#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int cherryPickup(const vector<vector<int>>& a) {
    const int r = a.size();
    const int c = a[0].size();
    vector<vector<vector<int>>> m(
        r, vector<vector<int>>(c, vector<int>(c, INT_MIN)));
    m[0][0][c - 1] = a[0][0] + a[0][c - 1];
    for (int x = 0; x < r - 1; x++) {
      for (int y1 = 0; y1 < c; y1++) {
        for (int y2 = y1; y2 < c; y2++) {
          if (m[x][y1][y2] == INT_MIN) {
            continue;
          }
          for (int dy1 = -1; dy1 <= 1; dy1++) {
            const int y1_prime = y1 + dy1;
            if (y1_prime < 0 || y1_prime >= c) {
              continue;
            }
            for (int dy2 = -1; dy2 <= 1; dy2++) {
              const int y2_prime = y2 + dy2;
              if (y2_prime < y1_prime || y2_prime >= c) {
                continue;
              }
              const int m_prime =
                  m[x][y1][y2] + a[x + 1][y1_prime] +
                  (y1_prime == y2_prime ? 0 : a[x + 1][y2_prime]);
              m[x + 1][y1_prime][y2_prime] =
                  max(m[x + 1][y1_prime][y2_prime], m_prime);
            }
          }
        }
      }
    }

    int max_sum = 0;
    for (int y1 = 0; y1 < c; y1++) {
      for (int y2 = y1; y2 < c; y2++) {
        max_sum = max(max_sum, m[r - 1][y1][y2]);
      }
    }
    return max_sum;
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(24, s.cherryPickup({{3, 1, 1}, {2, 5, 1}, {1, 5, 5}, {2, 1, 1}}));
}
