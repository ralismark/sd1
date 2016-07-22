#include "curloc.hpp"

#include <mouse.hpp>
#include "disp/window.hpp" // Assuming stdwin

namespace userctl
{

	vec2i cursor_loc()
	{
		auto pos = sf::Mouse::getPosition(disp::stdwin);
		return vec2i(pos.x, pos.y);
	}

}
