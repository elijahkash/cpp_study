#include <vector>
#include <iostream>
#include <algorithm>

// TODO: this??? task 5

int mDiff = 0;

int func(const std::vector<std::vector<int>>& a, int row, int col) {
  if (row == a.size() - 1)
    return a[row][col];
  int i = col - mDiff;
  int j = col + mDiff + 1;
  if (i < 0)
    i = 0;
  if (i >= a[row + 1].size())
    return -1;
  if (j >= a[row + 1].size())
    j = a[row + 1].size();

  std::vector<int> vals;
  for (int iter = i; iter < j; iter++)
    vals.push_back(func(a, row + 1, iter));


  if (vals.empty())
    return -1;
  int min = *std::max_element(vals.begin(), vals.end());
  for (auto& item : vals)
    if (item != -1 and item < min)
      min = item;
  return min + a[row][col];
}

int MinDownPath(const std::vector<std::vector<int>>& a, int maxDiff)
{
  mDiff = maxDiff;
  if (a.size() == 0)
    return -1;

  int res = -1;
  for (int i = 0; i < a[0].size(); i++) {
    int tmp = func(a, 0, i);
    if (res == -1 or (tmp != -1 and tmp < res))
      res = tmp;
  }
  return res;
}

int main() {
  int maxDiff;
  std::cin >> maxDiff;

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> a;
  for (int i = 0; i < n; ++i) {
    int m;
    std::cin >> m;

    std::vector<int> line;
    for (int j = 0; j < m; ++j) {
      int val;
      std::cin >> val;
      line.push_back(val);
    }

    a.push_back(std::move(line));
  }

  std::cout << MinDownPath(a, maxDiff);
  return 0;
}