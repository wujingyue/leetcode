#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  bool isEscapePossible(const vector<vector<int>>& blocked,
                        const vector<int>& source, const vector<int>& target) {
    vector<int> xs;
    vector<int> ys;
    for (const vector<int>& obstacle : blocked) {
      AddCoordinates(obstacle[0], &xs);
      AddCoordinates(obstacle[1], &ys);
    }
    AddCoordinates(source[0], &xs);
    AddCoordinates(source[1], &ys);
    AddCoordinates(target[0], &xs);
    AddCoordinates(target[1], &ys);

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    const int r = xs.size();
    const int c = ys.size();
    vector<vector<bool>> is_obstacle(r, vector<bool>(c));
    for (const vector<int>& obstacle : blocked) {
      int x = GetCoordinate(xs, obstacle[0]);
      int y = GetCoordinate(ys, obstacle[1]);
      is_obstacle[x][y] = true;
    }

    const int sx = GetCoordinate(xs, source[0]);
    const int sy = GetCoordinate(ys, source[1]);
    const int tx = GetCoordinate(xs, target[0]);
    const int ty = GetCoordinate(ys, target[1]);
    if (is_obstacle[sx][sy] || is_obstacle[tx][ty]) {
      return false;
    }

    vector<pair<int, int>> stack;
    vector<vector<bool>> visited(r, vector<bool>(c));

    stack.push_back({sx, sy});
    visited[sx][sy] = true;

    while (!stack.empty()) {
      const int x = stack.back().first;
      const int y = stack.back().second;
      stack.pop_back();
      for (int dir = 0; dir < 4; dir++) {
        const int x2 = x + kDx[dir];
        const int y2 = y + kDy[dir];
        if (x2 >= 0 && x2 < r && y2 >= 0 && y2 < c && !visited[x2][y2] &&
            !is_obstacle[x2][y2]) {
          stack.push_back({x2, y2});
          visited[x2][y2] = true;
          if (x2 == tx && y2 == ty) {
            return true;
          }
        }
      }
    }
    return false;
  }

 private:
  void AddCoordinates(const int x, vector<int>* xs) {
    if (x - 1 >= 0) {
      xs->push_back(x - 1);
    }
    xs->push_back(x);
    if (x + 1 < 1000000) {
      xs->push_back(x + 1);
    }
  }

  int GetCoordinate(const vector<int>& xs, const int x) {
    return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
  }

  static constexpr int kDx[] = {-1, 0, 1, 0};
  static constexpr int kDy[] = {0, 1, 0, -1};
};

constexpr int Solution::kDx[];
constexpr int Solution::kDy[];

TEST(SolutionTest, testBlocked) {
  Solution s;
  EXPECT_EQ(false, s.isEscapePossible({{0, 1}, {1, 0}}, {0, 0}, {0, 2}));
}

TEST(SolutionTest, testNotBlocked) {
  Solution s;
  EXPECT_EQ(true, s.isEscapePossible({}, {0, 0}, {999999, 999999}));
}
