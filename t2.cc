#include <atomic>
#include <utility>
namespace alt {


template<typename T>
struct _counted
{
	T*	_ptr;
	std::atomic<uint64_t> mutable _ref;

	template<typename...Arg>
	_counted(Arg...arg)
	: _ptr(new T(std::forward(arg)...))
	, _ref(1)
	{}

	// _counted()
	// : _ptr(nullptr)
	// , _ref(1)
	// {}

	~_counted()
	{
		if(--_ref == 0)
			delete _ptr;
	}

	_counted(_counted const&) =default;
	_counted(_counted&&)      =default;
	_counted& operator=(_counted const&) =delete;
	_counted& operator=(_counted&&)      =default;

	_counted* dup() const { ++_ref; return this; }
};




template<typename T>
class shared_ptr
{
	_counted<T>* _imp;

public:
	template<typename...Arg>
	shared_ptr(Arg...arg)
	: _imp{new _counted(arg...)}
	{}

	~shared_ptr() =default;

	T& operator*() { return *_imp._ptr; }
	T const& operator*() const { return *_imp._ptr; }
	T* operator->() { return _imp._ptr; }
	T const* operator->() const { return _imp._ptr; }

	shared_ptr(shared_ptr const& x)
	: _imp(x._imp.dup())
	{}

	shared_ptr(shared_ptr&& x)
	: _imp(std::move(x.imp))
	{}

	shared_ptr& operator=(shared_ptr const& x)
	{
		auto _t=x._imp.dup();
		_imp.~_counted();
		_imp=_t.dup();
	}

	shared_ptr& operator=(shared_ptr&& x)
	{
		_imp=std::move(x._imp);
	}

};

}//alt


int main()
{
	alt::shared_ptr<int> x(0);
	++*x;
	auto y=x;

	return 0;
}


