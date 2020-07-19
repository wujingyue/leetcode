#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(const vector<int>& a) {
    int prev = a[0];
    int profit = 0;
    for (int i = 1; i < (int)a.size(); i++) {
      profit += max(a[i] - prev, 0);
      prev = a[i];
    }
    return profit;
  }
};
