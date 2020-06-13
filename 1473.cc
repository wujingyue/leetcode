#include <climits>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int minCost(const vector<int>& houses, const vector<vector<int>>& cost,
              const int num_houses, const int num_colors,
              const int num_neighborhoods) {
    const int n = houses.size();
    vector<vector<vector<int>>> m(
        num_houses, vector<vector<int>>(num_neighborhoods + 1,
                                        vector<int>(num_colors + 1, INT_MAX)));
    if (houses[0] > 0) {
      m[0][1][houses[0]] = 0;
    } else {
      for (int k = 1; k <= num_colors; k++) {
        m[0][1][k] = cost[0][k - 1];
      }
    }

    for (int i = 0; i + 1 < n; i++) {
      for (int j = 1; j <= num_neighborhoods; j++) {
        for (int k = 1; k <= num_colors; k++) {
          if (m[i][j][k] == INT_MAX) {
            continue;
          }

          if (houses[i + 1] > 0) {
            const int j2 = j + (houses[i + 1] != k);
            if (j2 <= num_neighborhoods) {
              UpdateIfSmaller(m[i + 1][j2][houses[i + 1]], m[i][j][k]);
            }
          } else {
            for (int k2 = 1; k2 <= num_colors; k2++) {
              const int j2 = j + (k2 != k);
              if (j2 <= num_neighborhoods) {
                UpdateIfSmaller(m[i + 1][j2][k2],
                                m[i][j][k] + cost[i + 1][k2 - 1]);
              }
            }
          }
        }
      }
    }

    int answer = INT_MAX;
    for (int k = 1; k <= num_colors; k++) {
      UpdateIfSmaller(answer, m[n - 1][num_neighborhoods][k]);
    }
    return (answer == INT_MAX ? -1 : answer);
  }

 private:
  void UpdateIfSmaller(int& a, const int b) {
    if (b < a) {
      a = b;
    }
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(9,
            s.minCost({0, 0, 0, 0, 0},
                      {{1, 10}, {10, 1}, {10, 1}, {1, 10}, {5, 1}}, 5, 2, 3));
}
