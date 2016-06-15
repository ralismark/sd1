#include "proxy.hpp"

template <class T>
proxy<T>::proxy(proxy<T>::processor getter, proxy<T>::processor setter, void* xinit, T init)
	: get(getter), set(setter), val(init), ex(xinit)
{ ; }

template <class T>
T proxy<T>::operator=(T new_val)
{
	return val = set(ex, new_val);
}

template <class T>
proxy<T>::operator T() const
{
	return get(ex, val);
}
