#include <climits>
#include <string>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  string minWindow(const string& s, const string& t) {
    const int n = s.length();

    vector<int> t_freqs(128, 0);
    int num_letters_in_t = 0;
    for (char c : t) {
      int& t_freq = t_freqs[c];
      t_freq++;
      if (t_freq == 1) {
        num_letters_in_t++;
      }
    }

    int min_length = INT_MAX;
    int min_left = -1;
    int min_right = -1;

    int right = 0;
    vector<int> s_freqs(128, 0);
    int num_includes = 0;
    for (int left = 0; left < n; left++) {
      while (right < n && num_includes < num_letters_in_t) {
        const char c_add = s[right];
        const int t_freq = t_freqs[c_add];
        if (t_freq > 0) {
          int& s_freq = s_freqs[c_add];
          s_freq++;
          if (s_freq == t_freq) {
            num_includes++;
          }
        }
        right++;
      }
      if (num_includes == num_letters_in_t) {
        if (right - left < min_length) {
          min_length = right - left;
          min_left = left;
          min_right = right;
        }
      }
      const char c_remove = s[left];
      const int t_freq = t_freqs[c_remove];
      if (t_freq > 0) {
        int& s_freq = s_freqs[c_remove];
        if (s_freq == t_freq) {
          num_includes--;
        }
        s_freq--;
      }
    }

    if (min_length == INT_MAX) {
      return "";
    }
    return s.substr(min_left, min_right - min_left);
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ("BANC", s.minWindow("ADOBECODEBANC", "ABC"));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ("a", s.minWindow("a", "a"));
}

TEST(SolutionTest, testSample3) {
  Solution s;
  EXPECT_EQ("", s.minWindow("a", "aa"));
}
