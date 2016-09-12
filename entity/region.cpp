#include "region.hpp"

void region::render(vec2 offset)
{
	vec2 scale = area->size / bg->size().cast<double>();
	disp::draw_texture(*bg, area->min + offset, scale);

	for(auto&& it : objects) {
		it->render(offset);
	}
}

void region::step()
{
	for(auto&& it : objects) {
		it->step();
	}
	// TODO: collision detection
}

entity* region::create()
{
	entity* obj = new entity();
	obj->parent = this;
	return this->attach(obj);
}

bool region::destroy(entity* obj)
{
	if(this->detach(obj)) {
		delete obj;
		return true;
	} else {
		return false;
	}
}

entity* region::attach(entity* obj)
{
	objects.insert(obj);
	return obj;
}

bool region::detach(entity* obj)
{
	auto it = objects.find(obj);
	if(it != objects.end()) {
		objects.erase(it);
		return true;
	} else {
		return false;
	}
}
