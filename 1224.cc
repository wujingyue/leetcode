#include <iostream>
#include <unordered_map>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  int maxEqualFreq(const vector<int>& a) {
    unordered_map<int, int> num_freq;
    unordered_map<int, int> freq_num;
    int n = a.size();
    int max_prefix = 0;
    for (int i = 0; i < n; i++) {
      int x = a[i];
      int old_freq = GetOrZero(num_freq, x);
      int new_freq = old_freq + 1;
      num_freq[x] = new_freq;
      if (old_freq > 0) {
        if ((--freq_num[old_freq]) == 0) {
          freq_num.erase(old_freq);
        }
      }
      freq_num[new_freq]++;
      // Case 1: each number appear exactly once.
      // Case 2: only one number.
      // Case 3: one frequency is one larger than all other frequencies.
      // Case 4: one frequency is one and all others are the same but not one.
      if ((freq_num.size() == 1 && freq_num.begin()->first == 1) ||
          (freq_num.size() == 1 && freq_num.begin()->second == 1) ||
          (freq_num.size() == 2 &&
           ((freq_num.begin()->first == (++freq_num.begin())->first + 1 &&
             freq_num.begin()->second == 1) ||
            ((++freq_num.begin())->first == freq_num.begin()->first + 1 &&
             (++freq_num.begin())->second == 1) ||
            (freq_num.size() == 2 && GetOrZero(freq_num, 1) == 1)))) {
        max_prefix = i + 1;
      }
    }
    return max_prefix;
  }

  int GetOrZero(const unordered_map<int, int>& m, const int key) {
    return m.count(key) ? m.at(key) : 0;
  };
};

class SolutionTest : public ::testing::Test {
 protected:
  Solution s_;
};

TEST_F(SolutionTest, testSample1) {
  EXPECT_EQ(7, s_.maxEqualFreq({2, 2, 1, 1, 5, 3, 3, 5}));
}

TEST_F(SolutionTest, testSample2) {
  EXPECT_EQ(13, s_.maxEqualFreq({1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5}));
}

TEST_F(SolutionTest, testSample3) {
  EXPECT_EQ(5, s_.maxEqualFreq({1, 1, 1, 2, 2, 2}));
}

TEST_F(SolutionTest, testSample4) {
  EXPECT_EQ(8, s_.maxEqualFreq({10, 2, 8, 9, 3, 8, 1, 5, 2, 3, 7, 6}));
}

TEST_F(SolutionTest, testSample5) {
  EXPECT_EQ(2, s_.maxEqualFreq({1, 1}));
}
