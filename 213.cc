#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int rob(const vector<int>& a) {
    const int n = a.size();
    if (n == 0) {
      return 0;
    }
    if (n == 1) {
      return a[0];
    }

    vector<vector<int>> m(n, vector<int>(2));

    // a[0] is robbed.
    m[0][0] = INT_MIN;
    m[0][1] = a[0];
    DP(a, n, m);
    int answer = m[n - 1][0];

    // a[0] is not robbed.
    m[0][0] = 0;
    m[0][1] = INT_MIN;
    DP(a, n, m);
    answer = max(answer, max(m[n - 1][0], m[n - 1][1]));

    return answer;
  }

 private:
  void DP(const vector<int>& a, const int n, vector<vector<int>>& m) {
    for (int i = 1; i < n; i++) {
      m[i][0] = max(m[i - 1][0], m[i - 1][1]);
      m[i][1] = (m[i - 1][0] == INT_MIN ? INT_MIN : m[i - 1][0] + a[i]);
    }
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(3, s.rob({2, 3, 2}));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(4, s.rob({1, 2, 3, 1}));
}

TEST(SolutionTest, testOneElement) {
  Solution s;
  EXPECT_EQ(1, s.rob({1}));
}