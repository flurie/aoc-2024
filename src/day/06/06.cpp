#include "06.hpp"
#include "src/util/day/day.hpp"
#include <fstream>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

enum Cell {
  EMPTY,  // .
  OBJECT, // #
  OOB,    // OOB
};

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

using Coord = std::pair<int, int>;
using Row = std::vector<Cell>;
using Grid = std::vector<Row>;
using Location = std::pair<Coord, Direction>;

struct Game {
private:
  int xSize;
  int ySize;
  std::set<Location> visitedDetails;
  Coord guardAt;
  Direction guardFacing;
  Cell at(Coord c) {
    // std::cout << "called with coords (" << c.first << "," << c.second << ")"
    //           << std::endl;
    if (c.first < 0 || c.first >= ySize || c.second < 0 || c.second >= xSize)
      return OOB;
    return grid[c.first][c.second];
  }
  Cell facing() {
    // std::cout << "guard at (" << guardAt.first << "," << guardAt.second
    //           << ") and facing" << guardFacing << std::endl;
    switch (guardFacing) {
    case UP:
      return at({guardAt.first - 1, guardAt.second});
    case DOWN:
      return at({guardAt.first + 1, guardAt.second});
    case LEFT:
      return at({guardAt.first, guardAt.second - 1});
    case RIGHT:
      return at({guardAt.first, guardAt.second + 1});
    }
  }
  void gameMove() { // true if did not rotate
    if (facing() == EMPTY) {
      switch (guardFacing) {
      case UP:
        guardAt = {guardAt.first - 1, guardAt.second};
        break;
      case DOWN:
        guardAt = {guardAt.first + 1, guardAt.second};
        break;
      case LEFT:
        guardAt = {guardAt.first, guardAt.second - 1};
        break;
      case RIGHT:
        guardAt = {guardAt.first, guardAt.second + 1};
        break;
      }
    } else {
      switch (guardFacing) {
      case UP:
        guardFacing = RIGHT;
        break;
      case RIGHT:
        guardFacing = DOWN;
        break;
      case DOWN:
        guardFacing = LEFT;
        break;
      case LEFT:
        guardFacing = UP;
        break;
      }
    }
  }

public:
  Grid grid;
  std::set<Coord> visited;
  explicit Game(std::string const &input) {
    auto loc = Coord(0, 0);
    auto v = Row();
    for (auto const &c : input) {
      if (c == '.') {
        v.push_back(EMPTY);
        loc.second += 1;
      } else if (c == '#') {
        v.push_back(OBJECT);
        loc.second += 1;
      } else if (c == '^') {
        guardAt = loc;
        guardFacing = UP;
        loc.second += 1;
        v.push_back(EMPTY);
      } else if (c == '\n') {
        grid.push_back(Row(v));
        v.erase(v.begin(), v.end());
        loc.first += 1;
        loc.second = 0;
      }
    }
    xSize = grid.size();
    ySize = grid[0].size();
  }
  int run() {
    while (facing() != OOB) {
      visited.insert(guardAt);
      gameMove();
    }
    // insert last position
    visited.insert(guardAt);
    return visited.size();
  }
  int run2() {
    while (true) {
      visitedDetails.insert(std::make_pair(guardAt, guardFacing));
      gameMove();
      if (facing() == OOB) {
        return 0;
      } else if (visitedDetails.find(std::make_pair(guardAt, guardFacing)) !=
                 visitedDetails.end()) {
        return 1;
      }
    }
  }
};

auto partOne(auto input) {
  auto g = Game(input);
  return g.run();
}

auto partTwo(auto input) {
  auto g = Game(input);
  g.run();
  auto visited = std::set(g.visited);
  auto sum = 0;
  for (auto v : visited) {
    auto g2 = Game(input);
    g2.grid[v.first][v.second] = OBJECT;
    sum += g2.run2();
  }
  return sum;
}

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(6), argv[0]);
  std::ifstream t(puzzle);
  std::string input{std::istreambuf_iterator<char>(t),
                    std::istreambuf_iterator<char>()};
  std::cout << "part 1: " << partOne(input) << std::endl;
  std::cout << "part 1: " << partTwo(input) << std::endl;
  return 0;
}
