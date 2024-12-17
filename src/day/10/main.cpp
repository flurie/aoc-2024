#include "10.hpp"
#include "src/util/day/day.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(10), argv[0]);
  std::ifstream t(puzzle);
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(t, line)) {
    lines.push_back(line);
  };
  auto input = parsePuzzle(lines);
  std::cout << "part 1: " << partOne(input);
  std::cout << "part 2: " << partTwo(input);
  return 0;
};
