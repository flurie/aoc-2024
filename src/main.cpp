#include <iomanip>
#include <iostream>
#include <ranges>
#include <string_view>

int main() {
  using std::operator""sv;
  constexpr auto words{"Hello^_^C++^_^20^_^!"sv};
  constexpr auto delim{"^_^"sv};

  for (const auto word : std::views::split(words, delim))
    // with string_view's C++23 range constructor:
    std::cout << std::quoted(std::string_view(word)) << ' ';
  std::cout << '\n';
}
