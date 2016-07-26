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
		: font(fontface::load(path))
	{ ; }

	text_style::text_style(size_t sz, fontface* ff, styles st, unsigned color co)
		: size(sz), style(st), color(co & 0xffffff), font(ff)
	{ ; }

	unsigned short text_style::set_color(int r, int g, int b) {
		return color = ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff)
	}

	void set_font(fontface* ff)
	{
		font = ff;
	}

}
