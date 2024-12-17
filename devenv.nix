{ pkgs, ... }:
{
  packages = with pkgs.llvmPackages_19; [
    # scaffold
    pkgs.jinja2-cli

    # build
    pkgs.bazel_7
    pkgs.bazel-buildtools

    # LSP
    clang-tools
    stdenv.cc

    # static analysis
    pkgs.cppcheck
    pkgs.flawfinder
  ];

  git-hooks.hooks = {
    # C++
    clang-format = {
      enable = true;
      types_or = [
        "c++"
        "c"
      ];
    };
    clang-tidy = {
      enable = false;
      types_or = [
        "c++"
        "c"
      ];
      entry = "clang-tidy -p build --fix";
    };
    cppcheck = {
      enable = true;
      types = [ "c++" ];
      entry = ''
        cppcheck \
            --check-level=exhaustive \
            --enable=performance \
            --enable=portability \
            --enable=style \
            --enable=warning \
            --library=qt \
            --error-exitcode=1 \
            --inline-suppr \
            --suppress=unusedStructMember \
            --suppress=ctuOneDefinitionRuleViolation
      '';
    };
    flawfinder = {
      enable = true;
      pass_filenames = false;
      entry = "${pkgs.flawfinder}/bin/flawfinder --error-level=0 ./src";
    };

    # nix
    nixfmt-rfc-style.enable = true;
  };
  scripts.scaffold.exec = ''
    mkdir -p "$DEVENV_ROOT/src/day/$1"
    jinja2 "$DEVENV_ROOT/src/tpl/BUILD.bazel.j2" -D day=$1 > "src/day/$1/BUILD.bazel"
    jinja2 "$DEVENV_ROOT/src/tpl/day.cpp.j2" -D day=$1 > "src/day/$1/$1.cpp"
    jinja2 "$DEVENV_ROOT/src/tpl/day.hpp.j2" -D day=$1 > "src/day/$1/$1.hpp"
    bazel run //:cli -- download --day $1 -i data/inputs/$1.txt -p data/puzzles/$1.md --overwrite
  '';
}
