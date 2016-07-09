#include "sigslots.hpp"

#define NEED_BIND_FIRST
#include "utils.hpp"

// class sig::fn

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

// class sig

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

// class slot_guard

template <typename... T>
slot_guard<T...>::slot_guard(slot_type slot_init, sig_type* sig_init)
	: slot(slot_init), sig(sig_init)
{
	this->connect(sig);
}

template <typename... T>
slot_guard<T...>::slot_guard(slot_func* slot_init, sig_type* sig_init)
	: slot(sig_type::to_slot(slot_init)), sig(sig_init)
{
	this->connect(sig);
}

template <typename... T>
template <typename C>
slot_guard<T...>::slot_guard(C& obj, slot_func* slot_init, sig_type* sig_init)
	: slot(sig_type::to_slot(obj, slot_init)), sig(sig_init)
{
	this->connect(sig);
}

template <typename... T>
slot_guard<T...>::~slot_guard()
{
	this->disconnect();
}

template <typename... T>
void slot_guard<T...>::connect(sig_type& new_sig)
{
	this->connect(&new_sig);
}

template <typename... T>
void slot_guard<T...>::connect(sig_type* new_sig)
{
	this->disconnect();
	sig = new_sig;
	if(sig != 0) {
		con = sig->connect(slot);
	}
}

template <typename... T>
void slot_guard<T...>::disconnect()
{
	if(sig != 0) {
		sig->disconnect(con);
		sig = 0;
	}
}

template <typename... T>
void slot_guard<T...>::cut()
{
	con = 0;
	sig = 0;
}
