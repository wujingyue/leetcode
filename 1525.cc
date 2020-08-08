#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int numSplits(const string& a) {
    const int n = a.size();

    array<int, 26> left = {0};
    array<int, 26> right = {0};
    int left_non_zero = 0;
    int right_non_zero = 0;

    for (int j = 0; j < n; j++) {
      const int k = a[j] - 'a';
      right[k]++;
      if (right[k] == 1) {
        right_non_zero++;
      }
    }

    int num_splits = 0;
    for (int s = 1; s < n; s++) {
      const int k = a[s - 1] - 'a';
      // add a[s-1] to left
      left[k]++;
      if (left[k] == 1) {
        left_non_zero++;
      }
      // remove a[s-1] from right
      right[k]--;
      if (right[k] == 0) {
        right_non_zero--;
      }
      if (left_non_zero == right_non_zero) {
        num_splits++;
      }
    }
    return num_splits;
  }
};

TEST(SolutionTest, testSample) {
  Solution s;
  EXPECT_EQ(2, s.numSplits("aacaba"));
}
