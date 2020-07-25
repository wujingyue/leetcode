#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  Solution(): m(kMaxN + 1) {
    m[0] = false;
    for (int i = 1; i <= kMaxN; i++) {
      m[i] = false;
      for (int j = 1; j * j <= i; j++) {
        if (!m[i - j * j]) {
          m[i] = true;
          break;
        }
      }
    }
  }

  bool winnerSquareGame(const int n) {
    return m[n];
  }

 private:
  static constexpr int kMaxN = 100000;
  vector<int> m;
};

constexpr int Solution::kMaxN;

TEST(SolutionTest, testSample) {
  Solution s;
  EXPECT_EQ(true, s.winnerSquareGame(1));
  EXPECT_EQ(false, s.winnerSquareGame(2));
  EXPECT_EQ(true, s.winnerSquareGame(4));
  EXPECT_EQ(false, s.winnerSquareGame(7));
  EXPECT_EQ(false, s.winnerSquareGame(17));
}
