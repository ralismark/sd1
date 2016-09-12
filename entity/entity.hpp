#pragma once

#include "predecl.hpp"
#include "math/vec.hpp"
#include "math/rect.hpp"
#include "disp/texlist.hpp"

class entity
{
public: // statics
public: // variables
	region* parent;

	int render_order;

	rect<double> area;
	vec2 vel;

	disp::texlist tex;
public: // methods
	entity();
	~entity();

	void step();

	region* transfer(region* new_parent);

	void render(vec2 offset = { 0, 0 });
};
