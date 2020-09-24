#include <iostream>

#include <memory>

class Foo {
public:
	Foo() { std::cout << "Create Foo\n"; }
	~Foo() { std::cout << "Delete Foo\n"; }
};

template< typename T >
struct array_deleter
{
  void operator ()( T const * p)
  { 
    delete[] p; 
  }
};

int main() {
//	std::shared_ptr<Foo> tmp(new Foo[5], array_deleter<Foo>());
	std::shared_ptr<Foo []> tmp2(new Foo[3], std::default_delete<Foo []>());
	return 0;
}
