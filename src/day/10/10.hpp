#pragma once

#include <range/v3/all.hpp>
#include <utility>
#include <vector>

using Coord = std::pair<int, int>;
using Coords = std::vector<Coord>;
using Row = std::vector<int>;
using Grid = std::vector<Row>;

struct Map {
private:
  int xSize;
  int ySize;

public:
  Grid grid;
  explicit Map(Grid g);
  Coords neighbors(Coord c);
  int at(const Coord &c);
  int solve();
  Coords zeroes();
};

int partOne(Map input);
int partTwo(Map input);
Map parsePuzzle(std::vector<std::string> rawInput);
