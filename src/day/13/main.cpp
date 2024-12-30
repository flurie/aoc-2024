#include "13.hpp"
#include "src/util/day/day.hpp"
#include <fstream>
#include <iostream>
#include <range/v3/all.hpp>
#include <sstream>
#include <string>

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(13), argv[0]);
  std::ifstream t(puzzle);
  std::stringstream buffer;
  buffer << t.rdbuf();
  const auto input = buffer.str();
  std::cout << "part 1: " << partOne(input);
  std::cout << "part 2: " << partTwo(input);

  return 0;
};
