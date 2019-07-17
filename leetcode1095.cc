#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class MountainArray {
 public:
  MountainArray(vector<int> data): data_(std::move(data)) {}
  int get(int index) { return data_[index]; }
  int length() { return data_.size(); }

 private:
  vector<int> data_;
};

class Solution {
 public:
  int findInMountainArray(int target, MountainArray& a) {
    int peak = findPeak(a);
    int index = findInAscendingArray(target, 0, peak, a);
    if (index != -1) {
      return index;
    }
    return findInDescendingArray(target, peak, a.length() - 1, a);
  }

 private:
  int findPeak(MountainArray& a) {
    int i = 0;
    int j = a.length() - 1;
    while (i + 3 < j) {
      int k1 = i + (j - i) / 3;
      int k2 = i + (j - i) / 3 * 2;
      int v1 = a.get(k1);
      int v2 = a.get(k2);
      if (v1 <= v2) {
        i = k1 + 1;
      }
      if (v1 >= v2) {
        j = k2 - 1;
      }
    }
    assert(i <= j);
    int peak = i;
    int v_peak = a.get(i);
    for (int k = i + 1; k <= j; ++k) {
      int v = a.get(k);
      if (v > v_peak) {
        v_peak = v;
        peak = k;
      }
    }
    return peak;
  }

  int findInAscendingArray(int target, int left, int right, MountainArray& a) {
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int v_mid = a.get(mid);
      if (target == v_mid) {
        return mid;
      }
      if (target < v_mid) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return -1;
  }

  int findInDescendingArray(int target, int left, int right, MountainArray& a) {
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int v_mid = a.get(mid);
      if (target == v_mid) {
        return mid;
      }
      if (target > v_mid) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return -1;
  }
};

int main() {
  Solution s;

  MountainArray a({1, 2, 3, 4, 5, 3, 1});
  cout << s.findInMountainArray(3, a) << endl;

  a = vector<int>({0, 1, 2, 4, 2, 1});
  cout << s.findInMountainArray(3, a) << endl;
}
