#include "cli.h"

#include "reproc++/run.hpp"
#include "tools/cpp/runfiles/runfiles.h"
#include <iostream>
#include <string>
#include <system_error>
#include <tuple>

namespace aoc {
namespace cli {

std::string getCliPath(std::string execPath) {
  using bazel::tools::cpp::runfiles::Runfiles;
  std::string error;
  std::unique_ptr<Runfiles> runfiles(
      Runfiles::Create(execPath, BAZEL_CURRENT_REPOSITORY, &error));

  if (runfiles == nullptr) {
    std::cerr << "got error: " << error;
    throw error;
  }
  return runfiles->Rlocation("aoc-cli/bin/aoc");
}

int runCli(std::string cliPath) {
  std::string out, err;
  std::vector<std::string> args = {cliPath};
  reproc::options options;
  options.redirect.parent = true;
  options.deadline = reproc::milliseconds(5000);
  auto [status, ec] = reproc::run(args, options, reproc::sink::string(out),
                                  reproc::sink::string(err));

  if (ec) {
    std::cerr << ec.message() << std::endl;
  }

  return ec ? ec.value() : status;
}

} // namespace cli
} // namespace aoc
