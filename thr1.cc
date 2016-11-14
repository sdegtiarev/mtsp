//L1#shared_ptr.h : 291
      shared_ptr&
      operator=(shared_ptr&& __r) noexcept
      {
	this->__shared_ptr<_Tp>::operator=(std::move(__r));
	//L2#shared_ptr_base.h : 997
	     __shared_ptr&
	      operator=(__shared_ptr&& __r) noexcept
	      {
		__shared_ptr(std::move(__r)).swap(*this);
	 	//L#3shared_ptr_base.h : 932
	     __shared_ptr(__shared_ptr&& __r) noexcept
	      : _M_ptr(__r._M_ptr), _M_refcount()
	      {
		_M_refcount._M_swap(__r._M_refcount);
		 	//L#4shared_ptr_base.h : 684
		     void _M_swap(__shared_count& __r) noexcept
		      {
			_Sp_counted_base<_Lp>* __tmp = __r._M_pi;
			__r._M_pi = _M_pi;
			_M_pi = __tmp;
		      }
	//L2#shared_ptr_base.h : 1073
     void
      swap(__shared_ptr<_Tp, _Lp>& __other) noexcept
      {
	std::swap(_M_ptr, __other._M_ptr);
	_M_refcount._M_swap(__other._M_refcount);
      }
	 	 //L3#shared_ptr_base.h : 684
	      void
	      _M_swap(__shared_count& __r) noexcept
	      {
		_Sp_counted_base<_Lp>* __tmp = __r._M_pi;
		__r._M_pi = _M_pi;
		_M_pi = __tmp;
	      }
	 //L2#shared_ptr_base.h : 658
      ~__shared_count() noexcept
      {
	if (_M_pi != nullptr)
	  _M_pi->_M_release();
      }
		 //L3#shared_ptr_base.h : 142
	     void
	      _M_release() noexcept
	      {
	        // Be race-detector-friendly.  For more info see bits/c++config.
	        _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(&_M_use_count);
		if (__gnu_cxx::__exchange_and_add_dispatch(&_M_use_count, -1) == 1)
		  {
	            _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(&_M_use_count);
		    _M_dispose();
	//L1#shared_ptr.h : 93 (destructor)
	 //L2#shared_ptr_base.h : 658
	  ~__shared_count() noexcept
	  {
	if (_M_pi != nullptr) //_M_pi == nullptr - true here
	  _M_pi->_M_release();
	  }
