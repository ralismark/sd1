#include "geometry.hpp"

#include "window.hpp"

#include <cmath>
#include <sfml/graphics/convexshape.hpp>
#include <sfml/graphics/rectangleshape.hpp>

namespace disp
{

	void line(vec2 begin, vec2 end, int co, size_t width)
	{
		vec2 dir = end - begin;
		vec2 unit_dir = dir / std::sqrt(dir->x * dir->x + dir->y * dir->y);
		vec2 unit_perp= { -unit_dir->y, unit_dir->x };

		vec2 offset = (width / 2.0) * unit_perp;

		gvec<double, 2> vert[4];
		vert[0] = begin + offset;
		vert[1] = end + offset;
		vert[2] = end - offset;
		vert[3] = begin - offset;

		sf::Vertex vertices[4];

		sf::Color c = as_color(co);
		for(int i = 0; i < 4; ++i) {
			vertices[i].color = c;
			vertices[i].position = {vert[i]->x, vert[i]->y};
		}

		stdwin->draw(vertices, 4, sf::Quads);
	}

	void fill_rect(rect<double> r, int co)
	{
		sf::RectangleShape rs;
		rs.setSize(sf::Vector2f(r->w, r->h));
		rs.setPosition(r->x1, r->x2);

		rs.setOutlineColor(sf::Color::Transparent);
		rs.setFillColor(as_color(co));

		stdwin->draw(rs);
	}

	void border_rect(rect<double> r, int co, size_t width)
	{
		sf::RectangleShape rs;
		rs.setSize(sf::Vector2f(r->w, r->h));
		rs.setPosition(r->x1, r->x2);

		rs.setFillColor(sf::Color::Transparent);
		rs.setOutlineColor(as_color(co));

		rs.setOutlineThickness(width);

		stdwin->draw(rs);
	}

}
