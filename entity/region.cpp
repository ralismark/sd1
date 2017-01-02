#include "region.hpp"
#include "entity.hpp"
#include "core/runtime.hpp"

#include <functional>

region::region()
	: frame(rt::frame.connect(std::bind(&region::dispatch, this, 0, 0)))
	, frame_early(rt::frame_early.connect(std::bind(&region::dispatch, this, 0, 1)))
	, frame_late(rt::frame_late.connect(std::bind(&region::dispatch, this, 0, 2)))
	, render_x(rt::render.connect(std::bind(&region::dispatch, this, 0, 3)))
	, post_render(rt::post_render.connect(std::bind(&region::dispatch, this, 0, 4)))
	, frame_end(rt::frame_end.connect(std::bind(&region::dispatch, this, 0, 5)))
{ }

region::~region()
{
	rt::frame.disconnect(frame);
	rt::frame_early.disconnect(frame_early);
	rt::frame_late.disconnect(frame_late);
	rt::render.disconnect(render_x);
	rt::post_render.disconnect(post_render);
	rt::frame_end.disconnect(frame_end);
}

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
	return this->attach(new entity());
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
	obj->parent = this;
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

void region::dispatch(int id, uintptr_t data)
{
	for(auto&& it : objects) {
		it->event(id, data);
	}
}
