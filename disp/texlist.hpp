#pragma once

#include <memory>
#include <map>
#include <initializer_list>

#include "math/vec.hpp"
#include "image.hpp"

namespace disp
{

	class texlist
	{
	public: // statics
		typedef int id;
		typedef std::shared_ptr<texture> res_ptr;
	public: // variables
		const res_ptr& resource; // ref to real_resource
	private: // variables
		res_ptr real_resource;
		id selected;
		std::map<id, res_ptr> list;
	public: // methods
		texlist(std::initializer_list<res_ptr> il);

		res_ptr shift(id tex);
		res_ptr set(id tex, res_ptr res); // can add
		void erase(id tex);

		operator res_ptr() const;
		operator const texture&() const;
	};

}
