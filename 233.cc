#include <iostream>

class Solution {
 public:
  int countDigitOne(int n) {
    int multiplier = 1;
    int count = 0;
    int m = n;
    while (m > 0) {
      count += m / 10 * multiplier;
      if (m % 10 > 1) {
        count += multiplier;
      } else if (m % 10 == 1) {
        count += n % multiplier + 1;
      }
      m /= 10;
      // Avoid multiplier from overflowing.
      if (m == 0) {
        break;
      }
      multiplier *= 10;
    }
    return count;
  }

  int countDigitOneSlow(int n) {
    int count = 0;
    for (int m = 1; m <= n; ++m) {
      int x = m;
      while (x > 0) {
        count += (x % 10 == 1);
        x /= 10;
      }
    }
    return count;
  }
};

int main() {
  Solution solution;
  std::cout << solution.countDigitOne(13) << std::endl;
  std::cout << solution.countDigitOneSlow(13) << std::endl;
  std::cout << solution.countDigitOne(214748) << std::endl;
  std::cout << solution.countDigitOneSlow(214748) << std::endl;
}
