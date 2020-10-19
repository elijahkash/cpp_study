#include <iostream>

#include <vector>

int calc(int i, int j) {
  if (i == j)
    return i;
  if (i > j) {
    int tmp = j;
    j = i;
    i = tmp;
  }
  if (i == 0 and j == 1)
    return 2;
  if (i == 0 and j == 2)
    return 1;
  if (i == 1 and j == 2)
    return 0;
}

int main() {
  std::vector<int> numbers;

  char tmp;
  while (std::cin >> tmp) {
    if (tmp == 'A')
      numbers.push_back(0);
    else if (tmp == 'B')
      numbers.push_back(1);
    else if (tmp == 'C')
      numbers.push_back(2);
  }

  while (numbers.size() > 1) {
    for (int i = 0; i < numbers.size(); i++)
      numbers[i] = calc(numbers[i], numbers[i + 1]);
    numbers.pop_back();
  }

  char res = 'A';
  if (numbers[0] == 1)
    res = 'B';
  if (numbers[0] == 2)
    res = 'C';

  std::cout << res;

  return 0;
}

