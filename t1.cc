#include <thread>
#include <memory>

auto map=std::make_shared<int>(0);

void inc() {
	for(;;)
		auto sp=map;
}

int main(int argc, char**argv)
{
	std::thread(inc).detach();
	for(;;)
		map=std::make_shared<int>(0);
	return 0;
}

