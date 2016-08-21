#include "texlist.hpp"

#include <iostream>

namespace disp
{

	texlist::texlist()
		: resource(real_resource), real_resource(0), selected(id())
		, list({ {id(), 0}, }) // id() is still valid
	{ ; }

	texlist::texlist(std::initializer_list<res_ptr> il)
		: texlist()
	{
		id i = 0;
		for(auto&& it : il) {
			list[i++] = it;
		}
	}

	texlist::res_ptr texlist::shift(id tex)
	{
		if(!list.count(tex)) {
			tex = id();
		}

		selected = tex;
		return real_resource = list[tex];
	}

	texlist::res_ptr texlist::next()
	{
		auto it = list.find(selected);
		++it;
		if(it == list.end()) {
			return this->shift(0);
		} else {
			return this->shift(it->first);
		}
	}

	texlist::res_ptr texlist::set(id tex, res_ptr res)
	{
		list[tex] = res;
		if(tex == selected) {
			real_resource = list[tex];
		}
		return res;
	}

	texlist::res_ptr texlist::set(id tex, texture* res)
	{
		res_ptr ptr = {res, disp::texture::free};
		return this->set(tex, ptr);
	}

	void texlist::erase(id tex)
	{
		if(!list.count(tex)) {
			return;
		}

		if(tex == id()) {
			list[0] = 0;
		} else {
			list.erase(tex);
			if(selected == tex) {
				this->shift(id());
			}
		}
	}

	texlist::id texlist::state() const
	{
		return selected;
	}

	texlist::operator texlist::res_ptr() const
	{
		return real_resource;
	}

	texlist::operator const texture&() const
	{
		return *real_resource;
	}

}
