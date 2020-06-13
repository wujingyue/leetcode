#include "undirected_tree.h"

#include "gtest/gtest.h"

using namespace std;

class ConversionTest : public ::testing::Test {
 protected:
  void VerifyConversion(const UndirectedTree& tree, const vector<int>& prufer) {
    EXPECT_EQ(prufer, tree.ToPrufer());
    EXPECT_EQ(tree, UndirectedTree(prufer, tree.size()));
  }
};

TEST_F(ConversionTest, testSample1) {
  UndirectedTree tree(5);
  tree.AddEdge(0, 1);
  tree.AddEdge(0, 2);
  tree.AddEdge(0, 4);
  tree.AddEdge(3, 4);

  VerifyConversion(tree, {0, 0, 4});
}

TEST_F(ConversionTest, testSample2) {
  UndirectedTree tree(6);
  tree.AddEdge(1, 3);
  tree.AddEdge(3, 2);
  tree.AddEdge(2, 0);
  tree.AddEdge(0, 4);
  tree.AddEdge(3, 5);

  VerifyConversion(tree, {3, 0, 2, 3});
}

TEST_F(ConversionTest, testSample3) {
  UndirectedTree tree(5);
  tree.AddEdge(1, 0);
  tree.AddEdge(0, 2);
  tree.AddEdge(2, 4);
  tree.AddEdge(4, 3);

  VerifyConversion(tree, {0, 2, 4});
}

TEST_F(ConversionTest, testEmptyTree) {
  UndirectedTree tree(0);

  VerifyConversion(tree, {});
}

TEST_F(ConversionTest, testOneNodeTree) {
  UndirectedTree tree(1);

  VerifyConversion(tree, {});
}

int DFS(const UndirectedTree& tree, const int x, vector<bool>& visited) {
  if (visited[x]) {
    return 0;
  }
  visited[x] = true;

  int num_nodes = 1;
  for (const int y : tree.Neighbors(x)) {
    num_nodes += DFS(tree, y, visited);
  }
  return num_nodes;
}

TEST_F(ConversionTest, testRandom) {
  constexpr int n = 100;
  UndirectedTree tree = GenerateRandomUndirectedTree(n);
  for (const int x : tree.ToPrufer()) {
    EXPECT_GE(x, 0);
    EXPECT_LT(x, n);
  }

  int num_neighbors = 0;
  for (int x = 0; x < n; x++) {
    num_neighbors += tree.Neighbors(x).size();
  }
  EXPECT_EQ((n - 1) * 2, num_neighbors);

  vector<bool> visited(n);
  EXPECT_EQ(n, DFS(tree, 0, visited));
}
