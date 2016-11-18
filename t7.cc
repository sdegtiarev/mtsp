#include <iostream>
#include <thread>
#include "alt.h"



auto data=alt::shared_ptr<int>(0);

void read_data() {
	for(;;)
		auto sp=data;
}

int main()
{
	alt::shared_ptr<int> p(1);
	std::cout<<*p<<std::endl;

	auto q=p; ++*q;
	std::cout<<*p<<std::endl;

	auto r=std::move(q); ++*r;
	std::cout<<*p<<std::endl;

	p=alt::shared_ptr<int>(*r+1);
	std::cout<<*p<<std::endl;

	std::thread(read_data).detach();
	for(;;)
		data=alt::shared_ptr<int>(0);

	return 0;
}
