#include <iostream>

#include <thread>
#include <chrono>
#include <atomic>

std::atomic<bool> tmp;

const int * foo()
{
	std::cout << "enter foo\n";
	tmp.wait(true);
	std::cout << "exit foo\n";
}

int main()
{
	tmp.store(true);
	std::cout << "main start thread\n";
	std::thread worker(foo);
	std::cout << "main sleep\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "main store false\n";
	tmp.store(false);
	std::cout << "main exit\n";
	return 0;
}
