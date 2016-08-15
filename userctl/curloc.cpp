#include "curloc.hpp"

#include <sfml/window/mouse.hpp>
#include "disp/window.hpp" // Assuming stdwin

namespace userctl
{

	vec2i cursor_loc()
	{
		auto pos = sf::Mouse::getPosition(disp::stdwin);
		return make_vec<int>(pos.x, pos.y);
	}

}
