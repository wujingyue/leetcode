#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int ladderLength(string begin, string end, vector<string>& words) {
    unordered_map<string, int> word_id;
    int n = words.size();
    for (int x = 0; x < n; x++) {
      word_id[words[x]] = x;
    }

    if (word_id.count(end) == 0) {
      return 0;
    }
    int v = word_id[end];

    queue<int> q;
    vector<int> steps(n, -1);
    for (int y : FindNeighbors(word_id, begin)) {
      q.push(y);
      steps[y] = 2;
    }
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      if (x == v) {
        return steps[x];
      }
      for (int y : FindNeighbors(word_id, words[x])) {
        if (steps[y] == -1) {
          q.push(y);
          steps[y] = steps[x] + 1;
        }
      }
    }
    return 0;
  }

  vector<int> FindNeighbors(const unordered_map<string, int>& word_id,
                            string word) {
    vector<int> neighbors;
    for (size_t i = 0, e = word.length(); i < e; i++) {
      int orig_c = word[i];
      for (char c = 'a'; c <= 'z'; c++) {
        if (c == orig_c) {
          continue;
        }
        word[i] = c;
        auto iter = word_id.find(word);
        if (iter != word_id.end()) {
          neighbors.push_back(iter->second);
        }
      }
      word[i] = orig_c;
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