#include <iostream>

class Foo {
public:
	int size() = 0;


};

class Foo2 : public Foo {
public:
	int size() final {return sizeof(Foo2);}

private:
	char x;
	char y;
};

int main() {
	std::cout << sizeof(Foo) << '\n';
	std::cout << sizeof(Foo2) << '\n';
	Foo2 fff;
	std::cout << fff.size() << '\n';
	return 0;
}
