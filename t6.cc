// unsafe version, dumps core
// using copy ctor
#include <thread>
#include <memory>
#include <iostream>

auto map=std::make_shared<int>(0);

void inc() {
	for(;;)
		auto sp=map;
}

int main(int argc, char**argv)
{
	std::thread(inc).detach();
	for(;;)
		map=std::shared_ptr<int>();
	return 0;
}

