#include <climits>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int shortestPath(const vector<vector<int>>& a, const int k) {
    const int m = a.size();
    const int n = a[0].size();
    vector<vector<vector<int>>> d(
        m, vector<vector<int>>(n, vector<int>(k + 1, INT_MAX)));

    queue<State> q;
    q.push(State{0, 0, k});
    d[0][0][k] = 0;
    if (0 == m - 1 && 0 == n - 1) {
      return 0;
    }

    while (!q.empty()) {
      const State front = q.front();
      q.pop();
      for (int dir = 0; dir < 4; dir++) {
        const int x = front.x + kDx[dir];
        const int y = front.y + kDy[dir];
        if (x < 0 || x >= m || y < 0 || y >= n) {
          continue;
        }
        const int z = front.z - a[x][y];
        if (z < 0) {
          continue;
        }
        if (d[x][y][z] < INT_MAX) {
          continue;
        }
        q.push(State{x, y, z});
        const int step = d[front.x][front.y][front.z] + 1;
        d[x][y][z] = step;
        if (x == m - 1 && y == n - 1) {
          return step;
        }
      }
    }
    return -1;
  }

 private:
  struct State {
    int x;
    int y;
    int z;
  };

  const int kDx[4] = {-1, 0, 1, 0};
  const int kDy[4] = {0, 1, 0, -1};
};

TEST(SolutionTest, sample) {
  Solution s;
  EXPECT_EQ(6, s.shortestPath(
                   {{0, 0, 0}, {1, 1, 0}, {0, 0, 0}, {0, 1, 1}, {0, 0, 0}}, 1));
}

TEST(SolutionTest, impossible) {
  Solution s;
  EXPECT_EQ(-1, s.shortestPath({{0, 1, 1}, {1, 1, 1}, {1, 0, 0}}, 1));
}