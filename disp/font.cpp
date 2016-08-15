#include "font.hpp"

namespace disp
{

	fontface* fontface::load(std::string path)
	{
		fontface* res = new fontface();
		if(res->resource.loadFromFile(path)) {
			return res;
		} else {
			// Change to throw?
			delete res;
			return 0;
		}
	}

	void fontface::free(fontface* res)
	{
		delete res;
	}

	fontface::fontface()
		: resource()
	{ ; }

	fontface::fontface(const sf::Font& res)
		: resource(res)
	{ ; }

	fontface::fontface(std::string path)
		: fontface(fontface::load(path))
	{ ; }

	text_style::text_style(fontface* ff, size_t sz, styles st, int co)
		: style(st), size(sz), font(ff), color(co & 0xffffff)
	{ ; }

	unsigned short text_style::set_color(int r, int g, int b) {
		return color = ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
	}

	void text_style::set_font(fontface* ff)
	{
		font = ff;
	}

}
