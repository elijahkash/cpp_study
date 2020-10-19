#include <iostream>

class Foo {
	protected:
		int x = 3;
};

class Bar : public Foo {
	public:
	Bar(Foo base) : Foo(base) {};
};

int main() {
	const Foo t1;
	Bar t2(t1);
	return 0;
}
