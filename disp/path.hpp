#pragma once

#include <initializer_list>
#include <sfml/graphics/convexshape.hpp>

#include "math/vec.hpp"

namespace disp
{

	// different to resources
	class path
	{
	public: // variables
		sf::ConvexShape resource;
	public: // methods
		path();
		path(std::initializer_list<vec2> il);

		path& operator()(vec2 p);
		path& operator()(double x, double y);

		operator const sf::ConvexShape&();
	};

	void border_path(const path& p, int co = 0xffffff, size_t width = 1);
	void fill_path(const path& p, int co = 0xffffff);

}
