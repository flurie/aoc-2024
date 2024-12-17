#include "10.hpp"
#include <stack>

Grid grid(const std::vector<std::string> &lines) {
  std::vector<std::vector<int>> out;
  int n = lines.size();
  int m = lines[0].size();

  for (int i = 0; i < n; ++i) {
    std::vector<int> x;
    for (int j = 0; j < m; ++j) {
      x.push_back(lines[i][j] - '0');
    }
    out.push_back(std::move(x));
  }

  return out;
}

Map::Map(Grid const g) : grid(g) {
  xSize = g.size();
  ySize = g[0].size();
}

int Map::at(const Coord &c) { return grid[c.first][c.second]; }

Coords Map::zeroes() {
  return ranges::accumulate(
      grid | ranges::views::enumerate, Coords(),
      [&](auto &acc, const auto &i_row) {
        ranges::for_each(
            i_row.second | ranges::views::enumerate, [&](const auto &j_col) {
              if (j_col.second == 0) {
                acc.push_back(std::make_pair(i_row.first, j_col.first));
              }
            });
        return acc;
      });
}

Coord operator+(const Coord &c1, const Coord &c2) {
  return Coord({c1.first + c2.first, c1.second + c2.second});
}

Coords Map::neighbors(Coord c) {
  auto DIR4 = Coords({{-1, 0}, {1, 0}, {0, 1}, {0, -1}});
  return DIR4 | ranges::views::transform([&](auto c2) { return c2 + c; }) |
         ranges::views::remove_if([&](const auto &c) {
           return c.first < 0 || c.first > (xSize - 1) || c.second < 0 ||
                  c.second > (ySize - 1);
         }) |
         ranges::to<Coords>();
}

int countTrails(Map m, Coord start) {
  auto visited = Coords({start});
  auto init_neighbors = m.neighbors(start);
  auto neighbors = init_neighbors |
                   ranges::views::remove_if([&](const auto &n) {
                     return m.at(start) != (m.at(n) - 1);
                   }) |
                   ranges::to<Coords>();
  auto queue = std::stack<Coord>(neighbors.begin(), neighbors.end());
  while (!queue.empty()) {
    auto current = queue.top();
    queue.pop();
    visited.push_back(current);
    init_neighbors = m.neighbors(current);
    auto tmp_neighbors =
        init_neighbors | ranges::views::remove_if([&](const auto &n) {
          return (m.at(current) != (m.at(n) - 1)) ||
                 (std::find(visited.begin(), visited.end(), n) !=
                  visited.end());
        });
    for (auto n : tmp_neighbors) {
      queue.push(n);
    }
  }
  return ranges::accumulate(visited, 0, [&](const auto &acc, const auto &c) {
    if (m.at(c) == 9) {
      return acc + 1;
    } else {
      return acc;
    }
  });
}

int countRatings(Map m, Coord start) {
  auto rating = Coords();
  auto init_neighbors = m.neighbors(start);
  auto neighbors = init_neighbors |
                   ranges::views::remove_if([&](const auto &n) {
                     return m.at(start) != (m.at(n) - 1);
                   }) |
                   ranges::to<Coords>();
  auto queue = std::stack<Coord>(neighbors.begin(), neighbors.end());
  while (!queue.empty()) {
    auto current = queue.top();
    queue.pop();
    if (m.at(current) == 9) {
      rating.push_back(current);
    }
    init_neighbors = m.neighbors(current);
    auto tmp_neighbors =
        init_neighbors | ranges::views::remove_if([&](const auto &n) {
          return (m.at(current) != (m.at(n) - 1));
        });
    for (auto n : tmp_neighbors) {
      queue.push(n);
    }
  }
  return rating.size();
}

int partOne(Map input) {
  return ranges::accumulate(input.zeroes(), 0,
                            [&](const auto &acc, const auto &start) {
                              return acc + countTrails(input, start);
                              ;
                            });
}

int partTwo(Map input) {
  return ranges::accumulate(input.zeroes(), 0,
                            [&](const auto &acc, const auto &start) {
                              return acc + countRatings(input, start);
                              ;
                            });
}

Map parsePuzzle(const std::vector<std::string> &rawInput) {
  return Map(grid(rawInput));
}
