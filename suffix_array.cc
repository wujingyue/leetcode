#include "suffix_array.h"

#include <algorithm>
#include <climits>
#include <utility>

using namespace std;

struct Suffix {
  int index;
  int first;
  int second;

  bool operator<(const Suffix& other) const {
    return make_pair(first, second) < make_pair(other.first, other.second);
  }
};

SuffixArray::SuffixArray(const vector<int>& a) : rank_(a.size()) {
  const int n = a.size();
  vector<Suffix> suffixes(n);
  for (int i = 0; i < n; i++) {
    suffixes[i].index = i;
    suffixes[i].first = a[i];
    suffixes[i].second = (i + 1 < n ? a[i + 1] : INT_MIN);
  }
  // We cannot use bucket sort here in general because the range of a[i] is
  // unclear.
  sort(suffixes.begin(), suffixes.end());

  for (int step = 2;; step *= 2) {
    // `step` is the length of the substring captured by suffixes[i].first and
    // suffixes[i].second.
    //
    // Update rank_.
    for (int i = 0; i < n; i++) {
      rank_[suffixes[i].index] = i;
    }
    // Update first.
    int prev_first = suffixes[0].first;
    suffixes[0].first = 0;
    for (int i = 1; i < n; i++) {
      const bool same = (make_pair(prev_first, suffixes[i - 1].second) ==
                         make_pair(suffixes[i].first, suffixes[i].second));
      prev_first = suffixes[i].first;
      suffixes[i].first = suffixes[i - 1].first + !same;
    }
    if (suffixes[n - 1].first == n - 1) {
      break;
    }
    // Update second.
    for (int i = 0; i < n; i++) {
      const int second_index = suffixes[i].index + step;
      suffixes[i].second =
          (second_index < n ? suffixes[rank_[second_index]].first : -1);
    }

    // Sort.
    // TODO(jingyue): use bucket sort because the range of `suffixes[i].first`
    // and `suffixes[i].second` are bounded to [-1, n - 1].
    sort(suffixes.begin(), suffixes.end());
  }
}

int SuffixArray::GetRank(const int i) const { return rank_[i]; }
