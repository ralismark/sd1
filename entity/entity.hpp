#pragma once

#include "predecl.hpp"
#include "math/vec.hpp"
#include "math/rect.hpp"
#include "disp/texlist.hpp"

#include "capability.hpp"

#include <cstdint>
#include <vector>

class entity
{
public: // statics
public: // variables
	region* parent;

	int render_order;

	rect<double> area;
	vec2 vel;

	disp::texlist tex;

	std::vector<cap*> com; // capability component
public: // methods
	entity();
	~entity();

	void step();

	region* transfer(region* new_parent);

	void event(int id, uintptr_t data); // sends data to all capabilities
	template <typename T, typename... A> // user provides template T - it's the cap class
	cap* add_cap(A... args);             // use like: foo.add_cap<bar>(1)
	bool del_cap(cap* obj);

	void render(vec2 offset = { 0, 0 });
};
