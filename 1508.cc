#include "gtest/gtest.h"

#include <numeric>
#include <vector>

using namespace std;

class Solution {
 public:
  int rangeSum(const vector<int>& a, const int n, const int left, const int right) {
    vector<int> sums;
    sums.reserve(n * (n + 1) / 2);
    for (int i = 0; i < n; i++) {
      int sum = 0;
      for (int j = i; j < n; j++) {
        sum += a[j];
        sums.push_back(sum);
      }
    }

    nth_element(sums.begin(), sums.begin() + left - 1, sums.end());
    nth_element(sums.begin() + left, sums.begin() + right - 1, sums.end());

    int answer = 0;
    for (int i = left - 1; i <= right - 1; i++) {
      answer = (answer + sums[i]) % kModulo;
    }
    return answer;
  }

 private:
  static constexpr int kModulo = 1000000007;
};

constexpr int Solution::kModulo;

TEST(SolutionTest, testSample) {
  Solution s;
  EXPECT_EQ(13, s.rangeSum({1, 2, 3, 4}, 4, 1, 5));
}
