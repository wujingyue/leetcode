#include "gtest/gtest.h"

#include <cassert>
#include <vector>

using namespace std;

class Solution {
 public:
  int canCompleteCircuit(const vector<int>& gas, const vector<int>& cost) {
    const int n = gas.size();
    assert(n == (int)cost.size());

    int prefix_sum = 0;
    int min_prefix_sum = 0;
    int arg_min = 0;
    for (int i = 0; i < n; i++) {
      prefix_sum += gas[i] - cost[i];
      if (prefix_sum < min_prefix_sum) {
        min_prefix_sum = prefix_sum;
        arg_min = i + 1;
      }
    }
    if (prefix_sum < 0) {
      return -1;
    }
    assert(arg_min != n);
    return arg_min;
  }
};

TEST(SolutionTest, testPossible) {
  Solution s;
  EXPECT_EQ(3, s.canCompleteCircuit({1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}));
}

TEST(SolutionTest, testImpossible) {
  Solution s;
  EXPECT_EQ(-1, s.canCompleteCircuit({2, 3, 4}, {3, 4, 3}));
}
