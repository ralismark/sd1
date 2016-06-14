template <class T>
proxy<T>::proxy(proxy<T>::processor getter, proxy<T>::processor setter, xinit, T init)
	: get(getter), set(setter), val(init), ex(xinit)
{ ; }

template <class T>
T proxy<T>::operator=(T new_val)
{
	return val = set(this, ex, new_val);
}

template <class T>
proxy<T>::operator T() const
{
	return get(this, ex, val);
}
