#define NO_INC_SIGSLOTS_CPP
#include "sigslots.hpp"

#include <climits>
#include <stdexcept>

#define NEED_BIND_FIRST
#include "utils.hpp"

// class sig::fn

template <typename... T>
unsigned long long sig<T...>::fn::id_cnt = 1;

template <typename... T>
sig<T...>::fn::fn(fn_type* fun)
	: parent(0), func(fun), id(0), call(fun)
{ ; }

template <typename... T>
template <typename C>
sig<T...>::fn::fn(C& obj, void (C::*fun)(T...))
	: parent(&obj), id(fn::id_cnt++), func(0), call(bind_instance<C, void, T...>(fun, obj))
{
	if(fn::id_cnt == 0) {
		throw std::overflow_error("reached limit: sig<T...>::fn::id_cnt wraparound!");
	}
}

template <typename... T>
sig<T...>::fn::fn(std::function<fn_type> fun)
	: parent(0), id(fn::id_cnt++), func(0), call(fun)
{
	if(fn::id_cnt == 0) {
		throw std::overflow_error("reached limit: sig<T...>::fn::id_cnt wraparound!");
	}
}

template <typename... T>
void sig<T...>::fn::operator()(T... args) const
{
	call(args...);
}

template <typename... T>
bool sig<T...>::fn::operator<(const fn& other) const
{
	if(parent != other.parent) { // Different objects
		return parent < other.parent;
	} else if(parent != 0) { // Same object, compare ids
		return id < other.id;
	} else if(id != other.id) { // Different callables
		return id < other.id;
	} else { // Both normal functions
		return func < other.func;
	}
}

template <typename... T>
bool sig<T...>::fn::owned_by(void* obj) const
{
	return parent == obj;
}

// class sig

template <typename... T>
const typename sig<T...>::slot_id sig<T...>::no_id = {};

template <typename... T>
const typename sig<T...>::slot_type sig<T...>::no_slot = {0};

template <typename... T>
typename sig<T...>::slot_type sig<T...>::to_slot(slot_func* slot)
{
	return fn(slot);
}

template <typename... T>
template <typename C>
typename sig<T...>::slot_type sig<T...>::to_slot(C& obj, void (C::*slot)(T...))
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
typename sig<T...>::slot_id sig<T...>::connect(C& obj, void (C::*slot)(T...))
{
	return this->connect(sig<T...>::to_slot(obj, slot));
}

template <typename... T>
typename sig<T...>::slot_id sig<T...>::connect(std::function<slot_func> func)
{
	return this->connect(fn(func));
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
void sig<T...>::disconnect(C& obj)
{
	for(const auto& it : slots) {
		if(it.owned_by(&obj)) {
			slots.erase(it);
		}
	}
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
typename sig<T...>::slot_type sig<T...>::get_slot(slot_id slot) const
{
	if(slot == sig<T...>::no_id) {
		return sig<T...>::no_slot;
	} else {
		return *slot;
	}
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
slot_guard<T...>::slot_guard(C& obj, void (C::*slot_init)(T...), sig_type* sig_init)
	: slot(sig_type::to_slot(obj, slot_init)), sig(sig_init)
{
	this->connect(sig);
}

template <typename... T>
slot_guard<T...>::slot_guard(std::function<slot_func> func, sig_type* sig_init)
	: slot(func), sig(sig_init)
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
