#pragma once

#include "../expt/proxy.hpp"

class vec2
{
public:
	static double proc(proxy<double>*, void*, double v);

	proxy<double> x, y;
public:
	vec2(double v = 0);
	vec2(double x_init, double y_init);

	vec2 operator-() const;
	vec2 operator+() const;

	vec2 operator+(vec2 other) const;
	vec2 operator-(vec2 other) const;
	vec2 operator*(vec2 other) const;

	vec2 operator*(double scale) const;
	vec2 operator/(double scale) const;
	friend vec2 operator*(double scale, vec2 vec);
	friend vec2 operator/(double scale, vec2 vec);

	vec2& operator+=(const vec2& other);
	vec2& operator-=(const vec2& other);
	vec2& operator*=(const vec2& other);

	vec2& operator*=(double scale);
	vec2& operator/=(double scale);

	double dist() const;
	double dot(const vec2& other) const;
	vec2 norm() const;
	vec2 abs() const;
};
