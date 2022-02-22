#include <algorithm>
#include <cassert>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class OrderedMultiset {
 public:
  OrderedMultiset(vector<int64_t>&& values)
      : values_(values), counts_(values.size()) {}
  void Insert(int64_t value);
  int CountLessThan(int64_t value) const;

 private:
  vector<int64_t> values_;
  vector<int> counts_;
};

void OrderedMultiset::Insert(const int64_t value) {
  const int i =
      lower_bound(values_.begin(), values_.end(), value) - values_.begin();
  assert(i < (int)values_.size());
  assert(values_[i] == value);
  counts_[i]++;
}

int OrderedMultiset::CountLessThan(const int64_t value) const {
  int count = 0;
  for (int i = 0, size = values_.size(); i < size && values_[i] < value; i++) {
    count += counts_[i];
  }
  return count;
}

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

    OrderedMultiset ordered_multiset(std::move(prefix_sums));

    int count = 0;
    prefix_sum = 0;
    for (int num : nums) {
      ordered_multiset.Insert(prefix_sum);
      // lower <= prefix_sum - previous_prefix_sum <= upper
      // prefix_sum - upper <= previous_prefix_sum < prefix_sum - lower + 1
      prefix_sum += num;
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