#include "gtest/gtest.h"

#include <array>

using namespace std;

class Solution {
 public:
  int maximumUniqueSubarray(const vector<int>& a) {
    int n = a.size();
    int left = 0;
    int right = -1;
    vector<bool> values(kMaxValue + 1);
    int sum = 0;

    int max_sum = 0;
    while (right + 1 < n) {
      if (values[a[right + 1]] == false) {
        values[a[right + 1]] = true;
        sum += a[right + 1];
        right++;
        max_sum = max(max_sum, sum);
      } else {
        values[a[left]] = false;
        sum -= a[left];
        left++;
      }
    }
    return max_sum;
  }

 private:
  static constexpr int kMaxValue = 10000;
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(17, s.maximumUniqueSubarray({4, 2, 4, 5, 6}));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(8, s.maximumUniqueSubarray({5, 2, 1, 2, 5, 2, 1, 2, 5}));
}
