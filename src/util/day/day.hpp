#ifndef DAY_H_
#define DAY_H_

#include <string>
class Day {
public:
  int value;
  explicit Day(int day);
  explicit Day(const std::string &day);
  friend bool operator<(const Day &l, const Day &r) {
    return l.value < r.value;
  };
  friend bool operator>(const Day &l, const Day &r) { return r < l; };
  Day today();
};

#endif // DAY_H_
