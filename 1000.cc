#include <climits>
#include <iostream>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int mergeStones(const vector<int>& a, const int num_splits) {
    const int n = a.size();

    vector<vector<int>> sum(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      sum[i][i] = a[i];
      for (int j = i + 1; j < n; j++) {
        sum[i][j] = sum[i][j - 1] + a[j];
      }
    }

    // m[i][j][k] represents the minimum cost to merge the stones between i and
    // j into k piles.
    vector<vector<vector<int>>> m(
        n, vector<vector<int>>(n, vector<int>(num_splits + 1, INT_MAX)));
    for (int i = 0; i < n; i++) {
      m[i][i][1] = 0;
    }

    for (int i = n - 1; i >= 0; i--) {
      for (int j = i + 1; j < n; j++) {
        for (int k = 2; k <= num_splits; k++) {
          int mijk = INT_MAX;
          for (int t = i; t < j; t++) {
            const int left_merged_to_one_pile = m[i][t][1];
            if (left_merged_to_one_pile == INT_MAX) {
              continue;
            }
            const int right = m[t + 1][j][k - 1];
            if (right == INT_MAX) {
              continue;
            }
            UpdateIfSmaller(mijk, left_merged_to_one_pile + right);
          }
          m[i][j][k] = mijk;
        }
        if (m[i][j][num_splits] < INT_MAX) {
          m[i][j][1] = m[i][j][num_splits] + sum[i][j];
        }
      }
    }

    return m[0][n - 1][1] == INT_MAX ? -1 : m[0][n - 1][1];
  }

 private:
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
