#include "13.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <range/v3/all.hpp>
#include <regex>

std::pair<int, int> find_solution(auto x1, auto x2, auto y1, auto y2, auto xn,
                                  auto yn) {
  // brute force, favoring the cheaper button
  for (auto i : ranges::views::iota(0, 100)) {
    for (auto j : ranges::views::iota(0, 100)) {
      // cppcheck-suppress useStlAlgorithm
      if (i * x1 + j * x2 == xn && i * y1 + j * y2 == yn) {
        return {i, j};
      }
    }
  }
  return {0, 0};
}

std::pair<long long, long long>
find_solution_algebraic(auto x1, auto x2, auto y1, auto y2, auto xn, auto yn) {
  long long b = (yn * x1 - y1 * xn) / (x1 * y2 - y1 * x2);

  long long a = (xn - b * x2) / x1;

  if (a * x1 + b * x2 == xn && a * y1 + b * y2 == yn && a >= 0 && b >= 0) {
    return {a, b};
  } else {
    return {0, 0};
  }
}

int partOne(std::string input) {
  auto r = std::regex{
      R"<>(Button A: X\+(\d{2}), Y\+(\d{2})\nButton B: X\+(\d{2}), Y\+(\d{2})\nPrize: X=(\d{1,5}), Y=(\d{1,5})\n)<>"};
  std::regex_iterator<std::string::iterator> rit(input.begin(), input.end(), r),
      rend;
  auto init = 0;
  return ranges::accumulate(ranges::subrange(rit, rend), init,
                            [](const auto &acc, const auto &match) {
                              auto [a_button, b_button] = find_solution(
                                  std::stof(match[1]), std::stof(match[3]),
                                  std::stof(match[2]), std::stof(match[4]),
                                  std::stof(match[5]), std::stof(match[6]));
                              return acc + 3 * a_button + b_button;
                            });
}

long long partTwo(std::string input) {
  auto r = std::regex{
      R"<>(Button A: X\+(\d{2}), Y\+(\d{2})\nButton B: X\+(\d{2}), Y\+(\d{2})\nPrize: X=(\d{1,5}), Y=(\d{1,5})\n)<>"};
  std::regex_iterator<std::string::iterator> rit(input.begin(), input.end(), r),
      rend;
  long long init = 0;
  return ranges::accumulate(
      ranges::subrange(rit, rend), init,
      [](const auto &acc, const auto &match) {
        auto [a_button, b_button] = find_solution_algebraic(
            std::stoll(match[1]), std::stoll(match[3]), std::stoll(match[2]),
            std::stoll(match[4]), std::stoll(match[5]) + 10000000000000,
            std::stoll(match[6]) + 10000000000000);
        return acc + 3 * a_button + b_button;
      });
}
