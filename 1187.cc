#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int makeArrayIncreasing(vector<int> a, vector<int> b) {
    vector<int> nums(a);
    nums.insert(nums.end(), b.begin(), b.end());
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    int n = a.size();
    for (int i = 0; i < n; i++) {
      a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin();
    }
    for (int i = 0; i < b.size(); i++) {
      b[i] = lower_bound(nums.begin(), nums.end(), b[i]) - nums.begin();
    }
    sort(b.begin(), b.end());

    vector<int> next_in_b(nums.size());
    for (int j = 0; j < nums.size(); j++) {
      auto next = upper_bound(b.begin(), b.end(), j);
      next_in_b[j] = (next == b.end() ? -1 : *next);
    }

    // m[i][j] represents the fewest replacements to make a[0..i] increasing and
    // a[i] equal to j. We only need to store one row of m[i][j] at any time.
    vector<int> m(nums.size(), INT_MAX);
    m[a[0]] = 0;
    if (!b.empty()) {
      UpdateIfGreaterThan(&m[b[0]], 1);
    }
    for (int i = 0; i + 1 < n; i++) {
      for (int j = (int)nums.size() - 1; j >= 0; j--) {
        if (m[j] == INT_MAX) {
          continue;
        }
        if (j < a[i + 1]) {
          UpdateIfGreaterThan(&m[a[i + 1]], m[j]);
        }
        int next_j = next_in_b[j];
        if (next_j >= 0) {
          UpdateIfGreaterThan(&m[next_j], m[j] + 1);
        }
        // After this iteration, m[j] means m[i+1][j] instead of m[i][j] so set
        // it to INT_MAX.
        m[j] = INT_MAX;
      }
    }
    int answer = INT_MAX;
    for (int j = 0; j < nums.size(); j++) {
      UpdateIfGreaterThan(&answer, m[j]);
    }
    return (answer == INT_MAX ? -1 : answer);
  }

 private:
  void UpdateIfGreaterThan(int* a, int b) {
    if (*a > b) {
      *a = b;
    }
  }
};

int main() {
  Solution s;
  cout << s.makeArrayIncreasing({1, 5, 3, 6, 7}, {1, 3, 2, 4}) << endl;
  cout << s.makeArrayIncreasing({1, 5, 3, 6, 7}, {4, 3, 1}) << endl;
  cout << s.makeArrayIncreasing({1, 5, 3, 6, 7}, {1, 6, 3, 3}) << endl;
  cout << s.makeArrayIncreasing({1, 5, 3, 6, 7}, {}) << endl;
}
