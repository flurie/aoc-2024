#include "12.hpp"
#include <iostream>
#include <range/v3/all.hpp>
#include <set>
#include <stack>

using Coord = std::pair<int, int>;
using Coords = std::vector<Coord>;
using CoordSet = std::set<Coord>;
using Grid = std::vector<std::string>;

Coord operator+(const Coord &c1, const Coord &c2) {
  return Coord({c1.first + c2.first, c1.second + c2.second});
}

CoordSet neighbors(const Coord &c, const Grid &input) {
  auto xSize = input.size();
  auto ySize = input[0].size();
  auto val = input[c.first][c.second];
  auto DIR4 = Coords({{-1, 0}, {1, 0}, {0, 1}, {0, -1}});
  return DIR4 | ranges::views::transform([&](auto c2) { return c2 + c; }) |
         ranges::views::remove_if([&](const auto &cx) {
           return cx.first < 0 || cx.first > (xSize - 1) || cx.second < 0 ||
                  cx.second > (ySize - 1) ||
                  (input[cx.first][cx.second] != val);
         }) |
         ranges::to<CoordSet>();
}

int calc_area(const Coord &c, const Grid &input, CoordSet &visited) {
  auto perim = 0;
  auto area = 0;
  auto queue = std::stack<Coord>();
  queue.push(c);
  while (!queue.empty()) {
    auto current = queue.top();
    queue.pop();
    if (visited.contains(current)) {
      continue;
    }
    visited.insert(current);
    auto nb = neighbors(current, input);
    perim += 4 - nb.size();
    ++area;
    for (auto n : nb) {
      if (!visited.contains(n)) {
        queue.push(n);
      }
    }
  }
  return perim * area;
}

// 8-dirs
auto U = Coord(-1, 0);
auto UL = Coord(-1, -1);
auto L = Coord(0, -1);
auto DL = Coord(1, -1);
auto D = Coord(1, 0);
auto DR = Coord(1, 1);
auto R = Coord(0, 1);
auto UR = Coord(-1, 1);

int calc_area2(const Coord &c, const Grid &input, CoordSet &visited) {
  auto sides = 0;
  auto area = 0;
  auto region = CoordSet();
  auto queue = std::stack<Coord>();
  queue.push(c);
  // need to establish region first, then calc sides
  while (!queue.empty()) {
    auto current = queue.top();
    queue.pop();
    if (visited.contains(current)) {
      continue;
    }
    visited.insert(current);
    region.insert(current);
    auto nb = neighbors(current, input);
    for (auto n : nb) {
      if (!visited.contains(n)) {
        queue.push(n);
      }
    }
  }
  for (auto cd : region) {
    ++area;
    // sides match corners. add a side if we find a corner.
    // UL outer corner = not L + not U
    if (!region.contains(L + cd) && !region.contains(U + cd)) {
      ++sides;
    }
    // UL inner corner = L + U + not UL
    if (region.contains(L + cd) && region.contains(U + cd) &&
        !region.contains(UL + cd)) {
      ++sides;
    }
    // UR outer corner = not R + not U
    if (!region.contains(R + cd) && !region.contains(U + cd)) {
      ++sides;
    }
    // UR inner corner = R + U + not UR
    if (region.contains(R + cd) && region.contains(U + cd) &&
        !region.contains(UR + cd)) {
      ++sides;
    }
    // DL outer corner = not L + not D
    if (!region.contains(L + cd) && !region.contains(D + cd)) {
      ++sides;
    }
    // DL inner corner = L + D + not DL
    if (region.contains(L + cd) && region.contains(D + cd) &&
        !region.contains(DL + cd)) {
      ++sides;
    }
    // DR outer corner = not R + not D
    if (!region.contains(R + cd) && !region.contains(D + cd)) {
      ++sides;
    }
    // DR inner corner = R + D + not DR
    if (region.contains(R + cd) && region.contains(D + cd) &&
        !region.contains(DR + cd)) {
      ++sides;
    }
  }
  return sides * area;
}

int partOne(Grid const &input) {
  auto visited = CoordSet();
  auto sum = 0;
  for (auto i = 0; auto tmp : input) {
    for (auto j = 0; auto _ : tmp) {
      auto c = Coord(i, j);
      if (visited.contains(c)) {
        ++j;
        continue;
      } else {
        ++j;
        sum += calc_area(c, input, visited);
      }
    }
    ++i;
  }
  return sum;
}

int partTwo(Grid const &input) {
  auto visited = CoordSet();
  auto sum = 0;
  for (auto i = 0; auto tmp : input) {
    for (auto j = 0; auto _ : tmp) {
      auto c = Coord(i, j);
      if (visited.contains(c)) {
        ++j;
        continue;
      } else {
        ++j;
        sum += calc_area2(c, input, visited);
      }
    }
    ++i;
  }
  return sum;
}
