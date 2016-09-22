#include "entity.hpp"

#include "region.hpp"

#include <algorithm>

entity::entity()
	: parent(nullptr), area(), vel(), tex(), com()
{
	area.keep_size = area.keep_center = true;
}

entity::~entity()
{
	parent->detach(this);
	for(auto&& it : com) {
		delete it;
	}
}

void entity::step()
{
	area->center += vel;
}

region* entity::transfer(region* new_parent)
{
	if(parent == new_parent) {
		return parent;
	}

	vec2 g_offset = { 0, 0 };
	if(parent) {
		g_offset = parent->area->min;
	}

	vec2 new_offset = { 0, 0 };
	if(new_parent) {
		new_offset = new_parent->area->min;
	}

	vec2 off_diff = g_offset - new_offset;
	area->center -= off_diff;

	if(parent) {
		parent->detach(this);
	}
	parent = new_parent;
	if(parent) {
		parent->attach(this);
	}

	return parent;
}

void entity::event(int id, uintptr_t data)
{
	for(auto&& it : com) {
		if(it->filter(id)) {
			it->responder(id, data);
		}
	}
}

bool entity::del_cap(cap* obj)
{
	auto it = std::find(com.begin(), com.end(), obj);
	if(it != com.end()) {
		com.erase(it);
		delete obj;
		return true;
	} else {
		return false;
	}
}

void entity::render(vec2 offset)
{
	rect<double> cpy = area;
	cpy.translate(offset);

	disp::draw_texture(tex, cpy);
}
