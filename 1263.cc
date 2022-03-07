#include <algorithm>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

struct Position {
  int x;
  int y;

  bool Valid() const { return x != -1 && y != -1; }
  bool operator==(const Position& other) const {
    return tie(x, y) == tie(other.x, other.y);
  }
  bool operator!=(const Position& other) const { return !(*this == other); }

  static Position InvalidPosition() { return {-1, -1}; }
};

template <>
struct std::hash<Position> {
  size_t operator()(const Position& p) const noexcept { return p.x * 32 + p.y; }
};

struct State {
  Position person;
  Position box;
  bool operator==(const State& other) const {
    return person == other.person && box == other.box;
  }
};

template <>
struct std::hash<State> {
  size_t operator()(const State& s) const noexcept {
    hash<Position> position_hash;
    return position_hash(s.person) * 32 * 32 + position_hash(s.box);
  }
};

struct Grid {
  Grid(int r, int c) : rows(r), cols(c), is_empty(rows) {
    for (int x = 0; x < rows; x++) {
      is_empty[x].resize(cols);
    }
  }

  Position NeighborOf(const Position& p, const int dir) const {
    constexpr int kDx[] = {-1, 1, 0, 0};
    constexpr int kDy[] = {0, 0, -1, 1};
    const int x = p.x + kDx[dir];
    const int y = p.y + kDy[dir];
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
      return Position::InvalidPosition();
    }
    return {x, y};
  }

  bool IsEmpty(const Position& p) const { return is_empty[p.x][p.y]; }

  int rows;
  int cols;
  vector<vector<bool>> is_empty;
};

class Solution {
 public:
  int minPushBox(const vector<vector<char>>& cells) {
    Grid grid(cells.size(), cells[0].size());

    Position person_start = Position::InvalidPosition();
    Position box_start = Position::InvalidPosition();
    Position box_end = Position::InvalidPosition();
    for (int x = 0; x < grid.rows; x++) {
      for (int y = 0; y < grid.cols; y++) {
        if (cells[x][y] == '#') {
          grid.is_empty[x][y] = false;
        } else {
          grid.is_empty[x][y] = true;
          if (cells[x][y] == 'S') {
            person_start = {x, y};
          } else if (cells[x][y] == 'B') {
            box_start = {x, y};
          } else if (cells[x][y] == 'T') {
            box_end = {x, y};
          }
        }
      }
    }
    assert(person_start.Valid());
    assert(box_start.Valid());
    assert(box_end.Valid());

    State state_start{person_start, box_start};
    // TODO(jingyue): replace unordered_set with vector<bool> for performance.
    unordered_set<State> visited_states;
    visited_states.insert(state_start);
    // TODO(jingyue): use an array deque instead for performance.
    queue<State> q;
    q.push(state_start);

    // Returns true if we indeed enqueued.
    auto EnqueueIfNotVisited = [&q, &visited_states](const State& state) {
      if (visited_states.count(state) > 0) {
        return false;
      }
      visited_states.insert(state);
      q.push(state);
      return true;
    };

    vector<pair<Position, int>> pushable_boxes;
    pushable_boxes.reserve(grid.rows * grid.cols * 4);

    int step = 0;
    while (!q.empty()) {
      // Move the person without pushing the box.
      pushable_boxes.clear();
      while (!q.empty()) {
        const State state = q.front();
        q.pop();
        const Position& person = state.person;
        for (int dir = 0; dir < 4; dir++) {
          Position neighbor = grid.NeighborOf(person, dir);
          if (!neighbor.Valid() || !grid.IsEmpty(neighbor)) {
            continue;
          }
          if (neighbor == state.box) {
            // We'll handle box pushing in the next step. Cache all pushable
            // boxes so we don't have to compute them again. Because we deduped
            // with visited_states, pushable_boxes can't contain duplicates.
            pushable_boxes.push_back({neighbor, dir});
            continue;
          }

          EnqueueIfNotVisited({neighbor, state.box});
        }
      }

      // Push the box.
      for (const auto& [box, dir] : pushable_boxes) {
        Position new_box = grid.NeighborOf(box, dir);
        if (!new_box.Valid() || !grid.IsEmpty(new_box)) {
          continue;
        }

        if (EnqueueIfNotVisited({box, new_box})) {
          if (new_box == box_end) {
            return step + 1;
          }
        }
      }

      step++;
    }

    return -1;
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(s.minPushBox({{'#', '#', '#', '#', '#', '#'},
                          {'#', 'T', '#', '#', '#', '#'},
                          {'#', '.', '.', 'B', '.', '#'},
                          {'#', '.', '#', '#', '.', '#'},
                          {'#', '.', '.', '.', 'S', '#'},
                          {'#', '#', '#', '#', '#', '#'}}),
            3);
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(s.minPushBox({{'#', '#', '#', '#', '#', '#'},
                          {'#', 'T', '#', '#', '#', '#'},
                          {'#', '.', '.', 'B', '.', '#'},
                          {'#', '#', '#', '#', '.', '#'},
                          {'#', '.', '.', '.', 'S', '#'},
                          {'#', '#', '#', '#', '#', '#'}}),
            -1);
}

TEST(SolutionTest, testSample3) {
  Solution s;
  EXPECT_EQ(s.minPushBox({{'#', '#', '#', '#', '#', '#'},
                          {'#', 'T', '.', '.', '#', '#'},
                          {'#', '.', '#', 'B', '.', '#'},
                          {'#', '.', '.', '.', '.', '#'},
                          {'#', '.', '.', '.', 'S', '#'},
                          {'#', '#', '#', '#', '#', '#'}}),
            5);
}