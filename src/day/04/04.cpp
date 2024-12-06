#include "04.hpp"
#include "src/util/day/day.hpp"
#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <range/v3/all.hpp>

template <typename Derived>
auto countSubsequences(
    const Eigen::MatrixBase<Derived> &matrix,
    const std::vector<typename Derived::Scalar> &subsequence) {
  auto matches = 0;

  if (subsequence.empty() ||
      subsequence.size() > matrix.rows() * matrix.cols()) {
    return matches;
  }

  for (auto row = 0; row < matrix.rows(); ++row) {
    for (auto col = 0; col <= matrix.cols() - subsequence.size(); ++col) {
      auto found = true;
      for (auto i = 0; i < subsequence.size(); ++i) {
        if (matrix(row, col + i) != subsequence[i]) {
          found = false;
          break;
        }
      }
      if (found) {
        matches++;
      }
    }
  }

  // Vertical search
  for (auto col = 0; col < matrix.cols(); ++col) {
    for (auto row = 0; row <= matrix.rows() - subsequence.size(); ++row) {
      auto found = true;
      for (auto i = 0; i < subsequence.size(); ++i) {
        if (matrix(row + i, col) != subsequence[i]) {
          found = false;
          break;
        }
      }
      if (found) {
        matches++;
      }
    }
  }

  // Forward diagonal search (top-left to bottom-right)
  for (auto row = 0; row <= matrix.rows() - subsequence.size(); ++row) {
    for (auto col = 0; col <= matrix.cols() - subsequence.size(); ++col) {
      auto found = true;
      for (auto i = 0; i < subsequence.size(); ++i) {
        if (matrix(row + i, col + i) != subsequence[i]) {
          found = false;
          break;
        }
      }
      if (found) {
        matches++;
      }
    }
  }

  // Backward diagonal search (top-right to bottom-left)
  for (auto row = 0; row <= matrix.rows() - subsequence.size(); ++row) {
    for (auto col = subsequence.size() - 1; col < matrix.cols(); ++col) {
      auto found = true;
      for (auto i = 0; i < subsequence.size(); ++i) {
        if (matrix(row + i, col - i) != subsequence[i]) {
          found = false;
          break;
        }
      }
      if (found) {
        matches++;
      }
    }
  }

  return matches;
}

template <typename Derived, typename OtherDerived>
auto countSubmatrices(const Eigen::MatrixBase<Derived> &matrix,
                      const Eigen::MatrixBase<OtherDerived> &submatrix) {
  auto matches = 0;
  for (auto row = 0; row <= matrix.rows() - submatrix.rows(); ++row) {
    for (auto col = 0; col <= matrix.cols() - submatrix.cols(); ++col) {
      Eigen::Matrix<char, 3, 3> test = matrix.block(row, col, 3, 3);
      // apply mask
      test(0, 1) = 0;
      test(1, 0) = 0;
      test(1, 2) = 0;
      test(2, 1) = 0;
      if (test.isApprox(submatrix)) {
        matches++;
      }
    }
  }
  return matches;
}

auto partOne(auto input) {
  std::vector<char> subsequence = {'X', 'M', 'A', 'S'};
  std::vector<char> subsequenceRev = {'S', 'A', 'M', 'X'};
  auto matches = countSubsequences(input, subsequence);
  auto matchesRev = countSubsequences(input, subsequenceRev);
  return matches + matchesRev;
}

auto partTwo(auto input) {
  typedef Eigen::Matrix<char, 3, 3> finder;
  finder submatrix0, submatrix90, submatrix180, submatrix270;
  submatrix0 << 'M', 0, 'S', 0, 'A', 0, 'M', 0, 'S';
  submatrix90 << 'M', 0, 'M', 0, 'A', 0, 'S', 0, 'S';
  submatrix180 << 'S', 0, 'S', 0, 'A', 0, 'M', 0, 'M';
  submatrix270 << 'S', 0, 'M', 0, 'A', 0, 'S', 0, 'M';
  return countSubmatrices(input, submatrix0) +
         countSubmatrices(input, submatrix90) +
         countSubmatrices(input, submatrix180) +
         countSubmatrices(input, submatrix270);
}

int main(int argc, char *argv[]) {
  const auto dim = 140;
  typedef Eigen::Matrix<char, dim, dim> puzzleGrid;
  auto puzzle = getPuzzleForDay(Day(4), argv[0]);
  std::ifstream t(puzzle);
  std::string line;
  puzzleGrid p;
  auto i = 0;
  while (std::getline(t, line)) {
    for (auto &&[j, c] : line | ranges::views::enumerate) {
      p(j, i) = c;
    };
    i++;
  }

  std::cout << "partOne: " << partOne(p) << std::endl;
  std::cout << "partTwo: " << partTwo(p) << std::endl;
  return 0;
}
