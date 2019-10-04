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
  BFS(const vector<string>& words, bool bidirectional)
      : words_(words), bidirectional_(bidirectional) {
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

  int Search(const string& begin, const string& end) {
    if (bidirectional_) {
      return BidirectionalSearch(begin, end);
    } else {
      return UnidirectionalSearch(begin, end);
    }
  }

 private:
  int UnidirectionalSearch(const string& begin, const string& end) {
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

  int BidirectionalSearch(const string& begin, const string& end) {
    int n = words_.size();
    queue<int> q_forward;
    queue<int> q_backward;
    vector<int> steps_forward(n, -1);
    vector<int> steps_backward(n, -1);

    int end_id = find(words_.begin(), words_.end(), end) - words_.begin();
    if (end_id == n) {
      return 0;
    }

    q_backward.push(end_id);
    steps_backward[end_id] = 0;

    for (int y : FindNeighbors(begin)) {
      q_forward.push(y);
      steps_forward[y] = 1;
      if (steps_backward[y] >= 0) {
        return steps_forward[y] + steps_backward[y] + 1;
      }
    }

    while (!q_forward.empty() && !q_backward.empty()) {
      int step = ExpandOneLevel(&q_backward, &steps_backward, steps_forward);
      if (step > 0) {
        return step;
      }
      step = ExpandOneLevel(&q_forward, &steps_forward, steps_backward);
      if (step > 0) {
        return step;
      }
    }
    return 0;
  }

  int ExpandOneLevel(queue<int>* q, vector<int>* steps,
                     const vector<int>& other_steps) {
    int q_size = q->size();
    for (int i = 0; i < q_size; i++) {
      int x = q->front();
      q->pop();
      for (int y : FindNeighbors(words_[x])) {
        if ((*steps)[y] == -1) {
          q->push(y);
          (*steps)[y] = (*steps)[x] + 1;
          if (other_steps[y] >= 0) {
            return (*steps)[y] + other_steps[y] + 1;
          }
        }
      }
    }
    return 0;
  }

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
  bool bidirectional_;
  unordered_map<string, vector<int>> pattern_words_;
};

class Solution {
 public:
  int ladderLength(const string& begin, const string& end,
                   const vector<string>& words) {
    BFS bfs(words, /*bidirectional=*/true);
    return bfs.Search(begin, end);
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
