#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int minDistance(vector<int>& a, const int k) {
    sort(a.begin(), a.end());
    const int n = a.size();

    vector<vector<int>> d(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        int mid = i + (j - i) / 2;
        for (int k = i; k <= j; k++) {
          d[i][j] += abs(a[k] - a[mid]);
        }
      }
    }

    vector<vector<int>> m(n + 1, vector<int>(k + 1, INT_MAX));
    m[0][0] = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= k; j++) {
        // m[i][j] = min(m[i'][j - 1] + TotalDistanceWithOneMailBox(i', i - 1))
        // for all 0 <= i' < i
        for (int i2 = 0; i2 < i; i2++) {
          int m2 = m[i2][j - 1];
          if (m2 < INT_MAX) {
            m[i][j] = min(m[i][j], m2 + d[i2][i - 1]);
          }
        }
      }
    }
    return m[n][k];
  }
};

TEST(SolutionTest, testSample1) {
  vector<int> a({1, 4, 8, 10, 20});
  Solution s;
  EXPECT_EQ(5, s.minDistance(a, 3));
}

TEST(SolutionTest, testSample2) {
  vector<int> a({2, 3, 5, 12, 18});
  Solution s;
  EXPECT_EQ(9, s.minDistance(a, 2));
}

TEST(SolutionTest, testSample3) {
  vector<int> a({7, 4, 6, 1});
  Solution s;
  EXPECT_EQ(8, s.minDistance(a, 1));
}

TEST(SolutionTest, testSample4) {
  vector<int> a({3, 6, 14, 10});
  Solution s;
  EXPECT_EQ(0, s.minDistance(a, 4));
}
