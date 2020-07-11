#include <algorithm>
#include <climits>
#include <set>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int findMaxValueOfEquation(const vector<vector<int>>& points, const int k) {
    const int n = points.size();

    deque<pair<int, int>> q;
    int max_value = INT_MIN;
    for (int i = 0; i < n; i++) {
      while (!q.empty() && points[i][0] - q.front().first > k) {
        q.pop_front();
      }
      if (!q.empty()) {
        max_value = max(max_value, points[i][0] - q.front().first +
                                       points[i][1] + q.front().second);
      }
      while (!q.empty() &&
             points[i][1] - q.back().second >= points[i][0] - q.back().first) {
        q.pop_back();
      }
      q.push_back({points[i][0], points[i][1]});
    }
    return max_value;
  }
};

TEST(SolutionTest, testSample) {
  Solution s;
  EXPECT_EQ(4,
            s.findMaxValueOfEquation({{1, 3}, {2, 0}, {5, 10}, {6, -10}}, 1));
}
