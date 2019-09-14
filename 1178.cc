#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findNumOfValidWords(const vector<string>& words,
                                  const vector<string>& puzzles) {
    unordered_map<int, int> subset_count;
    for (const string& word : words) {
      int subset = 0;
      for (char c : word) {
        subset |= (1 << (c - 'a'));
      }
      subset_count[subset]++;
    }

    vector<int> result(puzzles.size());
    for (int i = 0; i < puzzles.size(); i++) {
      int num_valid_words = 0;
      const string& puzzle = puzzles[i];
      int mask = 0;
      for (char c : puzzle) {
        mask |= (1 << (c - 'a'));
      }
      int first_char_mask = (1 << (puzzle[0] - 'a'));
      for (int subset = mask; subset > 0; subset = (subset - 1) & mask) {
        if ((subset & first_char_mask) && subset_count.count(subset)) {
          num_valid_words += subset_count.at(subset);
        }
      }
      result[i] = num_valid_words;
    }
    return result;
  }
};

int main() {
  Solution s;
  for (int num_valid_words : s.findNumOfValidWords(
           {"aaaa", "asas", "able", "ability", "actt", "actor", "access"},
           {"aboveyz", "abrodyz", "abslute", "absoryz", "actresz",
            "gaswxyz"})) {
    cout << num_valid_words << endl;
  }
}