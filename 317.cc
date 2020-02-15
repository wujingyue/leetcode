#include <climits>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int shortestDistance(const vector<vector<int>>& a) {
    const int r = a.size();
    const int c = a[0].size();

    vector<vector<int>> sum_d(r, vector<int>(c));
    for (int x = 0; x < r; x++) {
      for (int y = 0; y < c; y++) {
        if (a[x][y] == 1) {
          vector<vector<int>> d = BFS(a, x, y);
          for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
              if (sum_d[i][j] == INT_MAX || d[i][j] == INT_MAX) {
                sum_d[i][j] = INT_MAX;
              } else {
                sum_d[i][j] += d[i][j];
              }
            }
          }
        }
      }
    }

    int shortest_distance = INT_MAX;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (a[i][j] == 0) {
          shortest_distance = min(shortest_distance, sum_d[i][j]);
        }
      }
    }
    return (shortest_distance == INT_MAX ? -1 : shortest_distance);
  }

 private:
  vector<vector<int>> BFS(const vector<vector<int>>& a, const int start_x,
                          const int start_y) {
    const int r = a.size();
    const int c = a[0].size();
    vector<vector<int>> d(r, vector<int>(c, INT_MAX));

    queue<pair<int, int>> q;
    d[start_x][start_y] = 0;
    q.push(make_pair(start_x, start_y));

    while (!q.empty()) {
      const int x = q.front().first;
      const int y = q.front().second;
      q.pop();

      for (int dir = 0; dir < 4; dir++) {
        const int x2 = x + kDx[dir];
        const int y2 = y + kDy[dir];
        if (x2 < 0 || x2 >= r || y2 < 0 || y2 >= c) {
          continue;
        }
        if (d[x2][y2] < INT_MAX) {
          continue;
        }
        if (a[x2][y2] != 0) {
          continue;
        }
        d[x2][y2] = d[x][y] + 1;
        q.push(make_pair(x2, y2));
      }
    }

    return d;
  }

  static const int kDx[];
  static const int kDy[];
};

const int Solution::kDx[] = {-1, 0, 1, 0};
const int Solution::kDy[] = {0, 1, 0, -1};

TEST(SolutionTest, sample) {
  vector<vector<int>> a;
  a.push_back({1, 0, 2, 0, 1});
  a.push_back({0, 0, 0, 0, 0});
  a.push_back({0, 0, 1, 0, 0});

  Solution s;
  EXPECT_EQ(7, s.shortestDistance(a));
}

TEST(SolutionTest, notConnected) {
  vector<vector<int>> a;
  a.push_back({1, 0, 2, 0, 1});
  a.push_back({0, 0, 2, 0, 0});
  a.push_back({0, 0, 2, 0, 0});

  Solution s;
  EXPECT_EQ(-1, s.shortestDistance(a));
}

TEST(SolutionTest, notPassThroughBuildings) {
  vector<vector<int>> a = {{1, 1}, {0, 1}};
  Solution s;
  EXPECT_EQ(-1, s.shortestDistance(a));
}