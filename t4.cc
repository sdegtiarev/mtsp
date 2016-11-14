// unsafe version, dumps core
// using move ctor
#include <thread>
#include <memory>
#include <iostream>

struct seed : std::enable_shared_from_this<seed>
{};

auto map=std::make_shared<seed>();

void inc() {
	int cnt=0, last=0;
	for(;; ++cnt) try {
		auto sp=map->shared_from_this();
	} catch(...) { std::cerr<<cnt-last<<std::endl; last=cnt; }
}

int main()
{
	std::thread(inc).detach();
	for(;;)
		map=std::make_shared<seed>();
	return 0;
}

