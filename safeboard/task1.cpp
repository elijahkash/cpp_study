#include <iostream>

#include <vector>

/*
 * На входе дан массив 32-битных натуральных чисел : A[]
 * (размером до двухсот тысяч элементов). Необходимо внутри массива выявить
 * монотонно невозрастающие последовательности элементов и вывести на экран
 * количество элементов в самой длинной такой последовательности.

  Последовательность считается монотонно невозрастающей,
  если каждый следующий элемент меньше или равен предыдущему.
  Sample Input:
  18
  7 11 9 0 11 15 6 18 2 14 16 1 5 12 14 0 10 11
  Sample Output:
  3
 */

uint calc(std::vector<u_int> arr) {
  std::vector<u_int> supp(arr.size(), 0);
  u_int res = 0;
  supp[0] = 1;
  u_int tmp = arr.size();

  for(u_int i = 1; i < tmp; i++) {
    if (arr[i] <= arr[i - 1]) {
      supp[i] = supp[i - 1] + 1;
    }
    else {
      supp[i] = 1;
      if (supp[i - 1] > res)
        res = supp[i - 1];
    }
  }
  if (supp.back() > res)
    res = supp.back();
  return res;
}

int main() {
  u_int count;
  std::cin >> count;
  if (not count) {
    std::cout << 0;
    return 0;
  }
  std::vector<u_int> arr;
  arr.reserve(count);
  for(u_int i = 0; i < count; i++) {
    u_int tmp;
    std::cin >> tmp;
    arr.emplace_back(tmp);
  }
  std::cout << calc(arr);
  return 0;
}
