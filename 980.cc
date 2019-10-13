#include <iostream>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

constexpr int kDx[] = {-1, 0, 1, 0};
constexpr int kDy[] = {0, 1, 0, -1};

struct Node {
  bool operator<(const Node& other) const { return s > other.s; }

  int x;
  int y;
  int s;
};

class Solution {
 public:
  int uniquePathsIII(const vector<vector<int>>& grid) {
    int r = grid.size();
    int c = grid[0].size();
    int start_x = -1;
    int start_y = -1;
    int end_x = -1;
    int end_y = -1;
    int end_s = 0;
    for (int x = 0; x < r; x++) {
      for (int y = 0; y < c; y++) {
        if (grid[x][y] == 1) {
          start_x = x;
          start_y = y;
        }
        if (grid[x][y] == 2) {
          end_x = x;
          end_y = y;
        }
        if (grid[x][y] != -1) {
          end_s |= (1 << (x * c + y));
        }
      }
    }

    vector<vector<vector<int>>> m(
        r, vector<vector<int>>(c, vector<int>(1 << r * c)));
    priority_queue<Node> q;

    int start_s = (1 << (start_x * c + start_y));
    m[start_x][start_y][start_s] = 1;
    q.push(Node{start_x, start_y, start_s});
    while (!q.empty()) {
      const Node& top = q.top();
      const int x = top.x;
      const int y = top.y;
      const int s = top.s;
      const int value = m[x][y][s];
      q.pop();

      if (s >= end_s) {
        break;
      }

      for (int dir = 0; dir < 4; dir++) {
        int x2 = x + kDx[dir];
        int y2 = y + kDy[dir];
        if (x2 < 0 || x2 >= r || y2 < 0 || y2 >= c) {
          continue;
        }
        if (grid[x2][y2] == -1) {
          continue;
        }
        int mask2 = (1 << (x2 * c + y2));
        if (s & mask2) {
          continue;
        }
        int s2 = s + mask2;
        int& value2 = m[x2][y2][s2];
        if (value2 == 0) {
          q.push(Node{x2, y2, s2});
        }
        value2 += value;
      }
    }

    return m[end_x][end_y][end_s];
  }
};

class SolutionTest : public testing::Test {
 protected:
  Solution s_;
};

TEST_F(SolutionTest, testSample1) {
  EXPECT_EQ(2, s_.uniquePathsIII({{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1}}));
}

TEST_F(SolutionTest, testSample2) {
  EXPECT_EQ(4, s_.uniquePathsIII({{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 2}}));
}

TEST_F(SolutionTest, testSample3) {
  EXPECT_EQ(0, s_.uniquePathsIII({{0, 1}, {2, 0}}));
}

TEST_F(SolutionTest, testLarge) {
  EXPECT_EQ(20, s_.uniquePathsIII({{1, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 2}}));
}