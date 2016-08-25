#include "polystyle.hpp"

namespace disp
{

	fill_style::fill_style(int i_co)
		: co(i_co)
	{ ; }

	edge_style::edge_style(int i_co, size_t i_width)
		: co(i_co), width(i_width)
	{ ; }

}
