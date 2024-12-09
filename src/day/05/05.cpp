#include "05.hpp"
#include "src/util/day/day.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <range/v3/all.hpp>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

using rule = std::pair<int, int>;
using rules = std::vector<rule>;
using order = std::vector<int>;
using orders = std::vector<order>;

auto orderRules(rules rules) {
  std::unordered_map<int, std::vector<int>> sorted_rules;
  for (auto r : rules) {
    sorted_rules[r.first].push_back(r.second);
  }
  return sorted_rules;
}

auto reorderPages(auto rules, auto order) {
  auto origSize = order.size();
  auto result = std::vector<int>();
  while (result.size() != origSize) {
    auto options = std::vector<std::pair<int, std::vector<int>>>();
    for (auto i = 0; i < order.size(); i++) {
      auto vecC = std::vector<int>(order);
      auto removed = order[i];
      vecC.erase(vecC.begin() + i);
      options.push_back(std::make_pair(removed, vecC));
    }
    for (auto option : options) {
      auto comp = std::vector<int>(rules[option.first]);
      std::sort(comp.begin(), comp.end());
      auto tail = std::vector<int>(option.second.begin(), option.second.end());
      std::sort(tail.begin(), tail.end());
      auto diff = std::vector<int>(tail.size());
      std::set_intersection(tail.begin(), tail.end(), comp.begin(), comp.end(),
                            diff.begin());
      if (diff == tail) {
        result.push_back(option.first);
        order.erase(std::remove(order.begin(), order.end(), option.first),
                    order.end());
        break;
      }
    }
  }
  return result;
}

auto partOne(auto rules, auto orders) {
  auto result = 0;
  for (auto order : orders) {
    auto ordered = true;
    for (size_t i = 0; i < order.size() - 1; ++i) {
      auto comp = std::vector<int>(rules[order[i]]);
      std::sort(comp.begin(), comp.end());
      auto tail = std::vector<int>(order.begin() + i + 1, order.end());
      std::sort(tail.begin(), tail.end());
      auto diff = std::vector<int>(tail.size());
      std::set_intersection(tail.begin(), tail.end(), comp.begin(), comp.end(),
                            diff.begin());
      if (diff != tail) {
        ordered = false;
      }
    }
    if (ordered) {
      result += order[order.size() / 2];
    }
  }
  return result;
}

auto partTwo(auto rules, auto orders) {
  auto result = 0;
  for (auto order : orders) {
    auto ordered = true;
    for (size_t i = 0; i < order.size() - 1; ++i) {
      auto comp = std::vector<int>(rules[order[i]]);
      std::sort(comp.begin(), comp.end());
      auto tail = std::vector<int>(order.begin() + i + 1, order.end());
      std::sort(tail.begin(), tail.end());
      auto diff = std::vector<int>(tail.size());
      std::set_intersection(tail.begin(), tail.end(), comp.begin(), comp.end(),
                            diff.begin());
      if (diff != tail) {
        ordered = false;
      }
    }
    if (!ordered) {
      auto reordered = reorderPages(rules, order);
      result += reordered[reordered.size() / 2];
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(5), argv[0]);
  std::ifstream t(puzzle);
  std::string input{std::istreambuf_iterator<char>(t),
                    std::istreambuf_iterator<char>()};
  auto delim = input.find("\n\n");
  auto rulesStr = std::istringstream(input.substr(0, delim));
  auto ordersStr =
      std::istringstream(input.substr(delim + 2, input.size() - 1));

  auto rules = ranges::getlines(rulesStr, '\n') |
               ranges::views::transform([](std::string const &rule) {
                 return std::make_pair(std::stoi(rule.substr(0, 2)),
                                       std::stoi(rule.substr(3, 2)));
               }) |
               ranges::to<std::vector>();

  auto orders = ranges::getlines(ordersStr, '\n') |
                ranges::views::transform([](std::string const &order) {
                  auto line = std::istringstream(order);
                  return ranges::getlines(line, ',') |
                         ranges::views::transform([](std::string const &num) {
                           return std::stoi(num);
                         }) |
                         ranges::to<std::vector>();
                }) |
                ranges::to<std::vector>;
  auto ordered_rules = orderRules(rules);
  std::cout << "part 1: " << partOne(ordered_rules, orders) << std::endl;
  std::cout << "part 2: " << partTwo(ordered_rules, orders) << std::endl;
  return 0;
}
