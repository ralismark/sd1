#pragma once

#include <initializer_list>
#include <deque>

#include "vec.hpp"

// different to resources
class path
{
public: // variables
	std::deque<vec2> pts;
public: // methods
	path();
	path(std::initializer_list<vec2> il);

	size_t size() const;

	path& operator()(vec2 p);
	path& operator()(double x, double y);
};
