#ifndef _ALT_SHARED_PTR_H
#define _ALT_SHARED_PTR_H
#include <memory>
#include <atomic>
namespace alt {

namespace impl {

template<typename T>
struct __shared
{
public:
	__shared() : __shared_count(0) {}
	size_t __shared_count;
	char __data[sizeof(T)];
};

}//impl


template<typename T>
class shared_ptr
{
public:

	T* get() { return reinterpret_cast<T*>(_impl->__data); }
	T* operator->() { return get(); }
	T& operator*() { return *get(); }

	template<typename...Args>
	shared_ptr(Args...args)
	: _impl{new impl::__shared<T>}
	{
		//new (get()) T(std::forward(args)...);
		new (get()) T(args...);
		++_impl->__shared_count;
	}

	~shared_ptr()
	{
		auto t=lock();
		if(--t->__shared_count == 0)
			delete t;
		_impl=t;
	}

	shared_ptr(const shared_ptr& r)
	: _impl{r.lock()}
	{
		++_impl->__shared_count;
		r._impl=_impl;
	}


private:
	mutable impl::__shared<T>* _impl;

	impl::__shared<T>* lock() const
	{
		impl::__shared<T>* t=nullptr;
		while(t == nullptr)
			t=std::atomic_exchange(&_impl, t);
		return t;
	}


};



}
#endif
