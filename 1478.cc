#include <climits>
#include <iostream>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class NaiveDpSolution {
 public:
  int minDistance(vector<int>& a, const int k) {
    sort(a.begin(), a.end());
    const int n = a.size();

    // d[i][j] represents the total distance if we cover House i..j with
    // only one mail box.
    vector<vector<int>> d(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        int mid = i + (j - i) / 2;
        for (int k = i; k <= j; k++) {
          d[i][j] += abs(a[k] - a[mid]);
        }
      }
    }

    vector<vector<int>> m(n + 1, vector<int>(k + 1, INT_MAX));
    vector<vector<int>> c(n + 1, vector<int>(k + 1, -1));
    m[0][0] = 0;
    for (int j = 1; j <= k; j++) {
      for (int i = j; i <= n; i++) {
        // m[i][j] = min(m[t][j - 1] + d[t][i-1])
        // for all 0 <= t < i
        for (int t = 0; t < i; t++) {
          int m2 = m[t][j - 1];
          if (m2 < INT_MAX) {
            const int temp = m2 + d[t][i - 1];
            if (temp < m[i][j]) {
              m[i][j] = temp;
              c[i][j] = t;
            }
          }
        }
      }
    }
    return m[n][k];
  }
};

class OptimizedDpSolution {
 public:
  int minDistance(vector<int>& a, const int k) {
    sort(a.begin(), a.end());
    const int n = a.size();

    constexpr int kMaxN = 100;
    int d[kMaxN][kMaxN];
    for (int i = n - 1; i >= 0; i--) {
      for (int j = i; j < n; j++) {
        if (i == j) {
          d[i][j] = 0;
          continue;
        }
        if (i + 1 == j) {
          d[i][j] = a[j] - a[i];
          continue;
        }
        d[i][j] = d[i + 1][j - 1] + a[j] - a[i];
      }
    }

    vector<int> m(n + 1, INT_MAX);
    vector<int> c(n + 1, -1);
    m[0] = 0;
    for (int j = 1; j <= k; j++) {
      for (int i = n; i >= j; i--) {
        // m[i][j] = min(m[t][j - 1] + d[t][i-1])
        // for all (c[i][j - 1] or 0) <= t <= (c[i + 1][j] or i - 1).
        int start = (c[i] != -1 ? c[i] : 0);
        int end = (i == n ? i - 1 : min(c[i + 1], i - 1));
        m[i] = INT_MAX;
        for (int t = start; t <= end; t++) {
          int m2 = m[t];
          if (m2 < INT_MAX) {
            const int temp = m2 + d[t][i - 1];
            if (temp < m[i]) {
              m[i] = temp;
              c[i] = t;
            }
          }
        }
      }
    }
    return m[n];
  }
};

using Solution = OptimizedDpSolution;

TEST(SolutionTest, testSample1) {
  vector<int> a({1, 4, 8, 10, 20});
  Solution s;
  EXPECT_EQ(5, s.minDistance(a, 3));
}

TEST(SolutionTest, testSample2) {
  vector<int> a({2, 3, 5, 12, 18});
  Solution s;
  EXPECT_EQ(9, s.minDistance(a, 2));
}

TEST(SolutionTest, testSample3) {
  vector<int> a({7, 4, 6, 1});
  Solution s;
  EXPECT_EQ(8, s.minDistance(a, 1));
}

TEST(SolutionTest, testSample4) {
  vector<int> a({3, 6, 14, 10});
  Solution s;
  EXPECT_EQ(0, s.minDistance(a, 4));
}

TEST(SolutionTest, testRandom) {
  srand(time(nullptr));
  const int n = 100;
  const int max_distance = 10000;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = rand() % max_distance + 1;
  }
  const int k = rand() % n + 1;

  NaiveDpSolution ns;
  OptimizedDpSolution os;
  EXPECT_EQ(ns.minDistance(a, k), os.minDistance(a, k));
}
