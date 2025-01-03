#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "11.hpp"
#include <doctest.h>

std::string testcase = {"125 17"};

TEST_CASE("part one") {
  auto input = parsePuzzle(testcase);
  CHECK(partOne(input) == 55312);
}

// no part two info given for tests
// TEST_CASE("part two") {
//   auto input = parsePuzzle(testcase);
//   CHECK(partTwo(input) == 81);
// }
