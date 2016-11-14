// unsafe version, dumps core
// using move ctor
#include <thread>
#include <memory>
#include <iostream>

auto data=std::make_shared<int>(0);

void read_data() {
	for(;;)
		auto sp=data;
}

int main()
{
	std::thread(read_data).detach();
	for(;;)
		data=std::make_shared<int>(0);
	return 0;
}
