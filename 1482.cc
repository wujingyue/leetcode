#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class BinarySearchSolution {
 public:
  int minDays(const vector<int>& days, const int m, const int k) {
    int min_day = INT_MAX;
    int max_day = INT_MIN;
    for (const int day : days) {
      min_day = min(min_day, day);
      max_day = max(max_day, day);
    }

    int low = min_day;
    int high = max_day + 1;
    // impossible, impossible, possible, ...
    // Find the first possible.
    while (low < high) {
      int mid = low + (high - low) / 2;
      if (IsPossible(days, m, k, mid)) {
        high = mid;
      } else {
        low = mid + 1;
      }
    }
    if (low == max_day + 1) {
      return -1;
    }
    return low;
  }

 private:
  bool IsPossible(const vector<int>& days, const int m, const int k,
                  const int wait) {
    const int n = days.size();
    int num_segments = 0;
    int i = 0;
    while (true) {
      while (i < n && days[i] > wait) {
        i++;
      }
      if (i >= n) {
        break;
      }

      // days[i] <= wait
      int j = i + 1;
      while (j < n && days[j] <= wait) {
        j++;
      }

      num_segments += (j - i) / k;
      i = j;
    }
    return num_segments >= m;
  }
};

class UnionFindSet {
 public:
  UnionFindSet(const int n) : parent_(n, -1), size_(n, 0) {}

  void Add(int i) {
    parent_[i] = i;
    size_[i] = 1;
  }

  int GetParent(int i) {
    int* p = &parent_[i];
    if (i == *p) {
      return i;
    }
    *p = GetParent(*p);
    return *p;
  }

  int GetSize(int i) {
    if (size_[i] == 0) {
      return 0;
    }
    return size_[GetParent(i)];
  }

  void Union(int i, int j) {
    const int pi = GetParent(i);
    const int pj = GetParent(j);
    assert(pi != pj);
    parent_[pj] = pi;
    size_[pi] += size_[pj];
  };

 private:
  vector<int> parent_;
  vector<int> size_;
};

class UnionFindSolution {
 public:
  int minDays(const vector<int>& days, const int m, const int k) {
    const int n = days.size();
    vector<pair<int, int>> value_index;
    value_index.reserve(n);
    for (int i = 0; i < n; i++) {
      value_index.push_back(make_pair(days[i], i));
    }
    sort(value_index.begin(), value_index.end());

    UnionFindSet ufs(n);
    int num_segments = 0;
    for (const pair<int, int>& entry : value_index) {
      const int value = entry.first;
      const int i = entry.second;

      ufs.Add(i);

      int left_size = 0;
      if (i - 1 >= 0) {
        left_size = ufs.GetSize(i - 1);
        if (left_size > 0) {
          ufs.Union(i, i - 1);
        }
      }
      int right_size = 0;
      if (i + 1 < n) {
        right_size = ufs.GetSize(i + 1);
        if (right_size > 0) {
          ufs.Union(i, i + 1);
        }
      }

      num_segments -= left_size / k;
      num_segments -= right_size / k;
      num_segments += (left_size + 1 + right_size) / k;
      if (num_segments >= m) {
        return value;
      }
    }
    return -1;
  }
};

using Solution = UnionFindSolution;

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(3, s.minDays({1, 10, 3, 10, 2}, 3, 1));
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(-1, s.minDays({1, 10, 3, 10, 2}, 3, 2));
}

TEST(SolutionTest, testSample3) {
  Solution s;
  EXPECT_EQ(12, s.minDays({7, 7, 7, 7, 12, 7, 7}, 2, 3));
}

TEST(SolutionTest, testSample4) {
  Solution s;
  EXPECT_EQ(1000000000, s.minDays({1000000000, 1000000000}, 1, 1));
}

TEST(SolutionTest, testSample5) {
  Solution s;
  EXPECT_EQ(9, s.minDays({1, 10, 2, 9, 3, 8, 4, 7, 5, 6}, 4, 2));
}
