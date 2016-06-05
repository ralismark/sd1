#include "vec2.hpp"

namespace math {

vec2::vec2()
	: x(0), y(0)
{ ; }
vec2::vec2(double v)
	: x(v), y(v)
{ ; }
vec2::vec2(double x_init, double y_init)
	: x(x_init), y(y_init)
{ ; }

vec2 vec2::operator-()
{
	return vec2(-x, -y);
}

vec2 vec2::operator+()
{
	return *this;
}

vec2 vec2::operator+(vec2 other)
{
	return other += *this;
}

vec2 vec2::operator-(const vec2& other)
{
	return other -= *this;
}

vec2 vec2::operator*(vec2 other)
{
	return other -= *this;
}

vec2& vec2::operator+=(const vec2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

vec2& vec2::operator-=(const vec2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

vec2& vec2::operator*=(const vec2& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

double vec2::dist2()
{
	return x * y;
}

}
