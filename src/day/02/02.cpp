#include "02.hpp"
#include "src/util/day/day.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <range/v3/all.hpp>
#include <sstream>
#include <string>
#include <vector>

auto safe(auto vec) {
  auto diffs = vec | ranges::views::sliding(2) |
               ranges::views::transform(
                   [](const auto &window) { return window[1] - window[0]; });
  const auto max = ranges::max(diffs);
  const auto min = ranges::min(diffs);
  return ((max <= 3 && min >= 1) || (max <= -1 && min >= -3));
}

auto partOne(auto nums) {
  const auto sum =
      ranges::accumulate(nums, 0, [](const auto &i, const auto &vec) {
        return safe(vec) ? i + 1 : i;
      });
  return sum;
}

auto partTwo(auto nums) {
  auto sum = ranges::accumulate(nums, 0, [](const auto &i, const auto &vec) {
    auto vecs = std::vector<std::vector<int>>();
    for (auto i = 0; i < vec.size(); i++) {
      auto vecC = std::move(vec);
      vecC.erase(vecC.begin() + i);
      vecs.push_back(vecC);
    }
    return std::any_of(vecs.begin(), vecs.end(), [](auto v) { return safe(v); })
               ? i + 1
               : i;
  });
  return sum;
}

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(2), argv[0]);
  std::ifstream t(puzzle);
  std::vector<std::vector<int>> nums;
  std::string line;
  while (std::getline(t, line)) {
    std::vector<int> vec;
    int num;
    std::stringstream buffer(line);
    while (buffer >> num) {
      vec.push_back(num);
    }
    nums.push_back(vec);
  }

  std::cout << "part 1: " << partOne(nums);
  std::cout << "part 2: " << partTwo(nums);
  return 0;
}
