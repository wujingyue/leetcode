#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
 public:
  int validSubarrays(vector<int>& a) {
    int n = a.size();
    int answer = 0;
    stack<int> s;
    for (int i = n - 1; i >= 0; i--) {
      while (!s.empty() && a[i] <= a[s.top()]) {
        s.pop();
      }
      answer += (s.empty() ? n : s.top()) - i;
      s.push(i);
    }
    return answer;
  }
};

int main() {
  Solution s;
  vector<int> a({1, 4, 2, 5, 3});
  cout << s.validSubarrays(a) << endl;
  a = {3, 2, 1};
  cout << s.validSubarrays(a) << endl;
  a = {2, 2, 2};
  cout << s.validSubarrays(a) << endl;
}