#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

struct Worker {
  int quality;
  int wage;
};

bool CompareByRatio(const Worker& a, const Worker& b) {
  return a.wage * b.quality < b.wage * a.quality;
}

class Solution {
 public:
  double mincostToHireWorkers(std::vector<int>& quality, std::vector<int>& wage, int k) {
    int n = quality.size();
    assert(n == (int)wage.size());
    std::vector<Worker> workers;
    for (int i = 0; i < n; ++i) {
      workers.push_back(Worker{quality[i], wage[i]});
    }
    std::sort(workers.begin(), workers.end(), CompareByRatio);

    std::priority_queue<int> min_k_qualities;
    int sum_min_k_qualities = 0;
    for (int i = 0; i < k; ++i) {
      sum_min_k_qualities += workers[i].quality;
      min_k_qualities.push(workers[i].quality);
    }

    double min_cost = (double)workers[k - 1].wage * sum_min_k_qualities / workers[k - 1].quality;
    for (int i = k; i < n; ++i) {
      if (min_k_qualities.top() > workers[i].quality) {
        sum_min_k_qualities -= min_k_qualities.top();
        min_k_qualities.pop();
        sum_min_k_qualities += workers[i].quality;
        min_k_qualities.push(workers[i].quality);
      }
      min_cost = std::min(min_cost, (double)workers[i].wage * sum_min_k_qualities / workers[i].quality);
    }
    return min_cost;
  }
};

int main() {
  {
    std::vector<int> quality({10, 20, 5});
    std::vector<int> wage({70, 50, 30});
    std::cout << Solution().mincostToHireWorkers(quality, wage, 2) << std::endl;
  }
  {
    std::vector<int> quality({3, 1, 10, 10, 1});
    std::vector<int> wage({4, 8, 2, 2, 7});
    std::cout << Solution().mincostToHireWorkers(quality, wage, 3) << std::endl;
  }
}
