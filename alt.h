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
	__shared() : __shared_count(1) {}
	size_t __shared_count;
	char __data[sizeof(T)];
};

}//impl


template<typename T>
class shared_ptr
{
public:

	T* get() { return reinterpret_cast<T*>(_impl.load()->__data); }
	T& operator*() { return *get(); }
	T* operator->() { return get(); }

	template<typename...Args>
	shared_ptr(Args...args)
	: _impl{new impl::__shared<T>}
	{
		//new (get()) T(std::forward(args)...);
		new (get()) T(args...);
	}

	~shared_ptr()
	{
		auto t=lock();
		if(--t->__shared_count == 0)
			delete t;
		_impl=t;
	}

	shared_ptr(shared_ptr& r)
	: _impl{r.lock()}
	{
		++_impl.load()->__shared_count;
		r._impl.exchange(_impl);
	}


	shared_ptr(shared_ptr&& r)
	: _impl{new impl::__shared<T>}
	{
		_impl=r._impl.exchange(_impl);
	}

	shared_ptr& operator=(shared_ptr& r)
	{
		auto t=lock();
		if(--t->__shared_count == 0)
			delete t;

		t=r.lock();
		++t->__shared_count;
		_impl=t;
		r._impl.exchange(_impl);

		return *this;
	}

	shared_ptr& operator=(shared_ptr&& r)
	{
		auto t=lock();
		if(--t->__shared_count == 0)
			delete t;

		t=r.lock();
		++t->__shared_count;
		_impl=t;
		r._impl.exchange(_impl);

		return *this;
	}


private:
	std::atomic<impl::__shared<T>*> _impl;

	impl::__shared<T>* lock()
	{
		impl::__shared<T>* t=nullptr;
		while(t == nullptr)
			t=_impl.exchange(t);
		return t;
	}


};



}
#endif
