#include "03.hpp"
#include "src/util/day/day.hpp"
#include <fstream>
#include <iostream>
#include <range/v3/all.hpp>
#include <regex>
#include <sstream>
#include <string>

auto partOne(auto input) {
  auto r = std::regex{R"<>(mul\((\d{1,3}),(\d{1,3})\))<>"};
  std::regex_iterator<std::string::iterator> rit(input.begin(), input.end(), r);
  std::regex_iterator<std::string::iterator> rend;
  return ranges::accumulate(
      ranges::subrange(rit, rend), 0, [](const auto &acc, const auto &match) {
        return acc + std::stoi(match[1]) * std::stoi(match[2]);
      });
}

auto partTwo(auto input) {
  auto r = std::regex{R"<>((do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\)))<>"};
  std::regex_iterator<std::string::iterator> rit(input.begin(), input.end(), r);
  std::regex_iterator<std::string::iterator> rend;
  return ranges::accumulate(ranges::subrange(rit, rend), std::pair(0, true),
                            [](const auto &acc, const auto &match) {
                              if (match[1] == "do()") {
                                return std::pair(acc.first, true);
                              } else if (match[1] == "don't()") {
                                return std::pair(acc.first, false);
                              } else if (acc.second) {
                                return std::pair(acc.first +
                                                     std::stoi(match[2]) *
                                                         std::stoi(match[3]),
                                                 acc.second);
                              } else {
                                return acc;
                              }
                            })
      .first;
}

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(3), argv[0]);
  std::ifstream t(puzzle);
  std::stringstream buffer;
  buffer << t.rdbuf();
  const auto input = buffer.str();

  std::cout << "part 1: " << partOne(input);
  std::cout << "part 2: " << partTwo(input);
  return 0;
}
