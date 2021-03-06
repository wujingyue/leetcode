#include <climits>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int m = matrix.size();
    int n = matrix[0].size();
    // The problem doesn't describe what to return if we can't find any
    // submatrix whose sum is no larger than k.
    int answer = INT_MIN;
    // Assumes n is much smaller than m.
    vector<int> row_sum(m);
    for (int j1 = 0; j1 < n; j1++) {
      fill(row_sum.begin(), row_sum.end(), 0);
      for (int j2 = j1; j2 < n; j2++) {
        // Find the largest subarray sum that is no larger than k. This is
        // equivalent to finding the largest prefix_sum[i2]-prefix_sum[i1-1]
        // that is at most k.
        int prefix_sum = 0;
        set<int> previous_prefix_sums;
        previous_prefix_sums.insert(prefix_sum);
        for (int i2 = 0; i2 < m; i2++) {
          row_sum[i2] += matrix[i2][j2];
          prefix_sum += row_sum[i2];
          // Find the smallest previous prefix sum that is no smaller than
          // prefix_sum[i2]-k.
          auto iter = previous_prefix_sums.lower_bound(prefix_sum - k);
          if (iter != previous_prefix_sums.end()) {
            answer = max(answer, prefix_sum - *iter);
            if (answer == k) {
              return answer;
            }
          }
          previous_prefix_sums.insert(prefix_sum);
        }
      }
    }
    return answer;
  }
};

int main() {
  Solution s;
  vector<vector<int>> matrix;
  matrix.push_back({1, 0, 1});
  matrix.push_back({0, -2, 3});
  cout << s.maxSumSubmatrix(matrix, 2) << endl;

  matrix.clear();
  matrix.push_back({2, 2, -1});
  cout << s.maxSumSubmatrix(matrix, 0) << endl;
}