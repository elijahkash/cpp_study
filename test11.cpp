#include <iostream>

#include <memory>

#include <span>

class Foo {
	int a;
	int b;
	int c;
};

int main()
{
	std::cout << sizeof(std::span<Foo>(new Foo[10], 10));
	return 0;
}
