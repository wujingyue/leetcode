#include <bitset>
#include <iostream>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

constexpr int kModulo = 1000000007;
constexpr int kFollowedBy[][5] = {
    // a may only be followed by e.
    {0, 1, 0, 0, 0},
    // e may only be followed by a or i.
    {1, 0, 1, 0, 0},
    // i may not be followed by i.
    {1, 1, 0, 1, 1},
    // o may be followed by i or u.
    {0, 0, 1, 0, 1},
    // u may be followed by a.
    {1, 0, 0, 0, 0}};

class NaiveDPSolution {
 public:
  int countVowelPermutation(int n) {
    // m[i][j] represents the number of sequences of length i that end at vowel
    // j. 0 - 'a', 1 - 'e', 2 - 'i', 3 - 'o', 4 - 'u'.
    vector<vector<int>> m(n + 1, vector<int>(5));
    for (int j = 0; j < 5; j++) {
      m[1][j] = 1;
    }
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

class SpaceEfficientDPSolution {
 public:
  int countVowelPermutation(int n) {
    vector<int> m(5, 1);
    vector<int> m2(5);
    for (int i = 1; i < n; i++) {
      fill(m2.begin(), m2.end(), 0);
      for (int j = 0; j < 5; j++) {
        for (int j2 = 0; j2 < 5; j2++) {
          if (kFollowedBy[j][j2]) {
            m2[j2] += m[j];
            m2[j2] %= kModulo;
          }
        }
      }
      m.swap(m2);
    }

    int sum = 0;
    for (int j = 0; j < 5; j++) {
      sum = (sum + m[j]) % kModulo;
    }
    return sum;
  }
};

class Solution {
 public:
  int countVowelPermutation(int n) {
    // m = [1,1,1,1,1] * kFollowedBy^(n-1).
    constexpr int kBitWidth = 15;
    bitset<kBitWidth> bs(n - 1);
    int a[5][5];
    memset(a, 0, sizeof(a));
    for (int i = 0; i < 5; i++) {
      a[i][i] = 1;
    }
    for (int i = kBitWidth - 1; i >= 0; i--) {
      MatrixMultiply(a, a);
      if (bs.test(i)) {
        MatrixMultiply(a, kFollowedBy);
      }
    }

    int sum = 0;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        sum = (sum + a[i][j]) % kModulo;
      }
    }
    return sum;
  }

 private:
  void MatrixMultiply(int a[][5], const int b[][5]) {
    int c[5][5];
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        c[i][j] = 0;
        for (int k = 0; k < 5; k++) {
          c[i][j] =
              (c[i][j] + (long long)a[i][k] * b[k][j] % kModulo) % kModulo;
        }
      }
    }
    memcpy(a, c, sizeof(int) * 5 * 5);
  }
};

class SolutionTest : public testing::Test {
 protected:
  Solution s_;
};

TEST_F(SolutionTest, test1) { EXPECT_EQ(5, s_.countVowelPermutation(1)); }

TEST_F(SolutionTest, test2) { EXPECT_EQ(10, s_.countVowelPermutation(2)); }

TEST_F(SolutionTest, test5) { EXPECT_EQ(68, s_.countVowelPermutation(5)); }