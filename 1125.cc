#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void PrintVector(const vector<int>& v) {
  for (const auto& e : v) {
    cout << e << " ";
  }
  cout << endl;
}

class Solution {
 public:
  vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
    int m = req_skills.size();
    int n = people.size();
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      for (const auto& skill : people[i]) {
        int j = find(req_skills.begin(), req_skills.end(), skill) - req_skills.begin();
        assert(j < m);
        a[i] |= (1 << j);
      }
    }

    // dp[i][j] = considering only the first i people, the minimum number of
    // people to cover skill set j.
    vector<vector<int>> dp(n + 1, vector<int>(1 << m, INT_MAX));
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < (1 << m); ++j) {
        if (dp[i][j] == INT_MAX) {
          continue;
        }
        // Option 1: do not pick person i.
        dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
        // Option 2: pick person i.
        int next_j = j | a[i];
        dp[i + 1][next_j] = min(dp[i + 1][next_j], dp[i][j] + 1);
      }
    }

    assert(dp[n][(1 << m) - 1] < INT_MAX);

    vector<int> team;
    {
      int j = (1 << m) - 1;
      for (int i = n; i > 0; --i) {
        if (dp[i - 1][j] == dp[i][j]) {
          // Didn't pick person i-1.
          continue;
        }

        // Picked person i-1.
        team.push_back(i - 1);
        bool found_prev = false;
        for (int prev_j = 0; prev_j < (1 << m); ++prev_j) {
          if ((prev_j | a[i - 1]) == j && dp[i - 1][prev_j] < INT_MAX && dp[i - 1][prev_j] + 1 == dp[i][j]) {
            found_prev = true;
            j = prev_j;
            break;
          }
        }
        assert(found_prev);
      }
    }
    reverse(team.begin(), team.end());
    return team;
  }
};

int main() {
  Solution s;
  vector<string> req_skills = {"java", "nodejs", "reactjs"};
  vector<vector<string>> people = {{"java"}, {"nodejs"}, {"nodejs", "reactjs"}};
  PrintVector(s.smallestSufficientTeam(req_skills, people));

  req_skills = {"algorithms","math","java","reactjs","csharp","aws"};
  people = {{"algorithms","math","java"},{"algorithms","math","reactjs"},{"java","csharp","aws"},{"reactjs","csharp"},{"csharp","math"},{"aws","java"}};
  PrintVector(s.smallestSufficientTeam(req_skills, people));
}
