#include <iostream>

#include <memory>

static int i = 0;

class Foo {
	int n;
public:
	Foo() { n = i++; std::cout << "Create " << n << '\n'; }
	~Foo() { std::cout << "Delete " << n << '\n'; }
};

int main() {
	std::unique_ptr<Foo> zzz = std::make_unique<Foo>();
	zzz = std::make_unique<Foo>();
	std::cout << "End of exec\n";
	return 0;
}
