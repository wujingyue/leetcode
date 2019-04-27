#include <iostream>
#include <string>
#include <vector>

constexpr int kNumLetters = 26;

class Solution {
 public:
  std::string findLongestWord(std::string str, std::vector<std::string>& dict) {
    std::vector<std::vector<int>> next_char(str.length(),
                                            std::vector<int>(kNumLetters, -1));
    if (str.length() > 0) {
      int i = (int)str.length() - 1;
      next_char[i][str[i] - 'a'] = i;
      for (i = (int)str.length() - 2; i >= 0; --i) {
        for (int j = 0; j < kNumLetters; ++j) {
          next_char[i][j] = (str[i] == 'a' + j ? i : next_char[i + 1][j]);
        }
      }
    }

    std::string answer;
    for (const auto& word : dict) {
      if (Matches(word, next_char)) {
        if (word.length() > answer.length() ||
            word.length() == answer.length() && word < answer) {
          answer = word;
        }
      }
    }
    return answer;
  }

 private:
  bool Matches(const std::string& word,
               const std::vector<std::vector<int>>& next_char) {
    int n = next_char.size();
    int i = 0;
    for (const char c : word) {
      if (i >= n) {
        return false;
      }
      i = next_char[i][c - 'a'];
      if (i == -1) {
        return false;
      }
      i++;
    }
    return true;
  }
};

int main() {
  Solution sol;

  std::vector<std::string> d({"ale", "apple", "monkey", "plea"});
  std::cout << sol.findLongestWord("abpcplea", d) << std::endl;

  d = {"a", "b", "c"};
  std::cout << sol.findLongestWord("abpcplea", d) << std::endl;

  d = {"a", "b", "c"};
  std::cout << sol.findLongestWord("", d) << std::endl;

  d = {"", "a", "b", "c"};
  std::cout << sol.findLongestWord("", d) << std::endl;
}
