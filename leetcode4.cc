#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
    int len = a.size() + b.size();
    if (len % 2 == 0) {
      int smaller = KthInSortedArrays(a, 0, b, 0, len / 2);
      int larger = KthInSortedArrays(a, 0, b, 0, len / 2 + 1);
      return ((double)smaller + larger) / 2;
    } else {
      return KthInSortedArrays(a, 0, b, 0, len / 2 + 1);
    }
  }

 private:
  int KthInSortedArrays(const vector<int>& a, int a_left, const vector<int>& b,
                        int b_left, const int k) {
    if (a_left >= (int)a.size()) {
      return b[b_left + k - 1];
    }
    if (b_left >= (int)b.size()) {
      return a[a_left + k - 1];
    }
    if (k == 1) {
      return min(a[a_left], b[b_left]);
    }

    int a_mid = a_left + k / 2 - 1;
    int b_mid = b_left + k / 2 - 1;
    int a_mid_value = (a_mid < (int)a.size() ? a[a_mid] : INT_MAX);
    int b_mid_value = (b_mid < (int)b.size() ? b[b_mid] : INT_MAX);
    if (a_mid_value <= b_mid_value) {
      return KthInSortedArrays(a, a_mid + 1, b, b_left, k - k / 2);
    } else {
      return KthInSortedArrays(a, a_left, b, b_mid + 1, k - k / 2);
    }
  }
};

int main() {
  Solution solution;
  {
    vector<int> a({1, 3});
    vector<int> b({2});
    cout << solution.findMedianSortedArrays(a, b) << endl;
  }
  {
    vector<int> a({1, 2});
    vector<int> b({3, 4});
    cout << solution.findMedianSortedArrays(a, b) << endl;
  }
}
