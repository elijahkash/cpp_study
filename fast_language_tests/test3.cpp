#include <iostream>

struct Foo {
	int x = 0;
	int b = 0;

	Foo() = default;
	Foo(int x, int b) : x(x), b(b) {}
};

int main() {
	Foo obj1;
	std::cout << obj1.x << ' ' << obj1.b << '\n';

	Foo obj2{};	
	std::cout << obj2.x << ' ' << obj2.b << '\n';

//	Foo obj3(3);	
//	std::cout << obj3.x << ' ' << obj3.b << '\n';

	Foo obj4{1, 1};
	std::cout << obj4.x << ' ' << obj4.b << '\n';

	Foo obj5 = Foo();
	std::cout << obj5.x << ' ' << obj5.b << '\n';

	Foo obj6(3, 4);
	std::cout << obj6.x << ' ' << obj6.b << '\n';

	Foo obj7 = obj6;
	std::cout << obj7.x << ' ' << obj7.b << '\n';

	Foo obj8(obj6);
	std::cout << obj8.x << ' ' << obj8.b << '\n';

//	std::cout << obj9.x << ' ' << obj9.b << '\n';

	std::cout << std::is_trivially_copyable<Foo>::value << '\n';
	std::cout << std::is_trivial<Foo>::value << '\n';
	std::cout << std::is_standard_layout<Foo>::value << '\n';
	std::cout << std::is_aggregate<Foo>::value << '\n';
	return 0;
}
