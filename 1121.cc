#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Solution {
 public:
  bool canDivideIntoSubsequences(const vector<int>& nums, const int k) {
    const int n = nums.size();

    priority_queue<int> frequencies;
    int i = 0;
    while (i < n) {
      int j = i + 1;
      while (j < n && nums[j] == nums[i]) {
        j++;
      }
      frequencies.push(j - i);
      i = j;
    }

    while ((int)frequencies.size() >= k) {
      const int current_max = frequencies.top();
      frequencies.pop();
      int count = 1;
      while (count < k && frequencies.top() == current_max) {
        frequencies.pop();
        count++;
      }
      if (count >= k) {
        return true;
      }

      vector<int> new_frequencies(count, current_max - 1);
      while (count < k) {
        const int frequency = frequencies.top();
        frequencies.pop();
        new_frequencies.push_back(frequency - 1);
        count++;
      }
      for (const int frequency : new_frequencies) {
        if (frequency > 0) {
          frequencies.push(frequency);
        }
      }
    }

    return false;
  }
};

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(s.canDivideIntoSubsequences({1, 2, 2, 3, 3, 4, 4}, 3), true);
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(s.canDivideIntoSubsequences({5, 6, 6, 7, 8}, 3), false);
}