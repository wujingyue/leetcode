#include <algorithm>
#include <climits>
#include <set>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int findMaxValueOfEquation(const vector<vector<int>>& points, const int k) {
    const int n = points.size();

    set<pair<int, int>> additions;
    set<pair<int, int>> subtractions;
    int j = 0;
    int max_value = INT_MIN;
    for (int i = 0; i < n; i++) {
      while (j < n && points[j][0] - points[i][0] <= k) {
        additions.insert(make_pair(points[j][0] + points[j][1], j));
        subtractions.insert(make_pair(points[j][1] - points[j][0], j));
        j++;
      }
      if (!additions.empty()) {
        auto max_addition = additions.rbegin();
        auto max_subtraction = subtractions.rbegin();
        if (max_addition->second != max_subtraction->second) {
          max_value =
              max(max_value, max_addition->first + max_subtraction->first);
        } else if (additions.size() >= 2) {
          auto previous_addition = max_addition;
          ++previous_addition;
          auto previous_subtraction = max_subtraction;
          ++previous_subtraction;
          max_value =
              max(max_value, previous_addition->first + max_subtraction->first);
          max_value =
              max(max_value, max_addition->first + previous_subtraction->first);
        }
      }
      additions.erase(make_pair(points[i][0] + points[i][1], i));
      subtractions.erase(make_pair(points[i][1] - points[i][0], i));
    }
    return max_value;
  }
};

TEST(SolutionTest, testSample) {
  Solution s;
  EXPECT_EQ(4,
            s.findMaxValueOfEquation({{1, 3}, {2, 0}, {5, 10}, {6, -10}}, 1));
}
