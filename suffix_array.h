#ifndef _SUFFIX_ARRAY_H
#define _SUFFIX_ARRAY_H

#include <vector>

class SuffixArray {
 public:
  explicit SuffixArray(const std::vector<int>& a);
  // TODO(jingyue): explicit SuffixArray(const std::string& a);

  int GetRank(int i) const;

 private:
  std::vector<int> rank_;
};

#endif  // _SUFFIX_ARRAY_H
