#include "cli.hpp"

#include "rules_cc/cc/runfiles/runfiles.h"
#include "src/util/day/day.hpp"
#include <algorithm>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

namespace aoc {
namespace cli {

Runner::Runner(const std::string_view execPath)
    : cliPath(getCliPath(execPath)) {}

int Runner::runCli() { return runCli(std::vector<std::string>()); }
int Runner::runCli(std::vector<std::string> args = std::vector<std::string>()) {
  std::vector<std::string> command = {cliPath};
  std::copy(args.begin(), args.end(), std::back_inserter(command));
  auto flattened = joinStrings(command, " ");
  auto resp = std::system(flattened.c_str()); // flawfinder: ignore
  return resp;
}

std::string getCliPath(std::string_view execPath) {
  // using bazel::tools::cpp::runfiles::Runfiles;
  using rules_cc::cc::runfiles::Runfiles;
  std::string error;
  std::unique_ptr<Runfiles> runfiles(Runfiles::Create(
      std::string{execPath}, BAZEL_CURRENT_REPOSITORY, &error));

  if (runfiles == nullptr) {
    std::cerr << "got error: " << error;
    throw error;
  }
  return runfiles->Rlocation("aoc-cli/bin/aoc");
}

std::string getInputPath(Day day) {
  return "data/inputs/" + day.print() + ".txt";
}

std::string getPuzzlePath(Day day) {
  return "data/puzzles/" + day.print() + ".md";
}

std::optional<int> getYear() {
  if (const char *env_p = std::getenv("AOC_YEAR")) // flawfinder: ignore
    return std::stoi(env_p);
  return std::nullopt;
}

} // namespace cli
} // namespace aoc
