#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class ReversePairCounter {
 public:
  ReversePairCounter(vector<int>& nums) : nums_(nums), buffer_(nums.size()) {}

  int Count(int left, int right) {
    if (right - left <= 1) {
      return 0;
    }
    const int mid = left + (right - left) / 2;
    int count = Count(left, mid) + Count(mid, right);
    int i = left;
    for (int j = mid; j < right; j++) {
      while (i < mid && nums_[i] <= static_cast<int64_t>(nums_[j]) * 2) {
        i++;
      }
      count += mid - i;
    }
    merge(&nums_[left], &nums_[mid], &nums_[mid], &nums_[right],
          &buffer_[left]);
    copy(&buffer_[left], &buffer_[right], &nums_[left]);
    return count;
  }

 private:
  vector<int>& nums_;
  vector<int> buffer_;
};

class Solution {
 public:
  int reversePairs(vector<int>& nums) {
    const int n = nums.size();
    return ReversePairCounter(nums).Count(0, n);
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  vector<int> nums({1, 3, 2, 3, 1});
  EXPECT_EQ(s.reversePairs(nums), 2);
}

TEST(SolutionTest, testSample2) {
  Solution s;
  vector<int> nums({2, 4, 3, 5, 1});
  EXPECT_EQ(s.reversePairs(nums), 3);
}