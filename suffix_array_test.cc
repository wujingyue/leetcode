#include "suffix_array.h"

#include "gtest/gtest.h"

using namespace std;

TEST(SuffixArrayTest, testSimple) {
  vector<int> a({1, 2, 1, 1, 2});
  SuffixArray sa(a);

  EXPECT_EQ(0, sa.GetRank(2));
  EXPECT_EQ(1, sa.GetRank(3));
  EXPECT_EQ(2, sa.GetRank(0));
  EXPECT_EQ(3, sa.GetRank(4));
  EXPECT_EQ(4, sa.GetRank(1));
}

TEST(SuffixArrayTest, testRandom) {
  const int n = 1000;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = rand() % 2 + 10000;
  }

  struct VectorIndex {
    vector<int> v;
    int index;

    bool operator<(const VectorIndex& other) const { return v < other.v; }
  };

  vector<VectorIndex> vector_indexes;
  vector_indexes.reserve(n);
  for (int i = 0; i < n; i++) {
    vector_indexes.push_back({vector<int>(a.begin() + i, a.end()), i});
  }
  sort(vector_indexes.begin(), vector_indexes.end());

  SuffixArray sa(a);
  for (int rank = 0; rank < n; rank++) {
    EXPECT_EQ(rank, sa.GetRank(vector_indexes[rank].index));
  }
}
