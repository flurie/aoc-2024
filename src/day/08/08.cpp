#include "08.hpp"
#include "src/util/day/day.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <range/v3/all.hpp>
#include <unordered_map>
#include <vector>

class Coord {
public:
  int x;
  int y;
  explicit Coord(int xVal, int yVal) {
    x = xVal;
    y = yVal;
  }
  Coord distance(const Coord &c) const { return Coord((x - c.x), (y - c.y)); }
  int scalarDistance(const Coord &c) const {
    return std::abs(x - c.x) + std::abs(y - c.y);
  }
  Coord operator*(int scalar) { return Coord(x * scalar, y * scalar); }
  Coord operator/(int scalar) { return Coord(x / scalar, y / scalar); }
  bool operator==(const Coord &c) const { return x == c.x && y == c.y; }
  std::string show() const {
    return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
  }
  bool isColinear(const Coord &c1, const Coord &c2) const {
    // the points (𝑎,𝑏), (𝑚,𝑛) and (𝑥,𝑦) are collinear if and only iff
    // (𝑛−𝑏)(𝑥−𝑚)=(𝑦−𝑛)(𝑚−𝑎)
    return ((c1.y - y) * (c2.x - c1.x) == (c2.y - c1.y) * (c1.x - x));
  }
};

class Grid {
public:
  explicit Grid(std::string const &input) {
    auto loc = Coord(0, 0);
    for (auto const &c : input) {
      if (c == '.') {
        spaces.push_back(loc);
        loc.y += 1;
      } else if (c == '\n') {
        loc.y = 0;
        loc.x += 1;
      } else {
        spaces.push_back(loc);
        antennae[c].emplace_back(loc);
        loc.y += 1;
      }
    }
  }
  int findAntinodes() {
    return ranges::accumulate(
        spaces, 0, [&](const auto &acc, const auto space) {
          for (auto [_, v] : antennae) {
            auto distances =
                ranges::views::transform(v, [&](const auto &antenna) {
                  return antenna.distance(space);
                });
            for (auto d : distances) {
              std::vector<Coord> check;
              // is even, check for half
              if (d.x == 0 && d.y == 0) {

              } else if (d.x % 2 == 0 && d.y % 2 == 0) {
                check = {d / 2, d * 2};
              } else {
                check = {d * 2};
              }
              const auto result =
                  std::find_first_of(distances.begin(), distances.end(),
                                     check.begin(), check.end());
              if (result != distances.end()) {
                return acc + 1;
              }
            }
          };
          return acc;
        });
  }
  int findAntinodes2() {
    return ranges::accumulate(
        spaces, 0, [&](const auto &acc, const auto space) {
          for (auto [_, v] : antennae) {
            auto pairs = ranges::views::cartesian_product(v, v);
            for (auto &&[first, second] : pairs) {
              if (first != second && space.isColinear(first, second)) {
                return acc + 1;
              }
            }
          }
          return acc;
        });
  }

private:
  std::unordered_map<char, std::vector<Coord>> antennae;
  std::vector<Coord> spaces;
};

auto partOne(auto input) {
  auto g = Grid(input);
  return g.findAntinodes();
}

auto partTwo(auto input) {
  auto g = Grid(input);
  return g.findAntinodes2();
}

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(8), argv[0]);
  std::ifstream t(puzzle);
  std::string input{std::istreambuf_iterator<char>(t),
                    std::istreambuf_iterator<char>()};
  std::cout << "part 1: " << partOne(input);
  std::cout << "part 2: " << partTwo(input);
  return 0;
}
