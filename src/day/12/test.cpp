#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "12.hpp"
#include <doctest.h>

// std::string testcase = {"125 17"};
std::vector<std::string> testcase1 = {"AAAA", "BBCD", "BBCC", "EEEC"};

std::vector<std::string> testcase2 = {
    "RRRRIICCFF", "RRRRIICCCF", "VVRRRCCFFF", "VVRCCCJFFF", "VVVVCJJCFE",
    "VVIVCCJJEE", "VVIIICJJEE", "MIIIIIJJEE", "MIIISIJEEE", "MMMISSJEEE"};

TEST_CASE("part one, test one") {
  // auto input = parsePuzzle(testcase);
  CHECK(partOne(testcase1) == 140);
}

TEST_CASE("part one, test two") {
  // auto input = parsePuzzle(testcase);
  CHECK(partOne(testcase2) == 1930);
}

TEST_CASE("part two, test one") { CHECK(partTwo(testcase1) == 80); }

TEST_CASE("part two, test two") { CHECK(partTwo(testcase2) == 1206); }
