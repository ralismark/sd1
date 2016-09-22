#pragma once

#include "predecl.hpp"
#include "entity.hpp"

#include "math/vec.hpp"
#include "math/rect.hpp"
#include "disp/image.hpp"

#include <set>
#include <memory>

class region
{
public: // statics
	struct object_sort // functor
	{
		bool operator()(entity* left, entity* right) const
		{
			if(left->render_order != right->render_order) {
				return left->render_order < right->render_order;
			}
			return left < right;
		}
	};
public: // variables
	std::set<entity*, object_sort> objects; // free sorting

	rect<double> area;
	std::shared_ptr<disp::texture> bg;
public: // methods
	// general operations
	void render(vec2 offset = { 0, 0 } );
	void step();
	// add/remove an owned entity
	entity* create();
	bool destroy(entity* obj); // only if we own it
	// add/remove an existing entity
	entity* attach(entity* obj);
	bool detach(entity* obj); // true if actually removed
};
