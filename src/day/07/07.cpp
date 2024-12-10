#include "07.hpp"
#include "src/util/day/day.hpp"
#include <fstream>
#include <iostream>
#include <range/v3/all.hpp>
#include <sstream>
#include <vector>

using Equations = std::pair<long long, std::vector<long long>>;

auto partOne(auto input) {
  long long sum = 0;
  return ranges::accumulate(input, sum, [](const auto &acc, const auto &e) {
    // tail vector
    std::vector<long long> terms(e.second.begin() + 1, e.second.end());
    // head vector (for acc)
    std::vector<long long> init(e.second.begin(), e.second.begin() + 1);
    auto solns = ranges::accumulate(terms, init,
                                    [](const auto &innerAcc, const auto &term) {
                                      auto innerVec = std::vector<long long>();
                                      for (auto innerE : innerAcc) {
                                        // add + and * results
                                        innerVec.push_back(innerE + term);
                                        innerVec.push_back(innerE * term);
                                      }
                                      return innerVec;
                                    });
    if (std::find(solns.begin(), solns.end(), e.first) != solns.end()) {
      return acc + e.first;
    } else {
      return acc;
    }
  });
}

auto partTwo(auto input) {
  long long sum = 0;
  return ranges::accumulate(input, sum, [](const auto &acc, const auto &e) {
    // tail vector
    std::vector<long long> terms(e.second.begin() + 1, e.second.end());
    // head vector (for acc)
    std::vector<long long> init(e.second.begin(), e.second.begin() + 1);
    auto solns = ranges::accumulate(
        terms, init, [](const auto &innerAcc, const auto &term) {
          auto innerVec = std::vector<long long>();
          for (auto innerE : innerAcc) {
            // add +, *, and || results
            innerVec.push_back(innerE + term);
            innerVec.push_back(innerE * term);
            auto s = std::to_string(innerE) + std::to_string(term);
            innerVec.push_back(std::stoll(s));
          }
          return innerVec;
        });
    if (std::find(solns.begin(), solns.end(), e.first) != solns.end()) {
      return acc + e.first;
    } else {
      return acc;
    }
  });
}

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(7), argv[0]);
  std::ifstream t(puzzle);
  std::vector<Equations> e;
  std::string line;
  while (std::getline(t, line)) {
    std::vector<long long> vec;
    long long num, head;
    char drop;
    std::stringstream buffer(line);
    buffer >> head; // init
    buffer >> drop; // drop ":"
    while (buffer >> num) {
      vec.push_back(num);
    }
    e.push_back(std::make_pair(head, vec));
  }

  std::cout << "part 1: " << partOne(e);
  std::cout << "part 2: " << partTwo(e);
  return 0;
}
