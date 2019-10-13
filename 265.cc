#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

class Solution {
 public:
  int minCostII(std::vector<std::vector<int>>& costs) {
    int m = costs.size();
    if (m == 0) {
      return 0;
    }
    int n = costs[0].size();
    assert(n > 0);
    if (n == 1) {
      assert(m == 1);
      return costs[0][0];
    }

    std::vector<int> dp(n, 0);
    for (int i = 0; i < m; ++i) {
      int min = dp[0];
      int arg_min = 0;
      int second_min = INT_MAX;
      for (int j = 1; j < n; ++j) {
        if (dp[j] < min) {
          second_min = min;
          min = dp[j];
          arg_min = j;
        } else if (dp[j] < second_min) {
          second_min = dp[j];
        }
      }
      for (int j = 0; j < n; ++j) {
        if (j != arg_min) {
          dp[j] = min + costs[i][j];
        } else {
          dp[j] = second_min + costs[i][j];
        }
      }
    }
    return *std::min_element(dp.begin(), dp.end());
  }
};

int main() {
  std::vector<std::vector<int>> costs;
  costs.push_back({1, 5, 3});
  costs.push_back({2, 9, 4});

  Solution s;
  std::cout << s.minCostII(costs) << std::endl;
}
