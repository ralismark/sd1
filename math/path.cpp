#include "path.hpp"

path::path()
	: pts()
{ ; }

path::path(std::initializer_list<vec2> il)
	: pts(il)
{ ; }

size_t path::size() const
{
	return pts.size();
}

path& path::operator()(vec2 p)
{
	pts.push_back(p);
	return *this;
}

path& path::operator()(double x, double y)
{
	pts.push_back(make_vec<double>(x, y));
	return *this;
}
