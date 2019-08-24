#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int ladderLength(string begin, string end, vector<string>& words) {
    unordered_map<string, vector<int>> pattern_words;
    int n = words.size();
    for (int x = 0; x < n; x++) {
      string pattern = words[x];
      for (size_t i = 0, e = words[x].length(); i != e; ++i) {
        pattern[i] = '*';
        pattern_words[pattern].push_back(x);
        pattern[i] = words[x][i];
      }
    }

    queue<int> q;
    vector<int> steps(n, -1);
    for (int y : FindNeighbors(pattern_words, begin)) {
      q.push(y);
      steps[y] = 2;
    }
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      if (words[x] == end) {
        return steps[x];
      }
      for (int y : FindNeighbors(pattern_words, words[x])) {
        if (steps[y] == -1) {
          q.push(y);
          steps[y] = steps[x] + 1;
        }
      }
    }
    return 0;
  }

  vector<int> FindNeighbors(const unordered_map<string, vector<int>>& pattern_words,
                            const string& word) {
    vector<int> neighbors;
    string pattern = word;
    for (size_t i = 0, e = pattern.length(); i != e; i++) {
      pattern[i] = '*';
      auto iter = pattern_words.find(pattern);
      if (iter != pattern_words.end()) {
        neighbors.insert(neighbors.end(), iter->second.begin(), iter->second.end());
      }
      pattern[i] = word[i];
    }
    return neighbors;
  }
};

int main() {
  Solution s;
  vector<string> words({"hot", "dot", "dog", "lot", "log", "cog"});
  cout << s.ladderLength("hit", "cog", words) << endl;

  words = {"hot", "dot", "dog", "lot", "log"};
  cout << s.ladderLength("hit", "cog", words) << endl;
}