#include <climits>
#include <iostream>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

template <int kNumBits>
class Bitset {
 public:
  int LeastSignificantSet() const {
    for (int i = 0, offset = 0; i < kSize; i++, offset += kBitWidth) {
      int least_significant_set = ffsll(bit_vector_[i]);
      if (least_significant_set > 0) {
        return offset + least_significant_set - 1;
      }
    }
    return kNumBits;
  }

  void Set(int pos) {
    int i = pos / kBitWidth;
    int j = pos % kBitWidth;
    bit_vector_[i] |= (1ULL << j);
  }

  Bitset operator&(const Bitset<kNumBits>& other) const {
    Bitset result;
    for (int i = 0; i < kSize; i++) {
      result.bit_vector_[i] = bit_vector_[i] & other.bit_vector_[i];
    }
    return result;
  }

 private:
  static constexpr int kBitWidth = sizeof(unsigned long long) * 8;
  static constexpr int kSize = (kNumBits + kBitWidth - 1) / kBitWidth;

  array<unsigned long long, kSize> bit_vector_ = {};
};

class Solution {
 public:
  int minTrioDegree(const int n, const vector<vector<int>>& edges) {
    vector<int> degrees(n);
    for (const auto& edge : edges) {
      const int x = edge[0] - 1;
      const int y = edge[1] - 1;
      degrees[x]++;
      degrees[y]++;
    }

    vector<int> order(n);
    for (int x = 0; x < n; x++) {
      order[x] = x;
    }
    sort(order.begin(), order.end(), [&degrees](const int x, const int y) {
      return degrees[x] < degrees[y];
    });
    vector<int> rank(n);
    for (int x = 0; x < n; x++) {
      rank[order[x]] = x;
    }

    vector<Bitset<kMaxN>> neighbors(n);
    for (const auto& edge : edges) {
      const int x = edge[0] - 1;
      const int y = edge[1] - 1;
      neighbors[x].Set(rank[y]);
      neighbors[y].Set(rank[x]);
    }

    int min_degree = INT_MAX;
    for (const auto& edge : edges) {
      const int x = edge[0] - 1;
      const int y = edge[1] - 1;
      const int degree_x = degrees[x];
      const int degree_y = degrees[y];
      if (degree_x + degree_y >= min_degree) {
        continue;
      }

      const int rank_z = (neighbors[x] & neighbors[y]).LeastSignificantSet();
      if (rank_z < kMaxN) {
        const int degree_z = degrees[order[rank_z]];
        min_degree = min(min_degree, degree_x + degree_y + degree_z);
      }
    }
    return (min_degree == INT_MAX ? -1 : min_degree - 6);
  }

 private:
  static constexpr int kMaxN = 400;
};

TEST(BitsetTest, testLeastSignificantSet) {
  Bitset<10> bs1;
  bs1.Set(0);
  bs1.Set(1);
  bs1.Set(3);
  bs1.Set(5);
  bs1.Set(7);

  Bitset<10> bs2;
  bs2.Set(2);
  bs2.Set(4);
  bs2.Set(6);
  bs2.Set(8);

  EXPECT_EQ((bs1 & bs2).LeastSignificantSet(), 10);

  bs2.Set(7);
  EXPECT_EQ((bs1 & bs2).LeastSignificantSet(), 7);

  bs2.Set(1);
  EXPECT_EQ((bs1 & bs2).LeastSignificantSet(), 1);
}

TEST(SolutionTest, testSample1) {
  Solution s;
  EXPECT_EQ(
      s.minTrioDegree(6, {{1, 2}, {1, 3}, {3, 2}, {4, 1}, {5, 2}, {3, 6}}), 3);
}

TEST(SolutionTest, testSample2) {
  Solution s;
  EXPECT_EQ(
      s.minTrioDegree(
          7, {{1, 3}, {4, 1}, {4, 3}, {2, 5}, {5, 6}, {6, 7}, {7, 5}, {2, 6}}),
      0);
}