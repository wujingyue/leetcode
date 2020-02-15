#include <climits>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int maxDistance(const vector<vector<int>>& a) {
    const int r = a.size();
    const int c = a[0].size();

    queue<pair<int, int>> q;
    vector<vector<int>> d(r, vector<int>(c, INT_MAX));

    for (int x = 0; x < r; x++) {
      for (int y = 0; y < c; y++) {
        if (a[x][y] == 1) {
          q.push(make_pair(x, y));
          d[x][y] = 0;
        }
      }
    }

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
        q.push(make_pair(x2, y2));
        d[x2][y2] = d[x][y] + 1;
      }
    }

    int max_distance = 0;
    for (int x = 0; x < r; x++) {
      for (int y = 0; y < c; y++) {
        max_distance = max(max_distance, d[x][y]);
      }
    }
    return (max_distance == 0 || max_distance == INT_MAX ? -1 : max_distance);
  }

 private:
  static const int kDx[];
  static const int kDy[];
};

const int Solution::kDx[] = {-1, 0, 1, 0};
const int Solution::kDy[] = {0, 1, 0, -1};

TEST(SolutionTest, sample) {
  vector<vector<int>> a;
  a.push_back({1, 0, 1});
  a.push_back({0, 0, 0});
  a.push_back({1, 0, 1});

  Solution s;
  EXPECT_EQ(2, s.maxDistance(a));
}

TEST(SolutionTest, noLand) {
  vector<vector<int>> a;
  a.push_back({0, 0, 0});
  a.push_back({0, 0, 0});
  a.push_back({0, 0, 0});

  Solution s;
  EXPECT_EQ(-1, s.maxDistance(a));
}