#pragma once

#include <string>
class Day {
public:
  int value;
  explicit Day(int day);
  explicit Day(const std::string &day);
  friend bool operator<(const Day &l, const Day &r) {
    return l.value < r.value;
  };
  friend bool operator>(const Day &l, const Day &r) { return r < l; };
  Day today();
  std::string print();
};
std::string getPuzzleForDay(Day day, std::string_view execPath);
