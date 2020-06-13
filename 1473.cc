#include <climits>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int minCost(const vector<int>& houses, const vector<vector<int>>& orig_cost,
              const int num_houses, const int num_colors,
              const int num_neighborhoods) {
    const int n = houses.size();

    vector<vector<int>> cost(orig_cost);
    for (int i = 0; i < n; i++) {
      if (houses[i] > 0) {
        for (int k = 1; k <= num_colors; k++) {
          cost[i][k - 1] = (k == houses[i] ? 0 : INT_MAX);
        }
      }
    }

    vector<vector<int>> m(num_neighborhoods + 1,
                          vector<int>(num_colors + 1, INT_MAX));
    vector<vector<int>> prefix_min(num_neighborhoods + 1,
                                   vector<int>(num_colors + 1, INT_MAX));
    vector<vector<int>> suffix_min(num_neighborhoods + 1,
                                   vector<int>(num_colors + 1, INT_MAX));
    if (houses[0] > 0) {
      m[1][houses[0]] = 0;
    } else {
      for (int k = 1; k <= num_colors; k++) {
        m[1][k] = cost[0][k - 1];
      }
    }
    ComputePrefixSuffixMin(1, m, prefix_min, suffix_min);

    for (int i = 1; i < n; i++) {
      for (int j = 1; j <= num_neighborhoods; j++) {
        for (int k = 1; k <= num_colors; k++) {
          if (cost[i][k - 1] == INT_MAX) {
            m[j][k] = INT_MAX;
            continue;
          }

          int local_min = min(m[j][k], prefix_min[j - 1][k - 1]);
          if (k + 1 <= num_colors) {
            local_min = min(local_min, suffix_min[j - 1][k + 1]);
          }
          if (local_min < INT_MAX) {
            local_min += cost[i][k - 1];
          }
          m[j][k] = local_min;
        }
      }
      for (int j = 1; j <= num_neighborhoods; j++) {
        ComputePrefixSuffixMin(j, m, prefix_min, suffix_min);
      }
    }

    int answer = INT_MAX;
    for (int k = 1; k <= num_colors; k++) {
      answer = min(answer, m[num_neighborhoods][k]);
    }
    return (answer == INT_MAX ? -1 : answer);
  }

 private:
  static void ComputePrefixSuffixMin(const int j, const vector<vector<int>>& m,
                                     vector<vector<int>>& prefix_min,
                                     vector<vector<int>>& suffix_min) {
    const int num_colors = m[j].size() - 1;
    prefix_min[j][0] = m[j][0];
    for (int k = 1; k <= num_colors; k++) {
      prefix_min[j][k] = min(prefix_min[j][k - 1], m[j][k]);
    }
    suffix_min[j][num_colors] = m[j][num_colors];
    for (int k = num_colors - 1; k >= 0; k--) {
      suffix_min[j][k] = min(suffix_min[j][k + 1], m[j][k]);
    }
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(9,
            s.minCost({0, 0, 0, 0, 0},
                      {{1, 10}, {10, 1}, {10, 1}, {1, 10}, {5, 1}}, 5, 2, 3));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(11,
            s.minCost({0, 2, 1, 2, 0},
                      {{1, 10}, {10, 1}, {10, 1}, {1, 10}, {5, 1}}, 5, 2, 3));
}

TEST(SolutionTest, testSample3) {
  Solution s;
  EXPECT_EQ(5,
            s.minCost({0, 0, 0, 0, 0},
                      {{1, 10}, {10, 1}, {1, 10}, {10, 1}, {1, 10}}, 5, 2, 5));
}

TEST(SolutionTest, testSample4) {
  Solution s;
  EXPECT_EQ(
      -1, s.minCost({3, 1, 2, 3}, {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
                    4, 3, 3));
}
