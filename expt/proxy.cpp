template <class T>
proxy<T>::proxy(proxy<T>::processor getter, proxy<T>::processor setter, T init)
	: get(getter), set(setter), val(init)
{ ; }

template <class T>
T proxy<T>::operator=(T new_val)
{
	return val = set(new_val);
}

template <class T>
proxy<T>::operator T() const
{
	return get(val);
}
