#include <bitset>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
  public:
  string removeDuplicateLetters(const string& a) {
    int n = a.length();
    bitset<26> bs;
    vector<bitset<26>> s(n);
    for (int i = n - 1; i >= 0; i--) {
      bs.set(a[i] - 'a');
      s[i] = bs;
    }

    string result;
    int i = 0;
    while (bs.any()) {
      int j = i;
      int arg_min = -1;
      while (j < n && (s[j] & bs) == bs) {
        if (bs.test(a[j] - 'a')) {
          if (arg_min == -1 || a[j] < a[arg_min]) {
            arg_min = j;
          }
        }
        j++;
      }
      result += a[arg_min];
      bs.flip(a[arg_min] - 'a');
      i = arg_min + 1;
    }
    return result;
  }
};

class SolutionTest : public testing::Test {
  protected:
  Solution s_;
};

TEST_F(SolutionTest, sample1) {
  EXPECT_EQ("abc", s_.removeDuplicateLetters("bcabc"));
}

TEST_F(SolutionTest, sample2) {
  EXPECT_EQ("acdb", s_.removeDuplicateLetters("cbacdcbc"));
}

TEST_F(SolutionTest, customized) {
  EXPECT_EQ("bcad", s_.removeDuplicateLetters("bcabd"));
}