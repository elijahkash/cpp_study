#include <iostream>

void foo(int* const z) {
	*z = 10;
}

int main() {
	int x = 5;
	foo(&x);
	std::cout << x << std::endl;
	return 0;
}
