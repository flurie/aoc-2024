#include <iostream>

#include <reproc++/run.hpp>

// Equivalent to reproc's run example but implemented using reproc++.
int main(int argc, const char **argv) {
  (void)argc;

  int status = -1;
  std::error_code ec;

  reproc::options options;
  options.redirect.parent = true;
  options.deadline = reproc::milliseconds(5000);

  std::tie(status, ec) = reproc::run(argv + 1, options);

  if (ec) {
    std::cerr << ec.message() << std::endl;
  }

  return ec ? ec.value() : status;
}

// #include <cstdlib>
// #include <fstream>
// #include <iostream>
// #include <reproc++/run.hpp>

// int main() {
//   // std::system("ls -l >test.txt"); // executes the UNIX command "ls -l
//   // >test.txt" std::cout << std::ifstream("test.txt").rdbuf();
//   reproc::run("ls -l >test.txt");
//   std::cout << std::ifstream("test.txt").rdbuf();
// }

// // #include <iomanip>
// // #include <iostream>
// // #include <ranges>
// // #include <string_view>

// // int main() {
// //   using std::operator""sv;
// //   constexpr auto words{"Hello^_^C++^_^20^_^!"sv};
// //   constexpr auto delim{"^_^"sv};

// //   for (const auto word : std::views::split(words, delim))
// //     // with string_view's C++23 range constructor:
// //     std::cout << std::quoted(std::string_view(word)) << ' ';
// //   std::cout << '\n';
// // }
