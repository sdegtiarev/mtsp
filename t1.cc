// unsafe version, dumps core
// using move ctor
#include <thread>
#include <memory>
#include <iostream>

auto map=std::make_shared<int>(0);

void inc() {
	for(;;)
		auto sp=map;
}

int main()
{
	std::thread(inc).detach();
	for(;;)
		map=std::make_shared<int>(0);
	return 0;
}

