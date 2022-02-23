#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class RangeSumCounter {
 public:
  RangeSumCounter(vector<int64_t>&& values, int lower, int upper)
      : values_(values),
        buffer_(values_.size()),
        lower_(lower),
        upper_(upper) {}
  int Count(int left, int right);

 private:
  vector<int64_t> values_;
  vector<int64_t> buffer_;
  const int lower_;
  const int upper_;
};

int RangeSumCounter::Count(const int left, const int right) {
  if (left >= right) {
    return 0;
  }

  const int mid = left + (right - left) / 2;
  int count = Count(left, mid) + Count(mid + 1, right);

  int low = left;
  int high = left;
  for (int j = mid + 1; j <= right; j++) {
    // In the left half, find the first index >= values_[j] - upper.
    const int64_t new_lower = values_[j] - upper_;
    while (low <= mid && values_[low] < new_lower) {
      low++;
    }
    // In the left half, find the first index > values_[j] - lower.
    const int64_t new_upper = values_[j] - lower_;
    while (high <= mid && values_[high] <= new_upper) {
      high++;
    }
    count += high - low;
  }

  // This is functionality-wise equivalent to inplace_merge. However, reusing a
  // preallocated buffer is much faster.
  merge(&values_[left], &values_[mid + 1], &values_[mid + 1],
        &values_[right + 1], &buffer_[0]);
  copy(&buffer_[0], &buffer_[right - left + 1], &values_[left]);
  return count;
}

class Solution {
 public:
  int countRangeSum(const vector<int>& nums, const int lower, const int upper) {
    const int n = nums.size();

    vector<int64_t> prefix_sums;
    prefix_sums.reserve(n + 1);

    int64_t prefix_sum = 0;
    prefix_sums.push_back(prefix_sum);
    for (const int num : nums) {
      prefix_sum += num;
      prefix_sums.push_back(prefix_sum);
    }

    return RangeSumCounter(std::move(prefix_sums), lower, upper).Count(0, n);
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