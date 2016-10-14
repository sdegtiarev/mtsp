#include <thread>
#include <memory>
#include <iostream>

auto map=std::make_shared<int>(0);

void inc() {
	for(;;)
		auto sp=std::atomic_load(&map);
}

int main(int argc, char**argv)
{
if(std::atomic_is_lock_free(&map))
	std::cout<<"std::shared_ptr is lock free"<<std::endl;
else
	std::cout<<"std::shared_ptr is NOT lock free"<<std::endl;

	std::thread(inc).detach();
	for(;;)
		std::atomic_exchange(&map, std::make_shared<int>(0));
	return 0;
}

