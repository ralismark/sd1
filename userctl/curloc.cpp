#include "curloc.hpp"

#include <sfml/window/mouse.hpp>
#include "disp/window.hpp" // Assuming stdwin

namespace
{

	int get_x()
	{
		return sf::Mouse::getPosition(disp::stdwin).x;
	}

	int get_y()
	{
		return sf::Mouse::getPosition(disp::stdwin).y;
	}

}

namespace userctl
{

	vec2i cursor_loc()
	{
		return make_vec<int>(get_x(), get_y());
	}

	bvec<int, 2> cursor_vec = {get_x, get_y};

}
