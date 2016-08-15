#pragma once

#include "rect.hpp"

template <typename T>
rect<T>::rect(const T& w, const T& h)
	: ac(
		zero,  zero,
		w,     h,
		w,     h,
		w / 2, h / 2
	    ), dirty(true)
{ ; }

template <typename T>
rect<T>::rect(const gvec<T, 2>& sz)
	: rect(sz.x, sz.y)
{ ; }

template <typename T>
rect<T>::rect(const T& ox, const T& oy, const T& w, const T& h)
	: ac(
		ox,         oy,
		ox + w,     oy + h,
		w,          h,
		ox + w / 2, oy + h / 2
	    ), dirty(true)
{ ; }

template <typename T>
rect<T>::rect(const gvec<T, 2>& o, const gvec<T, 2>& sz)
	: rect(o.x, o.y, sz.x, sz.y)
{ ; }

template <typename T>
rect<T>::rect(const rect& other)
	: ac(other.ac), dirty(true)
{
	this->fix();
}

template <typename T>
rect<T>& rect<T>::operator=(rect other)
{
	ac = other.fix().ac;
	dirty = false;
}

template <typename T>
rect<T>& rect<T>::fix()
{
	if(dirty) {
		dirty = false;

		// 1. Fix sign issues
		if(ac.x2 < ac.x1) {
			auto tmp = ac.x1;
			ac.x1 = ac.x2;
			ac.x2 = tmp;
		}
		if(ac.y2 < ac.y1) {
			auto tmp = ac.y1;
			ac.y1 = ac.y2;
			ac.y2 = tmp;
		}

		// Adjust values
		ac.size = ac.max - ac.min;
		ac.center = ac.min + ac.size / 2;
	}
	return *this;
}

template <typename T>
typename rect<T>::access* rect<T>::operator->()
{
	this->fix();
	dirty = true;
	return &ac;
}

template <typename T>
const typename rect<T>::access* rect<T>::operator->() const
{
	return &ac;
}

template <typename T>
bool rect<T>::operator==(const rect<T>& other) const
{
	if(!dirty && !other.dirty) {
		return ac.min == other->min && ac.max == other->max;
	} else if(dirty && !other.dirty) { // We are dirty
		auto cpy = *this;
		return cpy == other;
	} else if(!dirty && other.dirty) { // Other is dirty
		auto cpy = other;
		return *this == cpy;
	} else { // Both dirty
		auto left = *this;
		auto right = other;
		return left == right;
	}
}

template <typename T>
bool rect<T>::contains(const gvec<T, 2>& p, bool permit_eq) const
{
	if(dirty) {
		auto cpy = *this;
		return this->contains(p, permit_eq);
	} else {
		bool on_edge = p->x == ac.x1 || p->x == ac.x2 || p->y == ac.y1 || p->y == ac.y2;
		bool inside = p->x > ac.x1 && p->x < ac.x2 && p->y > ac.y1 && p->y < ac.y2;
		return inside || (permit_eq && on_edge);
	}
}

template <typename T>
bool rect<T>::overlaps(const rect<T>& r, bool permit_eq) const
{
	if(!dirty && !r.dirty) {
		bool on_edge = r->x1 == ac.x2 || r->x2 == ac.x1 || r->y1 == ac.y2 || r->y2 == ac.y1;
		bool intersect = r->x1 < ac.x2 && r->x2 > ac.x1 && r->y1 < ac.y2 && r->y2 > ac.y1;
		return intersect || (on_edge && permit_eq);
	} else if(dirty && !r.dirty) { // We are dirty
		auto cpy = *this;
		return cpy.overlaps(r, permit_eq);
	} else if(!dirty && r.dirty) { // Other is dirty
		auto cpy = r;
		return this->overlaps(cpy, permit_eq);
	} else { // Both dirty
		auto left = *this;
		auto right = r;
		return left.overlaps(right, permit_eq);
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const rect<T>& r)
{
	return os << "[ " << r->x1 << ", " << r->y1 << " -> " << r->x2 << ", " << r->y2 << " ]";
}