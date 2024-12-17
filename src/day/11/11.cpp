#include "11.hpp"
#include <iostream>
#include <range/v3/all.hpp>
#include <sstream>
#include <unordered_map>
#include <vector>

std::vector<long long> parsePuzzle(std::string rawInput) {
  auto v = std::vector<long long>();
  std::stringstream buffer(rawInput);
  long long i;
  while (buffer >> i) {
    v.push_back(i);
  }
  return v;
}

long long
recurse_val(long long val, int turns,
            std::vector<std::unordered_map<long long, long long>> &memo) {
  if (turns == 0) {
    return 1;
  } else if (memo[turns - 1].contains(val)) {
    return memo[turns - 1][val];
  } else {
    long long out;
    if (val == 0) {
      out = recurse_val(1, turns - 1, memo);
    } else if (auto s = std::to_string(val); s.size() % 2 == 0) {
      auto f = std::stoll(std::string(s.begin(), s.begin() + (s.size() / 2)));
      auto f_val = recurse_val(f, turns - 1, memo);
      auto b = std::stoll(std::string(s.begin() + (s.size() / 2), s.end()));
      auto b_val = recurse_val(b, turns - 1, memo);
      out = f_val + b_val;
    } else {
      out = recurse_val(val * 2024, turns - 1, memo);
    }
    memo[turns - 1][val] = out;
    return out;
  }
}

long long partOne(std::vector<long long> input) {
  std::vector<std::unordered_map<long long, long long>> memo(25);
  return ranges::accumulate(input, (long long)0,
                            [&](const auto &acc, const auto &val) {
                              return acc + recurse_val(val, 25, memo);
                            });
}

long long partTwo(std::vector<long long> input) {
  std::vector<std::unordered_map<long long, long long>> memo(75);
  return ranges::accumulate(input, (long long)0,
                            [&](const auto &acc, const auto &val) {
                              return acc + recurse_val(val, 75, memo);
                            });
}
