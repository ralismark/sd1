#include "entity.hpp"

#include "region.hpp"

entity::entity()
	: parent(nullptr), area(), vel()
{
	area.retain_size = area.retain_center = true;
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
