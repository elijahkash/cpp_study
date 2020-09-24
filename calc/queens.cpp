/*
 * LeetCode (ans 21pool) task:
 * https://leetcode.com/problems/n-queens/
 * https://leetcode.com/problems/n-queens-ii/
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <stdexcept>
#include <pair>

class Solution {
 public:
  std::vector<std::vector<std::string>> solveNQueens(int n);
  int totalNQueens(int n);

 private:
  class Field {
   public:
    Field(unsigned n);
    unsigned queensCount();
    bool tryAddQueen(unsigned findFromRow, unsigned findFromCol);
    std::pair<unsigned, unsigned> delLastQueen();
    std::vector<std::vector<std::string>> textMap();

   private:
    unsigned n;
    std::stack<std::pair<unsigned, unsigned>> queens;
    std::vector<bool> rows;
    std::vector<bool> cols;
    std::vector<bool> leftDiagonal;
    std::vector<bool> rightDiagonal;

    void set(unsigned row, unsigned col);
    void clean(unsigned row, unsigned col);
    bool check(unsigned row, unsigned col);
    unsigned getLeftDiagonal(unsigned row, unsigned col);
    unsigned getRightDiagonal(unsigned row, unsigned col);
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

bool Solution::Field::tryAddQueen(unsigned int findFromRow,
                                  unsigned int findFromCol) {
  j = ((findFromCol + 1) < n) ? findFromCol + 1 : 0;
  i = findFromRow + ((findFromCol == 0) ? 1 : 0);
  for (; i < n; i++) {
    for (; j < n; j++) {
      if (check(i, j)) {
        queens.push(std::pair<unsigned, unsigned>(i, j));
        set(i, j);
        return true;
      }
    }
    j = 0;
  }
  return false;
}

std::pair<unsigned int, unsigned int> Solution::Field::delLastQueen() {
  if (not queens.size())
    throw std::range_error("No queens already!\n");
  auto tmp = queens.top();
  clean(tmp.first, tmp.second);
  queens.pop();
  return tmp;
}

std::vector<std::vector<std::string>> Solution::Field::textMap() {

}

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
                                              unsigned int col) {
  return (n - 1 - row + col);
}

unsigned int Solution::Field::getRightDiagonal(unsigned int row,
                                               unsigned int col) {
  return (row + col)
}

vector<vector<string>> Solution::solveNQueens(int n) {
  if (n < 0)
    throw std::logic_error("N can't be negative!\n");


}

int Solution::totalNQueens(int n) {
  if (n < 0)
    throw std::logic_error("N can't be negative!\n");
}

