#include <iostream>
#include <vector>

class Solution {
 public:
  int jump(std::vector<int>& a) {
    int n = a.size();
    int level = 0;
    int first = 0;
    int last = 0;
    while (last < n - 1) {
      int next_last = last;
      for (int i = first; i <= last; i++) {
        next_last = std::max(next_last, i + a[i]);
      }
      if (next_last == last) {
        return -1;
      }
      level++;
      first = last + 1;
      last = next_last;
    }
    return level;
  }
};

int main() {
  Solution sol;
  std::vector<int> a({2, 3, 1, 1, 4});
  std::cout << sol.jump(a) << std::endl;

  a = {3, 2, 1, 0, 4};
  std::cout << sol.jump(a) << std::endl;
}
