template <class T>
class proxy
{
public:
	typedef T (*processor)(void*, T);
private:
	T val;
	void* ex;
	
	const processor get;
	const processor set;
public:
	proxy(processor getter, processor setter, void* xinit = 0, T init = T());

	T operator=(T new_val);
	operator T() const;
};
