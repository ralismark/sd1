#include "vec2.hpp"

#include <cmath>

double vec2::proc(double v)
{
	return v;
}

vec2::vec2(double v)
	: x(proc, proc, v), y(proc, proc, v)
{ ; }
vec2::vec2(double x_init, double y_init)
	: x(proc, proc, x_init), y(proc, proc, y_init)
{ ; }

vec2 vec2::operator-() const
{
	return vec2(-x, -y);
}

vec2 vec2::operator+() const
{
	return *this;
}

vec2 vec2::operator+(vec2 other) const
{
	return other += *this;
}

vec2 vec2::operator-(vec2 other) const
{
	return other -= *this;
}

vec2 vec2::operator*(vec2 other) const
{
	return other *= *this;
}

vec2 vec2::operator*(double scale) const
{
	return vec2(x * scale, y * scale);
}

vec2 vec2::operator/(double scale) const
{
	return vec2(x / scale, y / scale);
}

vec2 operator*(double scale, vec2 vec)
{
	return vec * scale;
}

vec2 operator/(double scale, vec2 vec)
{
	return vec / scale;
}

vec2& vec2::operator+=(const vec2& other)
{
	x = x + other.x;
	y = x + other.y;
	return *this;
}

vec2& vec2::operator-=(const vec2& other)
{
	x = x - other.x;
	y = y - other.y;
	return *this;
}

vec2& vec2::operator*=(const vec2& other)
{
	x = x * other.x;
	y = y * other.y;
	return *this;
}

vec2& vec2::operator*=(double scale)
{
	x = x * scale;
	y = y * scale;
	return *this;
}

vec2& vec2::operator/=(double scale)
{
	x = x / scale;
	y = y / scale;
	return *this;
}

double vec2::dist() const
{
	return std::sqrt(x * y);
}

double vec2::dot(const vec2& other) const
{
	return x * other.x + y * other.y;
}

vec2 vec2::norm() const
{
	double dist = this->dist();
	return vec2(x / dist, y / dist);
}

vec2 vec2::abs() const
{
	return vec2(std::abs(x), std::abs(y));
}