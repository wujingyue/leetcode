#include <cassert>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<int> gridIllumination(int n, std::vector<std::vector<int>>& lamps,
                                    std::vector<std::vector<int>>& queries) {
    std::unordered_map<int, int> row_illuminated;
    std::unordered_map<int, int> col_illuminated;
    std::unordered_map<int, int> major_illuminated;
    std::unordered_map<int, int> minor_illuminated;
    std::set<std::pair<int, int>> lamps_on;

    for (int i = 0; i < (int) lamps.size(); i++) {
      int x = lamps[i][0];
      int y = lamps[i][1];
      if (lamps_on.insert( { x, y }).second) {
        row_illuminated[x]++;
        col_illuminated[y]++;
        major_illuminated[x - y]++;
        minor_illuminated[x + y]++;
      }
    }

    std::vector<int> answer;
    for (const std::vector<int>& query : queries) {
      int x = query[0];
      int y = query[1];
      answer.push_back(
          (int) IsIlluminated(x, y, row_illuminated, col_illuminated,
                              major_illuminated, minor_illuminated));
      for (int dir = 0; dir < 9; ++dir) {
        int x2 = x + kDirs[dir][0];
        int y2 = y + kDirs[dir][1];
        std::pair<int, int> lamp(x2, y2);
        if (lamps_on.erase(lamp) > 0) {
          if ((--row_illuminated[x2]) == 0) {
            row_illuminated.erase(x2);
          }
          if ((--col_illuminated[y2]) == 0) {
            col_illuminated.erase(y2);
          }
          if ((--major_illuminated[x2 - y2]) == 0) {
            major_illuminated.erase(x2 - y2);
          }
          if ((--minor_illuminated[x2 + y2]) == 0) {
            minor_illuminated.erase(x2 + y2);
          }
        }
      }
    }
    return answer;
  }

 private:
  static constexpr int kDirs[][2] = { { -1, -1 }, { -1, 0 }, { -1, 1 },
      { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { 0, 0 } };

  bool IsIlluminated(const int x, const int y,
                     const std::unordered_map<int, int>& row_illuminated,
                     const std::unordered_map<int, int>& col_illuminated,
                     const std::unordered_map<int, int>& major_illuminated,
                     const std::unordered_map<int, int>& minor_illuminated) {
    return row_illuminated.count(x) || col_illuminated.count(y)
        || major_illuminated.count(x - y) || minor_illuminated.count(x + y);
  }
};

constexpr int Solution::kDirs[][2];

int main() {
  Solution sol;
  std::vector<std::vector<int>> lamps( { { 0, 0 }, { 4, 4 } });
  std::vector<std::vector<int>> queries( { { 1, 1 }, { 1, 0 } });
  std::vector<int> answer = sol.gridIllumination(5, lamps, queries);
  for (const int state : answer) {
    std::cout << state << std::endl;
  }
}
