#include "rect.hpp"

rect::rect(vec2 sz, vec2 pt)
	: loc(pt), size(sz)
{ ; }

rect::rect(double w, double h, vec2 pt)
	: loc(pt), size(w, h)
{ ; }

double rect::left() const
{
	return size.x >= 0 ? loc.x : loc.x + size.x;
}

double rect::right() const
{
	return size.x >= 0 ? loc.x + size.x : loc.x;
}

double rect::top() const
{
	return size.y >= 0 ? loc.y + size.y : loc.y;
}

double rect::bottom() const
{
	return size.y >= 0 ? loc.y : loc.y + size.y;
}

vec2 rect::center() const
{
	return loc + size / 2;
}

vec2 rect::extents() const
{
	return (size / 2).abs();
}

rect rect::normalise() const
{
	rect alt = *this;
	if(alt.size.x < 0) {
		alt.loc.x += alt.size.x;
		alt.size.x *= -1;
	}
	if(alt.size.y < 0) {
		alt.loc.y += alt.size.y;
		alt.size.y *= -1;
	}
	return alt;
}

bool rect::contains(const vec2& pt) const
{
	vec2 diff = (pt - this->center()).abs();
	return diff.x < this->extents().x && diff.y < this->extents().y;
}

bool rect::overlaps(const rect& other) const
{
	vec2 diff = (other.center() - this->center()).abs();
	vec2 total_sz = this->extents() + other.extents();
	return diff.x > total_sz.x && diff.y > total_sz.y;
}

vec2 rect::closest_corner(const vec2& pt) const
{
	vec2 diff = pt - this->center();
	vec2 corner;
	if(diff.x > 0) {
		corner.x = this->right();
	} else {
		corner.x = this->left();
	}
	if(diff.y > 0) {
		corner.y = this->top();
	} else {
		corner.y = this->bottom();
	}
	return corner;
}
