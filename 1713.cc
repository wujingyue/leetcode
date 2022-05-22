#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int minOperations(const vector<int>& a, const vector<int>& b) {
    vector<pair<int, int>> value_pos(a.size());
    for (int i = 0, size = a.size(); i < size; i++) {
      value_pos[i] = make_pair(a[i], i);
    }
    sort(value_pos.begin(), value_pos.end());

    vector<int> poses;
    poses.reserve(b.size());
    for (int i = 0, size = b.size(); i < size; i++) {
      const int pos = BinarySearch(value_pos, b[i]);
      if (pos >= 0) {
        poses.push_back(pos);
      }
    }

    return a.size() - LongestAscendingSubsequence(poses);
  }

 private:
  int BinarySearch(const vector<pair<int, int>>& value_pos, const int value) {
    auto i =
        lower_bound(value_pos.begin(), value_pos.end(), make_pair(value, -1),
                    [](const pair<int, int>& a, const pair<int, int>& b) {
                      return a.first < b.first;
                    });
    if (i == value_pos.end() || i->first != value) {
      return -1;
    }
    return i->second;
  }

  int LongestAscendingSubsequence(const vector<int>& a) {
    const int n = a.size();

    vector<int> lowest_endings(n + 1, INT_MAX);
    lowest_endings[0] = INT_MIN;

    int max_m = 0;
    for (int i = 0; i < n; i++) {
      // Find the largest j such that lowest_endings[j] < a[i].
      // M[i] = j + 1
      int m = lower_bound(lowest_endings.begin(), lowest_endings.end(), a[i]) -
              lowest_endings.begin();
      if (lowest_endings[m] > a[i]) {
        lowest_endings[m] = a[i];
      }
      max_m = max(max_m, m);
    }
    return max_m;
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(s.minOperations({5, 1, 3}, {9, 4, 2, 3, 4}), 2);
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(s.minOperations({6, 4, 8, 1, 3, 2}, {4, 7, 6, 2, 3, 8, 6, 1}), 3);
}