#pragma once

#include "proxy.hpp"
#include "vec2.hpp"

class tvec2
{
public:
	enum struct side { x, y };
	static double get(side s, void* self, double v);
	static double set(side s, void* self, double v);

	vec2* parent;
	vec2 off;
	proxy<double> x, y;
public:
	tvec2(double v = 0);
	tvec2(double x_init, double y_init);

	tvec2(vec2* p, double v = 0);
	tvec2(vec2* p, double x_init, double y_init);
};
