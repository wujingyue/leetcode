#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int maxValue(vector<vector<int>>& events, const int k) {
    sort(events.begin(), events.end());

    const int n = events.size();
    vector<vector<int>> m(n + 1, vector<int>(k + 1, INT_MIN));
    m[n][0] = 0;
    for (int i = n - 1; i >= 0; i--) {
      const int end_time = events[i][1];
      int i2 = upper_bound(events.begin() + i + 1, events.end(),
                           vector<int>({end_time, INT_MAX, INT_MAX})) -
               events.begin();
      for (int j = 0; j <= k; j++) {
        // m[i][j] = max(m[i + 1][j], m[i2][j - 1] + events[i][2])
        // where i2 is the smallest index such that events[i][1] <
        // events[i2][0].
        m[i][j] = m[i + 1][j];
        if (j - 1 >= 0 && m[i2][j - 1] > INT_MIN) {
          m[i][j] = max(m[i][j], m[i2][j - 1] + events[i][2]);
        }
      }
    }
    return *max_element(m[0].begin(), m[0].end());
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  vector<vector<int>> events({{1, 2, 4}, {3, 4, 3}, {2, 3, 1}});
  EXPECT_EQ(s.maxValue(events, 2), 7);
}

TEST(SolutionTest, testSample2) {
  Solution s;
  vector<vector<int>> events({{1, 2, 4}, {3, 4, 3}, {2, 3, 10}});
  EXPECT_EQ(s.maxValue(events, 2), 10);
}

TEST(SolutionTest, testSample3) {
  Solution s;
  vector<vector<int>> events({{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}});
  EXPECT_EQ(s.maxValue(events, 3), 9);
}