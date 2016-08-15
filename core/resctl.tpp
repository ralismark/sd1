#pragma once

#include "resctl.hpp"

#include <exception>
#include <stdexcept>

template <typename Val, typename Key>
res_ctl<Val, Key>::res_entry::res_entry(Val* init, int plevel)
	: res(init, res_entry::noop), prio(plevel)
{ ; }

template <typename Val, typename Key>
bool res_ctl<Val, Key>::res_entry::operator<(const res_entry& other)
{
	if(prio != other.prio) {
		return prio < other.prio;
	} else {
		return res < other.res; //  Arbitrary relation
	}
}

template <typename Val, typename Key>
void res_ctl<Val, Key>::res_entry::noop(Val*)
{ ; }

template <typename Val, typename Key>
res_ctl<Val, Key>::~res_ctl()
{
	this->cleanup();
	if(holder.size() > 0) {
		if(std::uncaught_exception()) {
			// Stack unwinding from exception, we let that exception propagate
			return;
		} else {
			// Definitely logic error, no bad things happening otherwise
			throw std::logic_error("resources still loaded when controller destroyed");
		}
	}
}

template <typename Val, typename Key>
void res_ctl<Val, Key>::preload(Key id)
{
	if(!holder.count(id)) {
		Val* r = this->load(id);
		if(!r) {
			throw std::runtime_error("Resource could not be loaded");
		}
		holder[id] = r;
	}
}

template <typename Val, typename Key>
std::shared_ptr<Val> res_ctl<Val, Key>::retrieve(Key id)
{
	this->preload(id);
	return holder[id].res;
}

template <typename Val, typename Key>
bool res_ctl<Val, Key>::in_use(Key id) const
{
	if(holder.count(id)) {
		return !holder.at(id).res.unique();
	}
	return false;
}

template <typename Val, typename Key>
void res_ctl<Val, Key>::unload(Key id)
{
	// Wrapper for the iterator version
	if(holder.count(id) && holder[id].res.unique()) {
		this->free(holder[id].res.get());
		holder.erase(id);
	}
}

template <typename Val, typename Key>
void res_ctl<Val, Key>::cleanup(int n)
{
	if(n >= 0) {
		bool uses_cnt = n != 0;
		for(auto it = holder.begin(); it != holder.end() && (!uses_cnt || n != 0); ) {
			if(it->second.res.unique()) {
				if(uses_cnt) {
					--n;
				}
				auto ptr = it++;
				std::cout << "Clean " << it->first << '\n';

				this->unload(ptr->first);
			} else {
				++it;
			}
		}
	} else {
		for(auto it = holder.rbegin(); it != holder.rend() && n != 0; ) {
			if(it->second.res.unique()) {
				--n;
				auto ptr = it++; // Avoid invalid iterators
				std::cout << "Clean " << ptr->first << '\n';

				this->unload(ptr->first);
			} else {
				++it;
			}
		}
	}
}
