#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class BFS {
 public:
  BFS(const vector<string>& words) : words_(words) {
    int n = words.size();
    for (int x = 0; x < n; x++) {
      string pattern = words[x];
      for (size_t i = 0, e = words[x].length(); i != e; ++i) {
        pattern[i] = '*';
        pattern_words_[pattern].push_back(x);
        pattern[i] = words[x][i];
      }
    }
  }

  int search(const string& begin, const string& end) {
    int n = words_.size();
    queue<int> q;
    vector<int> steps(n, -1);

    for (int y : FindNeighbors(begin)) {
      q.push(y);
      steps[y] = 2;
    }

    while (!q.empty()) {
      int x = q.front();
      q.pop();
      if (words_[x] == end) {
        return steps[x];
      }
      for (int y : FindNeighbors(words_[x])) {
        if (steps[y] == -1) {
          q.push(y);
          steps[y] = steps[x] + 1;
        }
      }
    }
    return 0;
  }

 private:
  unordered_set<int> FindNeighbors(const string& word) {
    unordered_set<int> neighbors;
    string pattern = word;
    for (size_t i = 0, e = pattern.length(); i != e; i++) {
      pattern[i] = '*';
      auto iter = pattern_words_.find(pattern);
      if (iter != pattern_words_.end()) {
        neighbors.insert(iter->second.begin(), iter->second.end());
      }
      pattern[i] = word[i];
    }
    return neighbors;
  }

  vector<string> words_;
  unordered_map<string, vector<int>> pattern_words_;
};

class Solution {
 public:
  int ladderLength(const string& begin, const string& end,
                   const vector<string>& words) {
    BFS bfs(words);
    return bfs.search(begin, end);
  }
};

TEST(WordLadderTest, testExists) {
  EXPECT_EQ(5, Solution().ladderLength(
                   "hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}));
}

TEST(WordLadderTest, testNotExists) {
  EXPECT_EQ(0, Solution().ladderLength("hit", "cog",
                                       {"hot", "dot", "dog", "lot", "log"}));
}
