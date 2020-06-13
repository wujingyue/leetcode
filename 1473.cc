#include <climits>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int minCost(const vector<int>& houses, vector<vector<int>>& cost,
              const int num_houses, const int num_colors,
              const int num_neighborhoods) {
    const int n = houses.size();

    for (int i = 0; i < n; i++) {
      if (houses[i] > 0) {
        for (int k = 1; k <= num_colors; k++) {
          cost[i][k - 1] = (k == houses[i] ? 0 : INT_MAX);
        }
      }
    }

    int m[kMaxNumNeighborhoods + 1][kMaxNumColors + 1];
    int prefix_min[kMaxNumNeighborhoods + 1][kMaxNumColors + 1];
    int suffix_min[kMaxNumNeighborhoods + 1][kMaxNumColors + 1];
    Fill(m, INT_MAX);
    Fill(prefix_min, INT_MAX);
    Fill(suffix_min, INT_MAX);

    if (houses[0] > 0) {
      m[1][houses[0]] = 0;
    } else {
      for (int k = 1; k <= num_colors; k++) {
        m[1][k] = cost[0][k - 1];
      }
    }
    ComputePrefixSuffixMin(1, num_colors, m, prefix_min, suffix_min);

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
        ComputePrefixSuffixMin(j, num_colors, m, prefix_min, suffix_min);
      }
    }

    int answer = INT_MAX;
    for (int k = 1; k <= num_colors; k++) {
      answer = min(answer, m[num_neighborhoods][k]);
    }
    return (answer == INT_MAX ? -1 : answer);
  }

 private:
  template <int rows, int cols>
  static void ComputePrefixSuffixMin(const int j, const int num_colors,
                                     const int (&m)[rows][cols],
                                     int (&prefix_min)[rows][cols],
                                     int (&suffix_min)[rows][cols]) {
    prefix_min[j][0] = m[j][0];
    for (int k = 1; k <= num_colors; k++) {
      prefix_min[j][k] = min(prefix_min[j][k - 1], m[j][k]);
    }
    suffix_min[j][num_colors] = m[j][num_colors];
    for (int k = num_colors - 1; k >= 0; k--) {
      suffix_min[j][k] = min(suffix_min[j][k + 1], m[j][k]);
    }
  }

  template <class T, int rows, int cols>
  static void Fill(int (&a)[rows][cols], const T value) {
    fill(&a[0][0], &a[0][0] + sizeof(a) / sizeof(T), value);
  }

  static constexpr int kMaxNumNeighborhoods = 100;
  static constexpr int kMaxNumColors = 20;
};

constexpr int Solution::kMaxNumNeighborhoods;
constexpr int Solution::kMaxNumColors;

TEST(SolutionTest, testSample1) {
  Solution s;
  vector<vector<int>> cost({{1, 10}, {10, 1}, {10, 1}, {1, 10}, {5, 1}});
  EXPECT_EQ(9, s.minCost({0, 0, 0, 0, 0}, cost, 5, 2, 3));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  vector<vector<int>> cost({{1, 10}, {10, 1}, {10, 1}, {1, 10}, {5, 1}});
  EXPECT_EQ(11, s.minCost({0, 2, 1, 2, 0}, cost, 5, 2, 3));
}

TEST(SolutionTest, testSample3) {
  Solution s;
  vector<vector<int>> cost({{1, 10}, {10, 1}, {1, 10}, {10, 1}, {1, 10}});
  EXPECT_EQ(5, s.minCost({0, 0, 0, 0, 0}, cost, 5, 2, 5));
}

TEST(SolutionTest, testSample4) {
  Solution s;
  vector<vector<int>> cost({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
  EXPECT_EQ(-1, s.minCost({3, 1, 2, 3}, cost, 4, 3, 3));
}
