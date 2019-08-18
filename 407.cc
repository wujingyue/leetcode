#include <climits>
#include <iostream>
#include <queue>
#include <vector>

struct LocationDistance {
  int x;
  int y;
  int d;

  LocationDistance(int x2, int y2, int dis): x(x2), y(y2), d(dis) {}

  bool operator<(const LocationDistance& other) const {
    return d > other.d;
  }
};

class Solution {
 public:
  int trapRainWater(std::vector<std::vector<int>>& h) {
    int m = h.size();
    if (m == 0) {
      return 0;
    }
    int n = h[0].size();
    if (n == 0) {
      return 0;
    }

    std::vector<std::vector<int>> d(m, std::vector<int>(n, INT_MAX));
    std::priority_queue<LocationDistance> q;

    auto enqueue = [&d, &q](int x, int y, int dis) {
      d[x][y] = dis;
      q.push(LocationDistance(x, y, dis));
    };

    for (int x = 0; x < m; ++x) {
      enqueue(x, 0, h[x][0]);
      enqueue(x, n - 1, h[x][n - 1]);
    }
    for (int y = 1; y < n - 1; ++y) {
      enqueue(0, y, h[0][y]);
      enqueue(m - 1, y, h[m - 1][y]);
    }

    while (!q.empty()) {
      int x = q.top().x;
      int y = q.top().y;
      int dis = q.top().d;
      q.pop();
      if (d[x][y] < dis) {
        continue;
      }
      for (int dir = 0; dir < 4; ++dir) {
        int x2 = x + kDx[dir];
        int y2 = y + kDy[dir];
        if (x2 >= 0 && x2 < m && y2 >= 0 && y2 < n) {
          int dis2 = std::max(dis, h[x2][y2]);
          if (dis2 < d[x2][y2]) {
            enqueue(x2, y2, dis2);
          }
        }
      }
    }

    int water = 0;
    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < n; ++y) {
        water += d[x][y] - h[x][y];
      }
    }
    return water;
  }

 private:
  const int kDx[4] = {-1, 0, 1, 0};
  const int kDy[4] = {0, 1, 0, -1};
};

int main() {
  std::vector<std::vector<int>> h;
  h.push_back({1, 4, 3, 1, 3, 2});
  h.push_back({3, 2, 1, 3, 2, 4});
  h.push_back({2, 3, 3, 2, 3, 1});

  Solution s;
  std::cout << s.trapRainWater(h) << std::endl;
}
