#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int minDays(const vector<int>& days, const int m, const int k) {
    int min_day = INT_MAX;
    int max_day = INT_MIN;
    for (const int day : days) {
      min_day = min(min_day, day);
      max_day = max(max_day, day);
    }

    int low = min_day;
    int high = max_day + 1;
    // impossible, impossible, possible, ...
    // Find the first possible.
    while (low < high) {
      int mid = low + (high - low) / 2;
      if (IsPossible(days, m, k, mid)) {
        high = mid;
      } else {
        low = mid + 1;
      }
    }
    if (low == max_day + 1) {
      return -1;
    }
    return low;
  }

 private:
  bool IsPossible(const vector<int>& days, const int m, const int k,
                  const int wait) {
    const int n = days.size();
    int num_segments = 0;
    int i = 0;
    while (i < n) {
      if (days[i] > wait) {
        i++;
        continue;
      }

      int j = i + 1;
      while (j < n && j - i < k && days[j] <= wait) {
        j++;
      }
      if (j - i >= k) {
        num_segments++;
      }
      i = j;
    }
    return num_segments >= m;
  }
};

TEST(SolutionTest, testSample) {
  Solution s;
  EXPECT_EQ(3, s.minDays({1, 10, 3, 10, 2}, 3, 1));
}
