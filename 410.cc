#include <climits>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
 public:
  int splitArray(const vector<int>& nums, const int m) {
    int sum = 0;
    for (int x : nums) {
      if (sum < INT_MAX - x) {
        sum += x;
      } else {
        sum = INT_MAX;
        break;
      }
    }

    int low = 0;
    int high = sum;
    while (low < high) {
      int mid = low + (high - low) / 2;
      if (NumSegments(nums, mid) <= m) {
        high = mid;
      } else {
        low = mid + 1;
      }
    }
    return low;
  }

 private:
  int NumSegments(const vector<int>& nums, const int max_sum) {
    int n = nums.size();
    int num_segments = 0;
    int i = 0;
    while (i < n) {
      int j = i;
      int sum = 0;  // sum = Sum(a[i..j-1])
      while (j < n && sum <= max_sum - nums[j]) {
        sum += nums[j];
        j++;
      }
      if (j == i) {
        return INT_MAX;
      }
      i = j;
      num_segments++;
    }
    return num_segments;
  }
};