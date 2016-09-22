#include "region.hpp"

void region::render(vec2 offset)
{
	rect<double> cpy = area;
	cpy.translate(offset);
	disp::draw_texture(*bg, cpy);

	for(auto&& it : objects) {
		it->render(offset);
	}
}

void region::step()
{
	for(auto&& it : objects) {
		it->step();
	}
}

std::vector<std::pair<entity*, entity*>> region::check_collision() const
{
	std::vector<std::pair<entity*, entity*>> out;
	// good job O(n^2)
	// at least some free lunch with c++
	// TODO: Make something more efficient
	for(auto it = objects.cbegin(); it != objects.cend(); ++it) {
		auto other = it;
		for(++other; other != objects.cend(); ++other) {
			if((*it)->area.overlaps((*other)->area)) {
				out.emplace_back(*it, *other);
			}
		}
	}
	return out;
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
