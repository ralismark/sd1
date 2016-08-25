#pragma once

namespace disp
{

	struct fill_style {
		int co;

		fill_style(int i_co = 0xffffff);
	};

	struct edge_style {
		int co;
		size_t width;

		edge_style(int i_co = 0xffffff, size_t i_width = 1);
	};

}
