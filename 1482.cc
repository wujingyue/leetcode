#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class BinarySearchSolution {
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

using Solution = BinarySearchSolution;

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(3, s.minDays({1, 10, 3, 10, 2}, 3, 1));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(-1, s.minDays({1, 10, 3, 10, 2}, 3, 2));
}

TEST(SolutionTest, testSample3) {
  Solution s;
  EXPECT_EQ(12, s.minDays({7, 7, 7, 7, 12, 7, 7}, 2, 3));
}

TEST(SolutionTest, testSample4) {
  Solution s;
  EXPECT_EQ(1000000000, s.minDays({1000000000, 1000000000}, 1, 1));
}

TEST(SolutionTest, testSample5) {
  Solution s;
  EXPECT_EQ(9, s.minDays({1, 10, 2, 9, 3, 8, 4, 7, 5, 6}, 4, 2));
}
