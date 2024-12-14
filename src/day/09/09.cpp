#include "09.hpp"
#include "src/util/day/day.hpp"
#include <fstream>
#include <functional>
#include <iostream>
#include <range/v3/all.hpp>
#include <set>
#include <tuple>
#include <unordered_map>

auto partOne(auto input) {
  // I think this can be done in a single pass.
  // We already know the number of IDs.
  auto fwd = input.begin();
  auto rev =
      input.end() - 2; // -2 because emacs insists on inserting a \n at the end
                       // of the line when saving the input, thanks bud
  // char place
  auto i = 0;
  auto empty = false;
  auto fID = 0;
  auto rID = (input.size() - 1) / 2;
  auto fVal = *fwd - '0';
  auto rVal = *rev - '0';
  long long sum = 0;
  while (true) {
    if (!empty) {
      while (fVal > 0) {
        sum += (long long)(i * fID);
        ++i;
        --fVal;
      }
      ++fwd;
      if (fwd == rev)
        goto done;
      fVal = *fwd - '0';
      empty = true;
    } else {
      while (fVal > 0) {
        if (rVal == 0) {
          --rev;
          if (fwd == rev)
            goto done;
          // skip the space coming from this direction
          --rev;
          if (fwd == rev)
            goto done;
          rVal = *rev - '0';
          --rID;
        } else {
          sum += (long long)(i * rID);
          --rVal;
          --fVal;
          ++i;
        }
      }
      ++fwd;
      if (fwd == rev)
        goto done;
      ++fID;
      empty = false;
      fVal = *fwd - '0';
    }
  }
done:
  while (rVal > 0) {
    sum += (long long)(i * rID);
    --rVal;
    ++i;
  }
  return sum;
}

auto partTwo(auto input) {
  // going to do this a bit more obviously.
  // we know there are 9999 IDs.
  // we can represent the filesystem as a structure of IDs and free spaces.
  // ID: num, starting position, length
  // Free spaces: accessible by size, ordered by position
  // When claiming space, leftover space gets put into new space accessor
  using IDs = std::tuple<int, int, int>; // ID-number, position, length
  using Spaces =
      std::unordered_map<int,
                         std::set<int>>; // size, automatically-sorted position
  // index of filesystem
  auto idx = 0;
  auto fragmented_ids = std::vector<IDs>();
  auto defragged_ids = std::vector<IDs>();
  Spaces spaces;
  // now we populate the containers
  for (auto const &[i, c] : input | ranges::views::enumerate) {
    // filter out unwanted values (like \n) from our friend emacs
    if (c < '0' || c > '9') {
      continue;
    } else {
      auto len = c - '0';
      // files are even indices
      if (i % 2 == 0) {
        fragmented_ids.push_back(std::make_tuple(i / 2, idx, len));
      } else if (len > 0) { // spaces, skip if empty
        spaces[len].emplace(idx);
      }
      idx += len;
    }
  }
  std::sort(fragmented_ids.begin(), fragmented_ids.end(),
            std::greater<std::tuple<int, int, int>>());
  for (auto file : fragmented_ids) {
    int id, pos, len;
    std::tie(id, pos, len) = file;
    auto newPos = pos;
    auto container = 0;
    for (auto s = 9; s >= len; s--) {
      if (!spaces[s].empty()) {
        auto c = *spaces[s].begin();
        if (c < newPos) {
          container = s;
          newPos = c;
        }
      }
    }
    if (container != 0) {
      // something was found, push new loc to fragmented vec
      defragged_ids.push_back(std::make_tuple(id, newPos, len));
      // reconfigure free space
      if (container == len) {
        // it was same size, can just delete from spaces
        spaces[container].erase(newPos);
      } else {
        // need to create new space with leftover room
        auto newSpace = container - len;
        auto newLoc = newPos + len;
        spaces[container].erase(newPos);
        spaces[newSpace].insert(newLoc);
      }
    } else {
      // no space available, just push existing file
      defragged_ids.push_back(file);
    }
  }
  long long res = 0;
  return ranges::accumulate(
      defragged_ids, res, [](const auto &acc, const auto &file) {
        int id, pos, len;
        std::tie(id, pos, len) = file;
        return acc + (long long)ranges::accumulate(
                         ranges::views::iota(pos, pos + len), 0) *
                         (long long)id;
      });
}

int main(int argc, char *argv[]) {
  auto puzzle = getPuzzleForDay(Day(9), argv[0]);
  std::ifstream t(puzzle);
  std::string input{std::istreambuf_iterator<char>(t),
                    std::istreambuf_iterator<char>()};

  std::cout << "part 1: " << partOne(input);
  std::cout << "part 2: " << partTwo(input);
  return 0;
}
