#ifndef CLI_H_
#define CLI_H_

#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace aoc {
namespace cli {

class Runner {
  std::string cliPath;

public:
  explicit Runner(std::string_view execPath);
  int runCli(std::optional<std::vector<std::string>>);
};
std::string getCliPath(std::string_view execPath);
} // namespace cli
} // namespace aoc

#endif // CLI_H_
