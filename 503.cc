#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> nextGreaterElements(const vector<int>& a) {
    const int n = a.size();

    vector<int> next_greater(n, -1);

    // Stores the elements that don't yet have a next greater.
    vector<pair<int, int>> stack;
    stack.reserve(n * 2);
    for (int j = 0; j < n * 2; j++) {
      const int i = j % n;
      const int value = a[i];
      while (!stack.empty() && stack.back().second < value) {
        next_greater[stack.back().first] = value;
        stack.pop_back();
      }
      stack.push_back(make_pair(i, value));
    }

    return next_greater;
  }
};
