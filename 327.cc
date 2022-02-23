#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

#include "ordered_multiset.h"

using namespace std;

class Solution {
 public:
  int countRangeSum(const vector<int>& nums, const int lower, const int upper) {
    const int n = nums.size();

    vector<int64_t> prefix_sums;
    prefix_sums.reserve(n);

    int64_t prefix_sum = 0;
    for (const int num : nums) {
      prefix_sums.push_back(prefix_sum);
      prefix_sum += num;
    }
    sort(prefix_sums.begin(), prefix_sums.end());
    prefix_sums.erase(unique(prefix_sums.begin(), prefix_sums.end()),
                      prefix_sums.end());

    OrderedMultiset<int64_t> ordered_multiset(prefix_sums);

    int count = 0;
    prefix_sum = 0;
    for (const int num : nums) {
      // Insert last prefix sum.
      ordered_multiset.Insert(prefix_sum);
      prefix_sum += num;
      // Find the number of previous prefix sums that satisfy
      //   lower <= prefix_sum - previous_prefix_sum <= upper
      // i.e.
      //   prefix_sum - upper <= previous_prefix_sum < prefix_sum - lower + 1
      count += ordered_multiset.CountLessThan(prefix_sum - lower + 1) -
               ordered_multiset.CountLessThan(prefix_sum - upper);
    }
    return count;
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(s.countRangeSum({-2, 5, -1}, -2, 2), 3);
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(s.countRangeSum({0}, 0, 0), 1);
}