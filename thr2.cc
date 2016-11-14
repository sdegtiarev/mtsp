  //L1#shared_ptr_base.h : 662
      __shared_count(const __shared_count& __r) noexcept
      : _M_pi(__r._M_pi)
      {
	if (_M_pi != 0)
	  _M_pi->_M_add_ref_copy();
      }
//L2#shared_ptr_base.h : 134
      void
      _M_add_ref_copy()
      { __gnu_cxx::__atomic_add_dispatch(&_M_use_count, 1); }

//L1#shared_ptr_base.h : 658
     ~__shared_count() noexcept
      {
	if (_M_pi != nullptr)
	  _M_pi->_M_release();
      }
//L2#shared_ptr_base.h : 147
  	if (__gnu_cxx::__exchange_and_add_dispatch(&_M_use_count, -1) == 1)
	  {
            _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(&_M_use_count);
	    _M_dispose();
