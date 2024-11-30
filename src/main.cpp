#include <iostream>

#include "src/util/cli.hpp"
#include <argparse/argparse.hpp>

int main(int argc, char *argv[]) {
  argparse::ArgumentParser program("advent_of_code");

  // Subcommands

  // Download
  argparse::ArgumentParser download_command("download");
  download_command.add_argument("day");

  // Read
  argparse::ArgumentParser read_command("read");
  read_command.add_argument("day");

  // Scaffold
  argparse::ArgumentParser scaffold_command("scaffold");
  scaffold_command.add_argument("day");
  scaffold_command.add_argument("-d", "--download")
      .help("Download your input and add to the scaffolding")
      .flag();
  scaffold_command.add_argument("-o", "--overwrite")
      .help("Overwrite existing files")
      .flag();

  // Solve
  argparse::ArgumentParser solve_command("solve");
  solve_command.add_argument("day");
  int part = 0;
  solve_command.add_argument("-s", "--submit")
      .help("Submit answer for a part of a given day")
      .choices(1, 2)
      .store_into(part);

  // All
  argparse::ArgumentParser all_command("all");

  // Time
  argparse::ArgumentParser time_command("time");

  // Today
  argparse::ArgumentParser today_command("today");

  // add args to main parser
  program.add_subparser(download_command);
  program.add_subparser(read_command);
  program.add_subparser(scaffold_command);
  program.add_subparser(solve_command);
  program.add_subparser(all_command);
  program.add_subparser(time_command);
  program.add_subparser(today_command);

  // Parse args and dispatch
  try {
    program.parse_args(argc, argv);
    auto runner = aoc::cli::Runner(argv[0]);
    runner::runCli(cliPath);
  } catch (const std::exception &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }
  return 0;
}
