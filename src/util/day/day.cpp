#include "day.hpp"
#include "tools/cpp/runfiles/runfiles.h"
#include <__format/format_functions.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

Day::Day(int day) {
  if (day < 1 || day > 25)
    throw "Invalid day";
  value = day;
}

Day::Day(const std::string &day) : Day(std::stoi(day)) {}

// NOTE: time is based on EST so we must fake it since our version of clang
// seems to be missing time zone support
Day Day::today() {
  char env[] = "TZ=America/New_York";
  putenv(env);
  const auto now = std::chrono::system_clock::now();
  auto t_c = std::chrono::system_clock::to_time_t(now);
  auto est_tm = std::localtime(&t_c);
  if (est_tm->tm_mon != 12 || est_tm->tm_mday > 25)
    throw "Today does not work, not during Advent of Code!";
  return Day(est_tm->tm_mday);
}

std::string Day::print() {
  std::ostringstream s;
  s << std::setw(2) << std::setfill('0') << value;
  return s.str();
}

std::string getPuzzleForDay(Day day, std::string_view execPath) {
  using bazel::tools::cpp::runfiles::Runfiles;
  std::string error;
  std::unique_ptr<Runfiles> runfiles(
      Runfiles::Create(std::string{execPath}, "", &error));

  if (runfiles == nullptr) {
    std::cerr << "got error: " << error;
    throw error;
  }
  return runfiles->Rlocation("_main/data/inputs/" + day.print() + ".txt");
}
