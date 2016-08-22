#include "path.hpp"

namespace disp
{

	path::path()
		: resource()
	{ ; }

	path::path(std::initializer_list<vec2> il)
		: resource(il.size())
	{
		size_t idx = 0;
		for(auto&& it : il) {
			resource.setPoint(idx++, { it->x, it->y });
		}
	}

	path& path::operator()(vec2 p)
	{
		return (*this)(p->x, p->y);
	}

	path& path::operator()(double x, double y)
	{
		size_t idx = resource.getPointCount();
		resource.setPointCount(idx + 1);
		resource.setPoint(idx, { x, y });
		return *this;
	}

	path::operator const sf::ConvexShape&()
	{
		return resource;
	}

}
