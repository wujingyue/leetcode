#include <iostream>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

constexpr int kDx[] = {-1, 0, 1, 0};
constexpr int kDy[] = {0, 1, 0, -1};

class Solver {
 public:
  Solver(const vector<vector<int>>& grid) : grid_(grid) {
    r_ = grid.size();
    c_ = grid[0].size();
    m_.resize(r_);
    for (int x = 0; x < r_; x++) {
      m_[x].resize(c_);
      for (int y = 0; y < c_; y++) {
        m_[x][y].resize(1 << r_ * c_, -1);
      }
    }
  }

  int Solve() {
    int start_x = -1;
    int start_y = -1;
    int end_x = -1;
    int end_y = -1;
    int end_s = 0;
    for (int x = 0; x < r_; x++) {
      for (int y = 0; y < c_; y++) {
        if (grid_[x][y] == 1) {
          start_x = x;
          start_y = y;
        }
        if (grid_[x][y] == 2) {
          end_x = x;
          end_y = y;
        }
        if (grid_[x][y] != -1) {
          end_s |= (1 << (x * c_ + y));
        }
      }
    }

    m_[start_x][start_y][1 << (start_x * c_ + start_y)] = 1;
    return DFS(end_x, end_y, end_s);
  }

 private:
  int DFS(int x, int y, int s) {
    if (m_[x][y][s] >= 0) {
      return m_[x][y][s];
    }

    int mask = (1 << (x * c_ + y));
    if ((s & mask) == 0) {
      return 0;
    }

    m_[x][y][s] = 0;
    for (int dir = 0; dir < 4; dir++) {
      int x2 = x + kDx[dir];
      int y2 = y + kDy[dir];
      if (x2 < 0 || x2 >= r_ || y2 < 0 || y2 >= c_) {
        continue;
      }
      if (grid_[x2][y2] == -1) {
        continue;
      }
      m_[x][y][s] += DFS(x2, y2, s - mask);
    }
    return m_[x][y][s];
  }

  vector<vector<int>> grid_;
  vector<vector<vector<int>>> m_;
  int r_;
  int c_;
};

class Solution {
 public:
  int uniquePathsIII(const vector<vector<int>>& grid) {
    Solver solver(grid);
    return solver.Solve();
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