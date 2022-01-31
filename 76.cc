#include <climits>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  string minWindow(const string& s, const string& t) {
    const int n = s.length();

    unordered_map<char, int> t_freq;
    for (char c : t) {
      t_freq[c]++;
    }
    const int num_letters_in_t = t_freq.size();

    int min_length = INT_MAX;
    int min_left = -1;
    int min_right = -1;

    int right = 0;
    unordered_map<char, int> s_freq;
    int num_includes = 0;
    for (int left = 0; left < n; left++) {
      while (right < n && num_includes < num_letters_in_t) {
        const char c_add = s[right];
        if (t_freq.count(c_add)) {
          int& freq = s_freq[c_add];
          freq++;
          if (freq == t_freq.at(c_add)) {
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
      if (t_freq.count(c_remove)) {
        int& freq = s_freq[c_remove];
        if (freq == t_freq.at(c_remove)) {
          num_includes--;
        }
        freq--;
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
