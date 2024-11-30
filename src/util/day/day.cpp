#include "day.hpp"
#include <chrono>
#include <cstdlib>
#include <ctime>
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
