#include "tvec2.hpp"

#include "except.hpp"

tvec2::tvec2(vec2* p, double x_init, double y_init)
	: parent(p), off(x_init, y_init), x(
		[](void* a, double b) { return tvec2::get(tvec2::side::x, a, b); },
		[](void* a, double b) { return tvec2::set(tvec2::side::x, a, b); }, this),
	y(
		[](void* a, double b) { return tvec2::get(tvec2::side::x, a, b); },
		[](void* a, double b) { return tvec2::set(tvec2::side::x, a, b); }, this)
{ ; }

tvec2::tvec2(vec2* p, double v)
	: tvec2(p, v, v)
{ ; }

tvec2::tvec2(double x_init, double y_init)
	: tvec2(0, x_init, y_init)
{ ; }

tvec2::tvec2(double v)
	: tvec2(0, v, v)
{ ; }

double tvec2::get(side s, void* self, double v)
{
	(void)v;

	tvec2* t = static_cast<tvec2*>(self);

	if(s == side::x) {
		return t->off.x + (t->parent ? t->parent->x : 0);
	} else if(s == side::y) {
		return t->off.y + (t->parent ? t->parent->y : 0);
	} else {
		throw except("%s: invalid state of variable", __PRETTY_FUNCTION__);
		return 0;
	}
}

double tvec2::set(side s, void* self, double v)
{
	(void)v;

	tvec2* t = static_cast<tvec2*>(self);

	if(s == side::x) {
		t->off.x = v - (t->parent ? t->parent->x : 0);
	} else if(s == side::y) {
		t->off.y = v - (t->parent ? t->parent->y : 0);
	} else {
		throw except("%s: invalid state of variable", __PRETTY_FUNCTION__);
	}
	return 0;
}
