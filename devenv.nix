{ pkgs, ... }: {
  packages = [ pkgs.bazel_7 pkgs.clang-tools pkgs.reproc ];

  # https://devenv.sh/pre-commit-hooks/
  # pre-commit.hooks = {
  #   # C++
  #   clang-format = {
  #     enable = true;
  #     types_or = [ "c++" "c" ];
  #   };
  #   clang-tidy = {
  #     enable = false;
  #     types_or = [ "c++" "c" ];
  #     entry = "clang-tidy -p build --fix";
  #   };
  #   cppcheck = {
  #     enable = true;
  #     types = [ "c++" ];
  #     entry = ''
  #       cppcheck \
  #           --check-level=exhaustive \
  #           --enable=performance \
  #           --enable=portability \
  #           --enable=style \
  #           --enable=warning \
  #           --library=qt \
  #           --error-exitcode=1 \
  #           --inline-suppr \
  #           --suppress=unusedStructMember \
  #           --suppress=ctuOneDefinitionRuleViolation
  #     '';
  #   };
  #   flawfinder = {
  #     enable = true;
  #     pass_filenames = false;
  #     entry = "flawfinder --error-level=0 ./src";
  #   };

  #   # # CMake
  #   # cmake-format = {
  #   #   enable = true;
  #   #   types = ["cmake"];
  #   #   entry = "cmake-format -c .cmake.yaml -i";
  #   # };
  #   # cmake-lint = {
  #   #   enable = true;
  #   #   types = ["cmake"];
  #   #   entry = "cmake-lint -c .cmake.yaml";
  #   # };

  #   # # Python
  #   # ruff.enable = true;

  #   # nix
  #   nixfmt.enable = true;
  #   deadnix.enable = true;
  #   flake-checker.enable = true;
  #   nil.enable = true;
  #   statix.enable = true;
  # };

  # See full reference at https://devenv.sh/reference/options/
}
