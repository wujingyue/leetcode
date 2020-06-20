#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int minRefuelStops(const int target, const int start_fuel,
                     const vector<vector<int>>& input_stations) {
    vector<Station> stations;
    stations.push_back(Station{0, start_fuel});
    for (const vector<int>& input_station : input_stations) {
      stations.push_back(Station{input_station[0], input_station[1]});
    }
    stations.push_back(Station{target, 0});

    const int n = stations.size();
    vector<vector<long long>> m(n, vector<long long>(n + 1, LLONG_MIN));
    m[0][1] = stations[0].gas;

    for (int i = 1; i < n; i++) {
      for (int j = 0; j <= n; j++) {
        const int delta_pos = stations[i].pos - stations[i - 1].pos;
        if (m[i - 1][j] >= delta_pos) {
          m[i][j] = max(m[i][j], m[i - 1][j] - delta_pos);
        }
        if (j - 1 >= 0 && m[i - 1][j - 1] >= delta_pos) {
          m[i][j] = max(m[i][j], m[i - 1][j - 1] - delta_pos + stations[i].gas);
        }
      }
    }

    for (int j = 0; j <= n; j++) {
      if (m[n - 1][j] > LLONG_MIN) {
        return j - 1;
      }
    }
    return -1;
  }

 private:
  struct Station {
    int pos;
    int gas;
  };
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
