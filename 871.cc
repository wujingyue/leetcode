#include <climits>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int minRefuelStops(const int target, const int start_fuel,
                     const vector<vector<int>>& stations) {
    const int n = stations.size();
    int cur_fuel = start_fuel;
    int prev_pos = 0;
    priority_queue<int> stop_fuels;
    int num_stops = 0;

    for (int i = 0; i < n; i++) {
      if (!MoveForward(stations[i][0] - prev_pos, &cur_fuel, &stop_fuels,
                        &num_stops)) {
        return -1;
      }
      stop_fuels.push(stations[i][1]);
      prev_pos = stations[i][0];
    }

    if (!MoveForward(target - prev_pos, &cur_fuel, &stop_fuels, &num_stops)) {
      return -1;
    }
    return num_stops;
  }

 private:
  bool MoveForward(const int distance, int* cur_fuel,
                   priority_queue<int>* stop_fuels, int* num_stops) {
    (*cur_fuel) -= distance;
    while (*cur_fuel < 0 && !stop_fuels->empty()) {
      (*cur_fuel) += stop_fuels->top();
      (*num_stops)++;
      stop_fuels->pop();
    }
    if (*cur_fuel < 0) {
      return false;
    }
    return true;
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(0, s.minRefuelStops(1, 1, {}));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(-1, s.minRefuelStops(100, 1, {{10, 100}}));
}

TEST(SolutionTest, testSample3) {
  Solution s;
  EXPECT_EQ(
      2, s.minRefuelStops(100, 10, {{10, 60}, {20, 30}, {30, 30}, {60, 40}}));
}
