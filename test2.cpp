#include <iostream>

int main()
{
	unsigned int x1 = 0 - 1;
	unsigned int y1 = 0 - 1;
	unsigned long long tmp = 1ull * x1 * y1;
	std::cout << tmp << '\n';


	unsigned long long x = 0 - 1;
	unsigned long long z = 0 - 1;
	std::cout << x << "  " << x * z << "\n";
	return 0;
}
