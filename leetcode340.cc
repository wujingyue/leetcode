#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int lengthOfLongestSubstringKDistinct(std::string s, int k) {
    if (s.empty()) {
      return 0;
    }

    if (k == 0) {
      return 0;
    }

    int i = 0;
    int j = 0;
    int max_length = 1;
    std::vector<int> char_count(256);
    char_count[s[i]] = 1;
    int char_count_size = 1;

    int n = s.length();
    while (j < n - 1) {
      char c = s[j + 1];
      if (char_count[c] > 0 || char_count_size < k) {
        if (char_count[c] == 0) {
          char_count_size++;
        }
        char_count[c]++;
        j++;
        max_length = std::max(max_length, j - i + 1);
      } else {
        char_count[s[i]]--;
        if (char_count[s[i]] == 0) {
          char_count_size--;
        }
        i++;
      }
    }
    return max_length;
  }
};

int main() {
  Solution s;
  std::cout << s.lengthOfLongestSubstringKDistinct("eceba", 2) << std::endl;
  std::cout << s.lengthOfLongestSubstringKDistinct("aa", 1) << std::endl;
  std::cout << s.lengthOfLongestSubstringKDistinct("a", 0) << std::endl;
  std::cout << s.lengthOfLongestSubstringKDistinct("aa", 0) << std::endl;
}
