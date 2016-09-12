#pragma once

#include "predecl.hpp"
#include "math/vec.hpp"
#include "math/rect.hpp"

class entity
{
public: // statics
public: // variables
	region* parent;

	int render_order;

	rect<double> area;
	vec2 vel;
public: // methods
	entity();
	~entity();

	region* transfer(region* new_parent);
};
