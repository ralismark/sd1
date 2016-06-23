#pragma once

#include "vec2.hpp"

class rect
{
public:
	vec2 loc, size;
public:
	rect(double w, double h, vec2 pt = {0, 0});
	rect(vec2 sz = {0, 0}, vec2 pt = {0, 0});

	// X increases from left to right
	// Y increases from bottom to top
	double left() const;
	double right() const;
	double top() const;
	double bottom() const;

	// Helps quite a few ops
	vec2 center() const;
	vec2 extents() const;

	// Fix size if negative
	rect normalise() const;

	// Detect overlapping, though not touching
	bool contains(const vec2& pt) const;
	bool overlaps(const rect& other) const;

	// finds closest corner
	vec2 closest_corner(const vec2& pt) const;
};
