#include "sigslots.hpp"

#define NEED_BIND_FIRST
#include "utils.hpp"

template <typename... T>
sig<T...>::fn::fn(fn_type* fun)
	: parent(0), func(fun), call(fun)
{ ; }

template <typename... T>
template <typename C>
sig<T...>::fn::fn(C& obj, fn_type* fun)
	: parent(&obj), func(fun), call(bind_first(std_func_type(fun), &obj))
{ ; }

template <typename... T>
void sig<T...>::fn::operator()(T... args) const
{
	call(args...);
}

template <typename... T>
bool sig<T...>::fn::operator<(const fn& other) const
{
	if(parent == other.parent) {
		return func < other.func;
	} else {
		return parent < other.parent;
	}
}

template <typename... T>
typename sig<T...>::slot_type sig<T...>::to_slot(slot_func* slot)
{
	return fn(slot);
}

template <typename... T>
template <typename C>
typename sig<T...>::slot_type sig<T...>::to_slot(C& obj, slot_func* slot)
{
	return fn(obj, slot);
}

template <typename... T>
typename sig<T...>::slot_id sig<T...>::connect(const slot_type& slot)
{
	return slots.insert(slot).first;
}

template <typename... T>
typename sig<T...>::slot_id sig<T...>::connect(slot_func* slot)
{
	return this->connect(sig<T...>::to_slot(slot));
}

template <typename... T>
template <typename C>
typename sig<T...>::slot_id sig<T...>::connect(C& obj, slot_func* slot)
{
	return this->connect(sig<T...>::to_slot(obj, slot));
}

template <typename... T>
void sig<T...>::disconnect(slot_id slot)
{
	slots.erase(slot);
}

template <typename... T>
void sig<T...>::disconnect(slot_type slot)
{
	slots.erase(slot);
}

template <typename... T>
void sig<T...>::disconnect(slot_func* slot)
{
	this->disconnect(sig<T...>::to_slot(slot));
}

template <typename... T>
template <typename C>
void sig<T...>::disconnect(C& obj, slot_func* slot)
{
	this->disconnect(sig<T...>::to_slot(obj, slot));
}

template <typename... T>
void sig<T...>::disconnect_all()
{
	slots.clear();
}

template <typename... T>
typename sig<T...>::slot_id sig<T...>::get_id(sig<T...>::slot_type slot) const
{
	slot_id id = slots.find(slot);
	if(id == slots.end()) {
		return sig<T...>::no_id;
	} else {
		return id;
	}
}

template <typename... T>
typename sig<T...>::slot_id sig<T...>::get_id(slot_func* slot) const
{
	return this->get_id(sig<T...>::to_slot(slot));
}

template <typename... T>
template <typename C>
typename sig<T...>::slot_id sig<T...>::get_id(C& obj, slot_func* slot) const
{
	return this->get_id(sig<T...>::to_slot(obj, slot));
}

template <typename... T>
void sig<T...>::emit(T... args)
{
	for(auto&& slot : slots) {
		slot(args...);
	}
}

template <typename... T>
void sig<T...>::operator()(T... args)
{
	this->emit(args...);
}
