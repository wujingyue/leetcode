#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  vector<int> findBall(const vector<vector<int>>& a) {
    const int r = a.size();
    const int c = a[0].size();
    vector<int> final_columns(c);
    for (int j = 0; j < c; ++j) {
      int column = j;
      for (int i = 0; i < r; i++) {
        if (a[i][column] == 1) {
          if (column == c - 1 || a[i][column + 1] == -1) {
            column = -1;
            break;
          }
          column++;
        } else {
          if (column == 0 || a[i][column - 1] == 1) {
            column = -1;
            break;
          }
          column--;
        }
      }
      final_columns[j] = column;
    }
    return final_columns;
  }
};

TEST(SolutionTest, testSample) {
  Solution s;
  EXPECT_EQ(vector<int>({1, -1, -1, -1, -1}),
            s.findBall({{1, 1, 1, -1, -1},
                        {1, 1, 1, -1, -1},
                        {-1, -1, -1, 1, 1},
                        {1, 1, 1, 1, -1},
                        {-1, -1, -1, -1, -1}}));
}
