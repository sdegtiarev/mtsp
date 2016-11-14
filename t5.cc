#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <thread>
#include <memory>

std::shared_ptr<int> variant[]={
	std::make_shared<int>(0),
	std::make_shared<int>(0)
};
auto data=variant[0];

void read_data() {
	for(;;)
		auto sp=data;
}

int main()
{
	std::thread(read_data).detach();
	for(size_t n=0;; ++n) {
		data=variant[n%2];
	}

	return 0;
}

