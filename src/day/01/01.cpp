#include "01.hpp"
#include "src/util/day/day.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/chunk_by.hpp>
#include <range/v3/view/zip.hpp>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

auto partOne(auto nums1, auto nums2) {
  auto diff = std::vector<int>();
  for (auto &&[a, b] : ranges::views::zip(nums1, nums2)) {
    diff.push_back(std::abs(b - a));
  }

  const auto sum = ranges::accumulate(diff, 0);
  std::cout << "part 1: " << sum << std::endl;
  return sum;
}

auto partTwo(auto nums1, auto nums2) {
  std::unordered_map<int, int> acc;
  auto groups = nums2 | ranges::views::chunk_by(std::ranges::equal_to{});
  for (auto v : groups) {
    acc.insert({v[0], v.size()});
  }
  const auto sum =
      ranges::accumulate(nums1, 0, [&acc](const auto &a, const auto &b) {
        return a + (b * acc[b]);
      });

  std::cout << "part 2: " << sum << std::endl;
}

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(1), argv[0]);
  std::ifstream t(puzzle);
  std::vector<int> nums1, nums2;
  std::string line;
  while (std::getline(t, line)) {
    int num;
    std::stringstream buffer(line);
    buffer >> num;
    nums1.push_back(num);
    buffer >> num;
    nums2.push_back(num);
  }
  std::sort(nums1.begin(), nums1.end());
  std::sort(nums2.begin(), nums2.end());
  partOne(nums1, nums2);
  partTwo(nums1, nums2);
  return 0;
}
