#pragma once

#include "math/vec.hpp"
#include "math/rect.hpp"
#include "math/path.hpp"

#include "polystyle.hpp"

namespace disp
{

	void line(vec2 begin, vec2 end, edge_style style = {});

	void fill_rect(rect<double> r, fill_style style = {});
	void border_rect(rect<double> r, edge_style style = {});

	void curve(path p, edge_style style = {});
	void polygon(path p, fill_style style = {}); // assumes to be convex

}
