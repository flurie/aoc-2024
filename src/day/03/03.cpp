#include "03.hpp"
#include "src/util/day/day.hpp"

auto partOne(auto input) { return input }

auto partTwo(auto input) { return input }

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(3), argv[0]);
  std::ifstream t(puzzle);
  std::vector<std::vector<int>> nums;
  std::string line;
  while (std::getline(t, line)) {
    // std::vector<int> vec;
    // int num;
    // std::stringstream buffer(line);
    // while (buffer >> num) {
    //   vec.push_back(num);
    // }
    // nums.push_back(vec);
  }

  std::cout << "part 1: " << partOne(nums);
  std::cout << "part 2: " << partTwo(nums);
  return 0;
}
