#include <iostream>

#include <utility>

class Foo {
public:
	Foo(int xx) {x = xx;}
protected:
	int x = 5;
};

class Bar : public Foo {
public:
	Bar(int xx) : Foo(xx) {}
	Bar(const Bar &) = delete;
	Bar(Bar &&src) : Foo(src.x) { src.x = 0; }

	int operator()() { static_assert(this->x, "Shit!\n"); return x; }
};

int main() {
	Bar tt(4);
	Bar zz(std::move(tt));
	tt();
	return 0;
}
