#include "font.hpp"

namespace disp
{

	fontface fontface::load(std::string path)
	{
		sf::Font font;
		if(font.loadFromFile(path)) {
			return fontface(font);
		} else {
			// Change to throw?
			return fontface();
		}
	}

	fontface::fontface()
		: font()
	{ ; }

	fontface::fontface(const sf::Font& res)
		: font(res)
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
