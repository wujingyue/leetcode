#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  string getPermutation(int n, int k) {
    vector<int> factorial(n);
    factorial[0] = 1;
    for (int i = 1; i < n; i++) {
      factorial[i] = factorial[i - 1] * i;
    }

    k--;
    string sequence(n, '0');
    vector<bool> used(n);
    for (int i = 0; i < n; i++) {
      const int divisor = factorial[n - 1 - i];
      int count_unused = k / divisor;
      k %= divisor;
      // Find the count_unused-th (0-based) unused digit.
      for (int digit = 0; digit < n; digit++) {
        if (used[digit]) {
          continue;
        }
        if (count_unused == 0) {
          used[digit] = true;
          sequence[i] = '1' + digit;
          break;
        }
        count_unused--;
      }
      assert(sequence[i] != '0');
    }
    return sequence;
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ("213", s.getPermutation(3, 3));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ("2314", s.getPermutation(4, 9));
}

TEST(SolutionTest, testSample3) {
  Solution s;
  EXPECT_EQ("123", s.getPermutation(3, 1));
}
