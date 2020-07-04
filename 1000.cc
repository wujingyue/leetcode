#include <climits>
#include <iostream>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int mergeStones(const vector<int>& a, const int k) {
    const int n = a.size();

    vector<vector<int>> sum(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      sum[i][i] = a[i];
      for (int j = i + 1; j < n; j++) {
        sum[i][j] = sum[i][j - 1] + a[j];
      }
    }

    vector<vector<int>> m(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++) {
      m[i][i] = 0;
    }

    for (int i = n - 1; i >= 0; i--) {
      for (int j = i + 1; j < n; j++) {
        vector<vector<int>> m2 = ComputeM2(m, k, i, j);
        m[i][j] = (m2[j][k] == INT_MAX ? INT_MAX : m2[j][k] + sum[i][j]);
      }
    }

    return m[0][n - 1] == INT_MAX ? -1 : m[0][n - 1];
  }

 private:
  vector<vector<int>> ComputeM2(const vector<vector<int>>& m,
                                const int k, const int left,
                                const int right) {
    vector<vector<int>> m2(right + 1, vector<int>(k + 1));
    for (int i = left; i < right; i++) {
      m2[i][1] = m[left][i];
    }
    m2[right][1] = INT_MAX;
    for (int j = 2; j <= k; j++) {
      for (int i = left; i <= right; i++) {
        int m2ij = INT_MAX;
        // count(left..i2) >= j - 1
        // i2 - left + 1 >= j - 1
        // i2 >= left + j - 2
        for (int i2 = left + j - 2; i2 < i; i2++) {
          if (m2[i2][j - 1] < INT_MAX && m[i2 + 1][i] < INT_MAX) {
            UpdateIfSmaller(m2ij, m2[i2][j - 1] + m[i2 + 1][i]);
          }
        }
        m2[i][j] = m2ij;
      }
    }

    return m2;
  }

  static void UpdateIfSmaller(int& a, int b) {
    if (b < a) {
      a = b;
    }
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(20, s.mergeStones({3, 2, 4, 1}, 2));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(-1, s.mergeStones({3, 2, 4, 1}, 3));
}

TEST(SolutionTest, testSample3) {
  Solution s;
  EXPECT_EQ(25, s.mergeStones({3, 5, 1, 2, 6}, 3));
}
