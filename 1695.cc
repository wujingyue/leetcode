#include "gtest/gtest.h"

#include <array>

using namespace std;

class Solution {
 public:
  int maximumUniqueSubarray(const vector<int>& a) {
    int n = a.size();
    int left = 0;
    int right = 0;
    vector<bool> values(kMaxValue + 1);
    int sum = 0;

    int max_sum = 0;
    while (right < n) {
      const int right_value = a[right];
      if (values[right_value] == false) {
        values[right_value] = true;
        sum += right_value;
        right++;
        max_sum = max(max_sum, sum);
      } else {
        const int left_value = a[left];
        values[left_value] = false;
        sum -= left_value;
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
