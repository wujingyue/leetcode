#include <iostream>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int countVowelPermutation(int n) {
    // m[i][j] represents the number of sequences of length i that end at vowel
    // j. 0 - 'a', 1 - 'e', 2 - 'i', 3 - 'o', 4 - 'u'.
    vector<vector<int>> m(n + 1, vector<int>(5));
    for (int j = 0; j < 5; j++) {
      m[1][j] = 1;
    }
    constexpr bool kFollowedBy[][5] = {// a may only be followed by e.
                                       {false, true, false, false, false},
                                       // e may only be followed by a or i.
                                       {true, false, true, false, false},
                                       // i may not be followed by i.
                                       {true, true, false, true, true},
                                       // o may be followed by i or u.
                                       {false, false, true, false, true},
                                       // u may be followed by a.
                                       {true, false, false, false, false}};
    constexpr int kModulo = 1000000007;
    for (int i = 1; i < n; i++) {
      for (int j = 0; j < 5; j++) {
        for (int j2 = 0; j2 < 5; j2++) {
          if (kFollowedBy[j][j2]) {
            m[i + 1][j2] += m[i][j];
            m[i + 1][j2] %= kModulo;
          }
        }
      }
    }

    int sum = 0;
    for (int j = 0; j < 5; j++) {
      sum = (sum + m[n][j]) % kModulo;
    }
    return sum;
  }
};

class SolutionTest : public testing::Test {
 protected:
  Solution s_;
};

TEST_F(SolutionTest, test1) { EXPECT_EQ(5, s_.countVowelPermutation(1)); }

TEST_F(SolutionTest, test2) { EXPECT_EQ(10, s_.countVowelPermutation(2)); }

TEST_F(SolutionTest, test5) { EXPECT_EQ(68, s_.countVowelPermutation(5)); }