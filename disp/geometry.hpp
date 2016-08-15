#pragma once

#include "math/vec.hpp"
#include "math/rect.hpp"

namespace disp
{

	void line(vec2 begin, vec2 end, int co = 0xffffff, size_t width = 1);

	void fill_rect(rect<double> r, int co = 0xffffff);
	void border_rect(rect<double> r, int co = 0xffffff, size_t width = 1);

}
