#pragma once

#define NEED_BIND_FIRST
#include "utils.hpp"

// statics

template <typename... T>
unsigned int sig<T...>::slot_guard::id_cnt = 1;

template <typename... T>
unsigned int sig<T...>::id_cnt = 1;

// slot guard

template <typename... T>
sig<T...>::slot_guard::slot_guard(slot_type fn, sig_type* tgt)
	: slot(fn), sig(tgt), slot_id("?guard" + std::to_string(id_cnt++), 0)
{
	this->new_con();
}

template <typename... T>
template <typename C>
sig<T...>::slot_guard::slot_guard(C& obj, void (C::*fn)(T...), sig_type* tgt)
	: slot(bind_instance<C, void, T...>(fn, obj)) // functor referencing object
	, sig(tgt), slot_id("?guard" + std::to_string(id_cnt++), &obj)
{
	this->new_con();
}

template <typename C>
sig<T...>::slot_guard::~slot_guard()
{
	this->disconnect();
}

template <typename C>
void sig<T...>::slot_guard::new_con()
{
	if(sig) {
		sig->connect(con, slot);
	}
}

template <typename... T>
void sig<T...>::slot_guard::connect(sig_type* tgt)
{
	this->disconnect();
	sig = tgt;
	this->new_con();
}

template <typename... T>
void sig<T...>::slot_guard::connect(sig_type& tgt)
{
	this->connect(&tgt);
}

template <typename... T>
void sig<T...>::slot_guard::disconnect()
{
	if(sig) {
		sig->disconnect(con);
	}
}

template <typename... T>
sig<T...>::slot_guard::sig_type* sig<T...>::slot_guard::get_signal() const
{
	return sig;
}

template <typename... T>
void sig<T...>::slot_guard::cut()
{
	sig = 0;
}

// main sig implementation

template <typename... T>
std::string sig<T...>::auto_id()
{
	return "?auto" + std::to_string(id_cnt++);
}

template <typename... T>
sig<T...>::slot_id sig<T...>::connect(slot_type slot)
{
	return this->connect(this->auto_id(), slot);
}

template <typename... T>
template <typename C>
sig<T...>::slot_id sig<T...>::connect(C& obj, void (C::*slot)(T...))
{
	return this->connect(this->auto_id(), obj, slot);
}

template <typename... T>
