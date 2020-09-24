/*
 * LeetCode (ans 21pool) task:
 * https://leetcode.com/problems/n-queens/
 * https://leetcode.com/problems/n-queens-ii/
 * */

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stdexcept>

class Solution {
 public:
  static std::vector<std::vector<std::string>> solveNQueens(int n);
  int totalNQueens(int n);

 private:
  class Field {
   public:
    explicit Field(unsigned n);
    unsigned queensCount();
    bool tryAddQueenToLine(std::pair<unsigned, unsigned> findFrom);
    std::pair<unsigned, unsigned> delLastQueen();
    std::vector<std::string> textMap();
/*    [[nodiscard]] std::pair<unsigned, unsigned> nextCell(
        std::pair<unsigned, unsigned>) const;*/

   private:
    unsigned n;
    std::list<std::pair<unsigned, unsigned>> queens;
    std::vector<bool> rows;
    std::vector<bool> cols;
    std::vector<bool> leftDiagonal;
    std::vector<bool> rightDiagonal;

    void set(unsigned row, unsigned col);
    void clean(unsigned row, unsigned col);
    bool check(unsigned row, unsigned col);
    [[nodiscard]] unsigned getLeftDiagonal(unsigned row, unsigned col) const;
    static unsigned getRightDiagonal(unsigned row, unsigned col);
  };
};

Solution::Field::Field(unsigned int n)
  : n(n), rows(n, false), cols(n, false),
  leftDiagonal(n * 2 - 1, false),
  rightDiagonal(n * 2 - 1, false) {
}

unsigned Solution::Field::queensCount() {
  return queens.size();
}

bool Solution::Field::tryAddQueenToLine(
    std::pair<unsigned, unsigned> findFrom) {
  unsigned i = findFrom.first;
  unsigned j = findFrom.second;
  if (i >= n)
    return false;
  for (; j < n; j++) {
    if (check(i, j)) {
      queens.emplace_back(i, j);
      set(i, j);
      return true;
    }
  }
  return false;
}

std::pair<unsigned int, unsigned int> Solution::Field::delLastQueen() {
  if (queens.empty())
    throw std::range_error("No queens already!\n");
  auto tmp = queens.back();
  clean(tmp.first, tmp.second);
  queens.pop_back();
  return tmp;
}

std::vector<std::string> Solution::Field::textMap() {
  std::vector<std::string> res(n, std::string(n, '.'));
  for (const auto& queen : queens)
    res[queen.first][queen.second] = 'Q';
  return res;
}

/*std::pair<unsigned, unsigned> Solution::Field::nextCell(
    std::pair<unsigned, unsigned> src) const {
  unsigned j = ((src.second + 1) < n) ? src.second + 1 : 0;
  unsigned i = src.first + ((j == 0) ? 1 : 0);
  return std::pair<unsigned, unsigned>(i, j);
}*/

void Solution::Field::set(unsigned int row, unsigned int col) {
  rows[row] = true;
  cols[col] = true;
  leftDiagonal[getLeftDiagonal(row, col)] = true;
  rightDiagonal[getRightDiagonal(row, col)] = true;
}

void Solution::Field::clean(unsigned int row, unsigned int col) {
  rows[row] = false;
  cols[col] = false;
  leftDiagonal[getLeftDiagonal(row, col)] = false;
  rightDiagonal[getRightDiagonal(row, col)] = false;
}

bool Solution::Field::check(unsigned int row, unsigned int col) {
  return (not rows[row]
          and not cols[col]
          and not leftDiagonal[getLeftDiagonal(row, col)]
          and not rightDiagonal[getRightDiagonal(row, col)]);
}

unsigned int Solution::Field::getLeftDiagonal(unsigned int row,
                                              unsigned int col) const {
  return (n - 1 - row + col);
}

unsigned int Solution::Field::getRightDiagonal(unsigned int row,
                                               unsigned int col) {
  return (row + col);
}

std::vector<std::vector<std::string>> Solution::solveNQueens(int inputN) {
  if (inputN < 0)
    throw std::logic_error("N can't be negative!\n");

  unsigned n = inputN;
  std::vector<std::vector<std::string>> res;
  Field gameField(n);
  std::pair<unsigned, unsigned> i(0, 0);
  while (true) {
    if (gameField.tryAddQueenToLine(i)) {
      if (i.first == n - 1) {
        res.push_back(gameField.textMap());
        i = gameField.delLastQueen();
        i.second++;
      } else {
        i = {i.first + 1, 0};
      }
    } else {
      if (gameField.queensCount()) {
        i = gameField.delLastQueen();
        i.second++;
      } else {
        break;
      }
    }
  }
  return res;
}

int Solution::totalNQueens(int inputN) {
  if (inputN < 0)
    throw std::logic_error("N can't be negative!\n");

  unsigned n = inputN;
  unsigned countRes = 0;
  Field gameField(n);
  std::pair<unsigned, unsigned> i(0, 0);
  while (true) {
    if (gameField.tryAddQueenToLine(i)) {
      if (i.first == n - 1) {
        countRes++;
        i = gameField.delLastQueen();
        i.second++;
      } else {
        i = {i.first + 1, 0};
      }
    } else {
      if (gameField.queensCount()) {
        i = gameField.delLastQueen();
        i.second++;
      } else {
        break;
      }
    }
  }
  return int(countRes);
}

int main(int argc, char** argv) {
  Solution test;
  // std::atoi(argv[1])
  auto res = test.solveNQueens(std::atoi(argv[1]));
  for (const auto& i : res) {
    for (const auto& j : i) {
      std::cout << j << '\n';
    }
    std::cout << "\n";
  }
  return 0;
}
