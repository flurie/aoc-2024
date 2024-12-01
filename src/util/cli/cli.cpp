#include "cli.hpp"

#include "src/util/day/day.hpp"
#include "tools/cpp/runfiles/runfiles.h"
#include <algorithm>
#include <csignal>
#include <cstdlib>
#include <format>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

namespace aoc {
namespace cli {

Runner::Runner(const std::string_view execPath)
    : cliPath(getCliPath(execPath)) {}

int Runner::runCli() { return runCli(std::vector<std::string>()); }
// int Runner::runCli(std::vector<std::string> args =
// std::vector<std::string>()) {
//   std::string out, err;
//   std::vector<std::string> command = {cliPath};
//   std::copy(args.begin(), args.end(), std::back_inserter(command));
//   reproc::options options;
//   options.deadline = reproc::milliseconds(5000);
//   auto [status, ec] = reproc::run(command, options);
//   return ec ? ec.value() : status;
// }
int Runner::runCli(std::vector<std::string> args = std::vector<std::string>()) {
  std::vector<std::string> command = {cliPath};
  std::copy(args.begin(), args.end(), std::back_inserter(command));
  auto flattened = joinStrings(command, " ");
  auto resp = std::system(flattened.c_str()); // flawfinder: ignore
  return resp;
}

std::string getCliPath(std::string_view execPath) {
  using bazel::tools::cpp::runfiles::Runfiles;
  std::string error;
  std::unique_ptr<Runfiles> runfiles(Runfiles::Create(
      std::string{execPath}, BAZEL_CURRENT_REPOSITORY, &error));

  if (runfiles == nullptr) {
    std::cerr << "got error: " << error;
    throw error;
  }
  return runfiles->Rlocation("aoc-cli/bin/aoc");
}

// std::string getInputPath(Day day) {
//   return std::format("data/inputs/{}.txt", day.value);
// }

// std::string getPuzzlePath(Day day) {
//   return std::format("data/puzzles/{}.md", day.value);
// }

std::optional<int> getYear() {
  if (const char *env_p = std::getenv("AOC_YEAR")) // flawfinder: ignore
    return std::stoi(env_p);
  return std::nullopt;
}

std::string joinStrings(const std::vector<std::string> &strings,
                        const std::string &delimiter) {
  return std::accumulate(
      strings.begin() + 1, strings.end(), strings[0],
      [&delimiter](const std::string &a, const std::string &b) {
        return a + delimiter + b;
      });
}
} // namespace cli
} // namespace aoc
