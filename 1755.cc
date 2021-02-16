#include <algorithm>
#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int minAbsDifference(const vector<int>& a, const int goal) {
    const int n = a.size();
    vector<int> left_sums = FindSums(a, 0, n / 2);
    vector<int> right_sums = FindSums(a, n / 2, n);

    int min_diff = INT_MAX;
    const int right_sums_size = right_sums.size();
    int j = right_sums_size - 1;
    for (size_t i = 0; i < left_sums.size(); i++) {
      while (j >= 0 && left_sums[i] + right_sums[j] > goal) {
        j--;
      }
      if (j + 1 < right_sums_size) {
        min_diff = min(min_diff, abs(left_sums[i] + right_sums[j + 1] - goal));
      }
      if (j >= 0) {
        min_diff = min(min_diff, abs(left_sums[i] + right_sums[j] - goal));
      }
      if (min_diff == 0) {
        return min_diff;
      }
    }
    return min_diff;
  }

 private:
  vector<int> FindSums(const vector<int>& a, const int begin, const int end) {
    vector<int> sums;
    sums.reserve(1 << (end - begin));
    DFS(a, begin, end, 0, &sums);
    sort(sums.begin(), sums.end());
    sums.erase(unique(sums.begin(), sums.end()), sums.end());
    return sums;
  }

  void DFS(const vector<int>& a, int i, const int end, const int sum,
           vector<int>* sums) {
    if (i == end) {
      sums->push_back(sum);
      return;
    }

    DFS(a, i + 1, end, sum, sums);
    DFS(a, i + 1, end, sum + a[i], sums);
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(s.minAbsDifference({5, -7, 3, 5}, 6), 0);
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(s.minAbsDifference({7, -9, 15, -2}, -5), 1);
}