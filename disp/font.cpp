#include "font.hpp"

#include "window.hpp"

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

	fontface::operator sf::Font&()
	{
		return resource;
	}

	text_style::text_style(std::shared_ptr<fontface> ff)
		: style(styles::regular), size(30), font(ff), color(0xffffff)
	{ ; }

	text_style::text_style(fontface* ff, size_t sz, styles st, int co)
		: style(st), size(sz), font(ff), color(co & 0xffffff)
	{ ; }

	text_style::operator sf::Text() const
	{
		sf::Text t;

		t.setFont(*font);
		t.setCharacterSize(size);

		t.setStyle(static_cast<unsigned int>(style));

		// 0xaarrggbb
		t.setColor(as_color(color));

		return t;
	}

	vec2 draw_text(const text_style& ts, vec2 p, const char* str)
	{
		sf::Text t = ts;
		t.setString(str);
		t.setPosition(p->x, p->y);

		auto loc = t.getLocalBounds();
		vec2 out = { loc.left + loc.width, loc.top + loc.height };

		stdwin->draw(t);

		return out;
	}

}
