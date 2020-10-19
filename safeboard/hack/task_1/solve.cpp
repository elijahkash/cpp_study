#include <iostream>

#include <vector>
#include <algorithm>


int find_max(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
  auto max = std::max_element(begin, end);
  int dist = std::distance(begin, end);
  if (*max <= dist + 1) {
    return dist + 1;
  }
  int left = 0;
  int right = 0;
  if (begin != max)
    left = find_max(begin, max);
  if (end != max + 1)
    right = find_max(max + 1, end);
  if (left >= right)
    return left;
  else
    return right;
}

int main() {
  std::vector<int> numbers;

  int tmp;
  while (std::cin >> tmp)
    numbers.push_back(tmp);

  std::vector<int> modules;

  for (int i = 0; i < numbers.size() - 1; i++)
    modules.push_back(std::abs(numbers[i] - numbers[i + 1]));

  auto res = find_max(modules.begin(), modules.end());

  std::cout << res;

  return 0;
}
