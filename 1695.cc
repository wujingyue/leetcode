#include "gtest/gtest.h"

#include <unordered_set>

using namespace std;

class Solution {
 public:
  int maximumUniqueSubarray(const vector<int>& a) {
    int n = a.size();
    int left = 0;
    int right = -1;
    unordered_set<int> values;
    int sum = 0;

    int max_sum = 0;
    while (right + 1 < n) {
      if (values.count(a[right + 1]) == 0) {
        values.insert(a[right + 1]);
        sum += a[right + 1];
        right++;
        max_sum = max(max_sum, sum);
      } else {
        values.erase(a[left]);
        sum -= a[left];
        left++;
      }
    }
    return max_sum;
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(17, s.maximumUniqueSubarray({4, 2, 4, 5, 6}));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(8, s.maximumUniqueSubarray({5, 2, 1, 2, 5, 2, 1, 2, 5}));
}
