#include <iostream>

#include <utility>

class Foo {
public:
	Foo(const Foo&) = delete;
	Foo(Foo&&) = default;

	int x = 4;
	Foo(int x) : x(x) {};
};

Foo func(Foo obj) { obj.x = 10; return obj; }

int main() {
	// Foo tmp(5);

	Foo t = func(Foo(5));
	std::cout << t.x << '\n';
	return 0;
}
