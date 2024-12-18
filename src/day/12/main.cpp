#include "12.hpp"
#include "src/util/day/day.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(12), argv[0]);
  std::ifstream t(puzzle);
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(t, line)) {
    lines.push_back(line);
  };
  std::cout << "part 1: " << partOne(lines);
  std::cout << "part 2: " << partTwo(lines);
  return 0;
};
