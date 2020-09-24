#include <iostream>

struct Foo {
	char x = 0;
	char b = 0;
	char cc = 0;

	Foo() = default;
//	Foo(int x, int b) : x(x), b(b) {}
//	virtual int bar(int x) = 0;
};

// class Foo2 : public Foo {
// 	int bar(int x) final {return x + 5;}
// };

int main() {
	std::cout << sizeof(Foo) << '\n';
	return 0;
}
