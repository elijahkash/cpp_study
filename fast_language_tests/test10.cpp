#include <iostream>

struct Foo {
	unsigned int x : 10;
	unsigned int y : 10;
	unsigned int z : 10;
};

int main() {
	std::cout << sizeof(Foo) << '\n';
	return 0;
}
