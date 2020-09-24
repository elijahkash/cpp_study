#include <iostream>
#include <chrono>
#include <random>

struct Foo {
	int x;
	long long int y;
};

struct Bar {
	int z;
};

int main() {
	std::random_device rDev;
	std::default_random_engine rEng(rDev());
	std::uniform_int_distribution<int> randVal(-1024, 1024);
	Foo *fozz = new Foo[2073600];
	Bar *bazz = new Bar[2073600];
	for (int i = 0; i < 2073600; i++)
		fozz[i].x = randVal(rEng);

	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < 2073600; i++)
		bazz[i].z = fozz[i].x;

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsedTime = end - start;
	std::cout << "Elapsed time:  " << elapsedTime.count() << '\n';

	return 0;
};
