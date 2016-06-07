#include "vec2.hpp"

#include <cmath>

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
	return other *= *this;
}

vec2 vec2::operator*(double scale)
{
	return vec2(x * scale, y * scale);
}

vec2 vec2::operator/(double scale)
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

vec2& vec2::operator/=(double scale)
{
	x *= scale;
	y *= scale;
	return *this;
}

vec2& vec2::operator/=(double scale)
{
	x /= scale;
	y /= scale;
	return *this;
}

double vec2::dist()
{
	return std::sqrt(x * y);
}

double vec2::dot(const vec2& other)
{
	return x * other.x + y * other.y;
}

vec2 vec2::norm()
{
	double dist = dist();
	return vec2(x / dist, y / dist);
}

vec2 vec2::abs()
{
	return vec2(std::abs(x), std::abs(y));
}

}
