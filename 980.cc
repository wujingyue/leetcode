#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

constexpr int kDx[] = {-1, 0, 1, 0};
constexpr int kDy[] = {0, 1, 0, -1};

struct Node {
  bool operator<(const Node& other) const { return s > other.s; }
  bool operator==(const Node& other) const {
    return x == other.x && y == other.y && s == other.s;
  }

  int x;
  int y;
  int s;
};

namespace std {
template <>
struct hash<Node> {
  size_t operator()(const Node& n) const {
    constexpr int kMaxRows = 20;
    constexpr int kMaxCols = 20;
    return (n.s * kMaxRows + n.x) * kMaxCols + n.y;
  }
};
}  // namespace std

class BFSMemoizationSolution {
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

    unordered_map<Node, int> m;
    priority_queue<Node> q;

    int start_s = (1 << (start_x * c + start_y));
    Node start{start_x, start_y, start_s};
    m[start] = 1;
    q.push(start);
    while (!q.empty()) {
      const Node& top = q.top();
      const int x = top.x;
      const int y = top.y;
      const int s = top.s;
      const int value = m.at(top);
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
        Node neighbor{x2, y2, s2};

        if (!m.count(neighbor)) {
          q.push(neighbor);
        }
        m[neighbor] += value;
      }
    }

    return m[Node{end_x, end_y, end_s}];
  }
};

class DFSSolver {
 public:
  DFSSolver(const vector<vector<int>>& grid) : grid_(grid) {
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
    int& value = m_[x][y][s];
    if (value >= 0) {
      return value;
    }

    int mask = (1 << (x * c_ + y));
    if ((s & mask) == 0) {
      return 0;
    }

    value = 0;
    for (int dir = 0; dir < 4; dir++) {
      int x2 = x + kDx[dir];
      int y2 = y + kDy[dir];
      if (x2 < 0 || x2 >= r_ || y2 < 0 || y2 >= c_) {
        continue;
      }
      if (grid_[x2][y2] == -1) {
        continue;
      }
      value += DFS(x2, y2, s - mask);
    }
    return value;
  }

  vector<vector<int>> grid_;
  vector<vector<vector<int>>> m_;
  int r_;
  int c_;
};

class DFSMemoizationSolution {
 public:
  int uniquePathsIII(const vector<vector<int>>& grid) {
    DFSSolver solver(grid);
    return solver.Solve();
  }
};

using Solution = BFSMemoizationSolution;

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