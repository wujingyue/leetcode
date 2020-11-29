#include <vector>

#include "gtest/gtest.h"

#include "suffix_array.h"

using namespace std;

class Solution {
 public:
  vector<int> maxNumber(const vector<int>& a, const vector<int>& b,
                        const int k) {
    vector<int> answer;
    const int m = a.size();
    const int n = b.size();
    for (int i = 0; i <= k; i++) {
      if (i > m || k - i > n) {
        continue;
      }
      vector<int> a2 = MaxNumber(a, i);
      vector<int> b2 = MaxNumber(b, k - i);
      vector<int> c = Merge(a2, b2);
      if (c > answer) {
        answer = c;
      }
    }
    return answer;
  }

 private:
  vector<int> MaxNumber(const vector<int>& a, const int k) {
    vector<int> max_number;
    for (int i = 0, n = a.size(); i < n; i++) {
      while (!max_number.empty() && max_number.back() < a[i] &&
             (int)max_number.size() - 1 + (n - i) >= k) {
        max_number.pop_back();
      }
      if ((int)max_number.size() < k) {
        max_number.push_back(a[i]);
      }
    }
    return max_number;
  }

  vector<int> Merge(const vector<int>& a, const vector<int>& b) {
    vector<int> s;
    s.reserve(a.size() + 1 + b.size());
    copy(a.begin(), a.end(), back_inserter(s));
    s.push_back(-1);
    copy(b.begin(), b.end(), back_inserter(s));
    SuffixArray sa(s);

    vector<int> c;
    c.reserve(a.size() + b.size());
    size_t i = 0;
    size_t j = 0;
    while (i < a.size() || j < b.size()) {
      if (j == b.size() || sa.GetRank(i) > sa.GetRank(a.size() + 1 + j)) {
        c.push_back(a[i]);
        i++;
      } else {
        c.push_back(b[j]);
        j++;
      }
    }
    return c;
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(vector<int>({9, 8, 6, 5, 3}),
            s.maxNumber({3, 4, 6, 5}, {9, 1, 2, 5, 8, 3}, 5));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(vector<int>({6, 7, 6, 0, 4}), s.maxNumber({6, 7}, {6, 0, 4}, 5));
}

TEST(SolutionTest, testSample3) {
  Solution s;
  EXPECT_EQ(vector<int>({9, 8, 9}), s.maxNumber({3, 9}, {8, 9}, 3));
}
