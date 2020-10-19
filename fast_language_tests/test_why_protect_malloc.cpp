#include <iostream>

#include <stdlib.h>

int main() {
  int *some_data = (int*)malloc(4); 
  *some_data = 0;
  unsigned long long x = (unsigned long long)some_data / 4; // какое-то большое значение получившиеся в результате каких-либо вычислений
  int *another_data = NULL; // имитируем сфейлившийся маллок
  another_data[x] = 100;
  std::cout << *some_data << std::endl;
}

//int main() {
 // return 0;
//}



