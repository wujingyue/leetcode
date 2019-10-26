#include <algorithm>
#include <iostream>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

struct Job {
  Job(int s, int e, int p) : start(s), end(e), profit(p) {}
  bool operator<(const Job& other) const { return end < other.end; }

  int start;
  int end;
  int profit;
};

class Solution {
 public:
  int jobScheduling(const vector<int>& start_times,
                    const vector<int>& end_times, const vector<int>& profit) {
    vector<int> times(start_times);
    times.insert(times.end(), end_times.begin(), end_times.end());
    sort(times.begin(), times.end());
    times.erase(unique(times.begin(), times.end()), times.end());

    int n = start_times.size();
    vector<Job> jobs;
    jobs.reserve(n);
    for (int i = 0; i < n; i++) {
      jobs.push_back(Job(
          lower_bound(times.begin(), times.end(), start_times[i]) -
              times.begin(),
          lower_bound(times.begin(), times.end(), end_times[i]) - times.begin(),
          profit[i]));
    }
    sort(jobs.begin(), jobs.end());

    vector<int> m(times.size());
    int i = 0;
    for (int j = 0, e = times.size(); j < e; j++) {
      if (j > 0) {
        m[j] = m[j - 1];
      }
      while (i < n && jobs[i].end == j) {
        m[j] = max(m[j], m[jobs[i].start] + jobs[i].profit);
        i++;
      }
    }
    return m[times.size() - 1];
  }
};

class SolutionTest : public ::testing::Test {
 protected:
  Solution s_;
};

TEST_F(SolutionTest, testSample1) {
  EXPECT_EQ(150, s_.jobScheduling({1, 2, 3, 4, 6}, {3, 5, 10, 6, 9},
                                  {20, 20, 100, 70, 60}));
}

TEST_F(SolutionTest, testSample2) {
  EXPECT_EQ(6, s_.jobScheduling({1, 1, 1}, {2, 3, 4}, {5, 6, 4}));
}
