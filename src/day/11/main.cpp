#include "11.hpp"
#include "src/util/day/day.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(11), argv[0]);
  std::ifstream t(puzzle);
  std::stringstream buffer;
  buffer << t.rdbuf();
  auto input = parsePuzzle(buffer.str());
  std::cout << "part 1: " << partOne(input);
  std::cout << "part 2: " << partTwo(input);
  return 0;
};
