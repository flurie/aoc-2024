#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "13.hpp"
#include <doctest.h>

auto testcase = std::string{R"<>(Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=8400, Y=5400

Button A: X+26, Y+66
Button B: X+67, Y+21
Prize: X=12748, Y=12176

Button A: X+17, Y+86
Button B: X+84, Y+37
Prize: X=7870, Y=6450

Button A: X+69, Y+23
Button B: X+27, Y+71
Prize: X=18641, Y=10279
)<>"};

TEST_CASE("part one") {
  // auto input = parsePuzzle(testcase);
  CHECK(partOne(testcase) == 480);
}

TEST_CASE("part two") {
  // auto input = parsePuzzle(testcase);
  CHECK(partTwo(testcase) == 118679050709 * 3 + 103199174542         // b
                                 + 102851800151 * 3 + 107526881786); // d
}
