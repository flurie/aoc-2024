#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "10.hpp"
#include <doctest.h>

std::vector<std::string> testcase = {"89010123", "78121874", "87430965",
                                     "96549874", "45678903", "32019012",
                                     "01329801", "10456732"};

TEST_CASE("part one") {
  auto input = parsePuzzle(testcase);
  CHECK(partOne(input) == 36);
}

TEST_CASE("part two") {
  auto input = parsePuzzle(testcase);
  CHECK(partTwo(input) == 81);
}
