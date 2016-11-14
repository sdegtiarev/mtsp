	// shared_ptr(move(new))
	auto* tmp_count=new.__shared_count._M_pi;
	new.__shared_count._M_pi=nullptr;
	tmp.__shared_count._M_pi=tmp_count;

	// tmp.swap(map)
	auto* tmp_count=map.__shared_count._M_pi;
	map.__shared_count._M_pi=tmp.__shared_count._M_pi;
	tmp.__shared_count._M_pi=tmp_count;

	// ~tmp
	if(--_M_pi->_M_use_count == 0)
		_M_pi->_M_dispose();

	// ~new
	if(nullptr) ;


