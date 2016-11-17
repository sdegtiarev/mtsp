#include <iostream>
#include "alt.h"

int main()
{
	alt::shared_ptr<int> p(7);
	std::cout<<*p<<std::endl;
	auto q=p;
	++*q;
	std::cout<<*p<<std::endl;
	return 0;
}
