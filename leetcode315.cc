#include <cassert>
#include <iostream>
#include <vector>

struct IndexCount {
  IndexCount(int i, int c) : index(i), count(c) {}

  int index;
  int count;
};

class Solution {
 public:
  std::vector<int> countSmaller(std::vector<int>& nums) {
    int n = nums.size();

    std::vector<IndexCount> index_counts;
    index_counts.reserve(n);
    for (int i = 0; i < n; ++i) {
      index_counts.push_back(IndexCount(i, 0));
    }

    MergeSort(nums, 0, n - 1, &index_counts);

    std::vector<int> answer(n);
    for (const auto& index_count : index_counts) {
      answer[index_count.index] = index_count.count;
    }
    return answer;
  }

 private:
  void MergeSort(const std::vector<int>& nums, int i, int j,
                 std::vector<IndexCount>* index_counts) {
    if (i >= j) {
      return;
    }

    int k = i + (j - i) / 2;
    MergeSort(nums, i, k, index_counts);
    MergeSort(nums, k + 1, j, index_counts);

    std::vector<IndexCount> merged;
    int p1 = i;
    int p2 = k + 1;
    while (p1 <= k || p2 <= j) {
      if (p1 <= k && (p2 > j || nums[(*index_counts)[p1].index] <=
                                    nums[(*index_counts)[p2].index])) {
        merged.push_back((*index_counts)[p1]);
        p1++;
        merged.back().count += p2 - (k + 1);
      } else {
        merged.push_back((*index_counts)[p2]);
        p2++;
      }
    }
    assert(merged.size() == j - i + 1);
    std::copy(merged.begin(), merged.end(), index_counts->begin() + i);
  }
};

int main() {
  std::vector<int> nums({5, 2, 6, 1});
  std::vector<int> answer = Solution().countSmaller(nums);
  for (const auto& elem : answer) {
    std::cout << elem << std::endl;
  }
}
