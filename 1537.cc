#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int maxSum(const vector<int>& a, const vector<int>& b) {
    const int m = a.size();
    const int n = b.size();
    int i = 0;
    int j = 0;
    long long sum_a = 0;
    long long sum_b = 0;
    int max_sum = 0;
    while (i < m || j < n) {
      const int ai = (i < m ? a[i] : INT_MAX);
      const int bj = (j < n ? b[j] : INT_MAX);
      if (ai == bj) {
        IncrementBy(max_sum, max(sum_a, sum_b) % kModulo);
        IncrementBy(max_sum, ai);
        sum_a = 0;
        sum_b = 0;
        i++;
        j++;
      } else if (ai < bj) {
        sum_a += ai;
        i++;
      } else {
        sum_b += bj;
        j++;
      }
    }
    IncrementBy(max_sum, max(sum_a, sum_b) % kModulo);
    return max_sum;
  }

 private:
  static void IncrementBy(int& a, int b) { a = (a + b) % kModulo; }

  static constexpr int kModulo = 1000000007;
};

constexpr int Solution::kModulo;

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(30, s.maxSum({2, 4, 5, 8, 10}, {4, 6, 8, 9}));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(109, s.maxSum({1, 3, 5, 7, 9}, {3, 5, 100}));
}

TEST(SolutionTest, testSample3) {
  Solution s;
  EXPECT_EQ(40, s.maxSum({1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}));
}

TEST(SolutionTest, testSample4) {
  Solution s;
  EXPECT_EQ(61, s.maxSum({1, 4, 5, 8, 9, 11, 19}, {2, 3, 4, 11, 12}));
}
