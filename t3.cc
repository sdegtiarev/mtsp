// safe version, loops forever
// using atomic operations
#include <thread>
#include <memory>
#include <iostream>
#include <assert.h>

auto data=std::make_shared<int>(0);

void read_data() {
	for(;;)
		auto sp=std::atomic_load(&data);
}

int main(int argc, char**argv)
{
	std::thread(read_data).detach();
	for(;;) {
		std::atomic_exchange(&data, std::make_shared<int>(0));
		assert(std::atomic_is_lock_free(&data));
	}
	return 0;
}

