#include <iostream>
#include <vector>

class Solution {
 public:
  int maxCoins(std::vector<int>& nums) {
    // m[i][j] =
    //   if i > j then 0
    //   else max(m[i][k-1] + m[k+1][j] + nums[i-1]*nums[k]*nums[j+1])
    int n = nums.size();
    std::vector<std::vector<int>> m(n, std::vector<int>(n));

    auto get_num = [&nums, n](int i) {
      if (i < 0) {
        return 1;
      }
      if (i >= n) {
        return 1;
      }
      return nums[i];
    };

    auto get_m = [&m, n](int i, int j) { return (i > j ? 0 : m[i][j]); };

    for (int i = n - 1; i >= 0; --i) {
      for (int j = i; j < n; ++j) {
        for (int k = i; k <= j; ++k) {
          m[i][j] =
              std::max(m[i][j], get_m(i, k - 1) + get_m(k + 1, j) +
                                    get_num(i - 1) * nums[k] * get_num(j + 1));
        }
      }
    }

    return get_m(0, n - 1);
  }
};

int main() {
  Solution s;
  std::vector<int> nums({3, 1, 5, 8});
  std::cout << s.maxCoins(nums) << std::endl;
}
