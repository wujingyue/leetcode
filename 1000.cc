#include <climits>
#include <iostream>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int mergeStones(const vector<int>& a, const int k) {
    const int n = a.size();

    if ((n - 1) % (k - 1) != 0) {
      return -1;
    }

    // m[i][j] represents the minimum cost to merge the stones between i and j
    // to the fewest piles, i.e., (j-i)%(k-1)+1 piles.
    vector<vector<int>> m(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++) {
      m[i][i] = 0;
    }

    for (int i = n - 1; i >= 0; i--) {
      int sum = a[i];
      for (int j = i + 1; j < n; j++) {
        sum += a[j];
        int mij = INT_MAX;
        for (int t = i; t < j; t += k - 1) {
          const int left_merged_to_one_pile = m[i][t];
          if (left_merged_to_one_pile == INT_MAX) {
            continue;
          }
          const int right = m[t + 1][j];
          if (right == INT_MAX) {
            continue;
          }
          UpdateIfSmaller(mij, left_merged_to_one_pile + right);
        }

        if ((j - i) % (k - 1) == 0) {
          mij += sum;
        }
        m[i][j] = mij;
      }
    }

    return m[0][n - 1];
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
