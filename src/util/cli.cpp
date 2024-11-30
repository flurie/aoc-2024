#include "cli.hpp"

#include "reproc++/run.hpp"
#include "tools/cpp/runfiles/runfiles.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <tuple>
#include <vector>

namespace aoc {
namespace cli {

Runner::Runner(const std::string_view execPath)
    : cliPath(getCliPath(execPath)) {}

int Runner::runCli() { return runCli(std::vector<std::string>()); }
int Runner::runCli(std::vector<std::string> args = std::vector<std::string>()) {
  std::string out, err;
  std::vector<std::string> command = {cliPath};
  std::copy(args.begin(), args.end(), std::back_inserter(command));
  reproc::options options;
  options.redirect.parent = true;
  options.deadline = reproc::milliseconds(5000);
  auto [status, ec] = reproc::run(command, options, reproc::sink::string(out),
                                  reproc::sink::string(err));

  if (ec) {
    std::cerr << ec.message() << std::endl;
  }

  return ec ? ec.value() : status;
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

} // namespace cli
} // namespace aoc
