#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  using Event = vector<int>;

  int maxValue(vector<Event>& events, const int k) {
    auto comparator = [](const Event& e1, const Event& e2) {
      return e1[0] < e2[0];
    };
    sort(events.begin(), events.end(), comparator);

    const int n = events.size();
    vector<int> next_disjoint(n);
    for (int i = n - 1; i >= 0; i--) {
      const int end_time = events[i][1];
      next_disjoint[i] = upper_bound(events.begin() + i + 1, events.end(),
                                     Event({end_time, 0, 0}), comparator) -
                         events.begin();
    }

    vector<int> m(n + 1, 0);
    int answer = 0;
    for (int j = 1; j <= k; j++) {
      // m[i][j] = max(m[i + 1][j], m[i2][j - 1] + events[i][2])
      // where i2 is the smallest index such that events[i][1] <
      // events[i2][0].
      for (int i = 0; i <= n - j; i++) {
        const int i2 = next_disjoint[i];
        m[i] = (i2 + j - 1 <= n ? m[i2] + events[i][2] : INT_MIN);
      }
      int max_m = m[n - j];
      for (int i = n - j - 1; i >= 0; i--) {
        m[i] = max_m = max(m[i], max_m);
      }
      answer = max(answer, m[0]);
    }
    return answer;
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

TEST(SolutionTest, testSample4) {
  Solution s;
  vector<vector<int>> events({{69, 83, 61}, {44, 90, 19}, {26, 87, 9}});
  EXPECT_EQ(s.maxValue(events, 3), 61);
}