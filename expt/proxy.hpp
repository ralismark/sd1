template <class T>
class proxy
{
public:
	typedef T (*processor)(T);
private:
	T val;
	
	const processor get;
	const processor set;
public:
	proxy(processor getter, processor setter, T init = T());

	T operator=(T new_val);
	operator T() const;
};

#include "proxy.cpp"
