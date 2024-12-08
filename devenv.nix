{ pkgs, ... }:
{
  packages = with pkgs.llvmPackages_19; [
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

}
