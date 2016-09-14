#include "image.hpp"

#include <stdexcept>
#include <sfml/graphics/sprite.hpp>

#include "window.hpp"

namespace disp
{

	image* image::load(std::string path)
	{
		image* res = new image();
		if(res->resource.loadFromFile(path)) {
			return res;
		} else {
			delete res;
			return 0;
		}
	}

	void image::free(image* res)
	{
		delete res;
	}

	image::pix_ref::pix_ref(image* p, size_t x, size_t y, int v)
		: parent(p), offset(make_vec<size_t>(x, y)), value(v)
	{ ; }

	image::pix_ref::~pix_ref()
	{
		parent->resource.setPixel(offset->x, offset->y, as_color(value));
	}

	int image::pix_ref::operator=(const int& v)
	{
		return value = v;
	}

	image::pix_ref::operator int()
	{
		return value;
	}

	image::image()
		: resource()
	{ ; }

	image::image(size_t x, size_t y)
		: resource()
	{
		resource.create(x, y, as_color(0xff000000));
	};

	image::image(const sf::Image& img)
		: resource(img)
	{ ; }

	image::pix_ref image::operator()(size_t x, size_t y)
	{
		return {this, x, y, as_int_color(resource.getPixel(x, y))};
	}

	int image::operator()(size_t x, size_t y) const
	{
		return as_int_color(resource.getPixel(x, y));
	}

	vec2i image::size() const
	{
		auto sz = resource.getSize();
		return make_vec<int>(sz.x, sz.y);
	}

	image::operator sf::Image&()
	{
		return resource;
	}

	texture* texture::load(const image& img, rect<size_t> region)
	{
		sf::Rect<int> area = { region->x1, region->y1, region->w, region->h };

		texture* res = new texture();
		if(res->resource.loadFromImage(img.resource, area)) {
			return res;
		} else {
			delete res;
			return 0;
		}
	}

	void texture::free(texture* res)
	{
		delete res;
	}

	texture::texture()
	{
		resource.setSmooth(false);
		resource.setRepeated(true);
	}

	texture::texture(const image& img, rect<size_t> region)
		: texture() // default settings
	{
		sf::Rect<int> area = { region->x1, region->y1, region->w, region->h };

		if(!resource.loadFromImage(img.resource, area)) {
			throw std::runtime_error("Could not load image");
		}
	}

	texture::texture(const sf::Texture& tex)
		: resource(tex)
	{
		resource.setSmooth(false);
		resource.setRepeated(true);
	}

	vec2i texture::size() const
	{
		auto sz = resource.getSize();
		return make_vec<int>(sz.x, sz.y);
	}

	texture::operator sf::Texture&()
	{
		return resource;
	}

	void draw_texture(const texture& tex, vec2 p, vec2 scale)
	{
		p = as_scr_coords(p);

		sf::Sprite sprite;

		sprite.setTexture(tex.resource);
		sprite.setPosition(p->x, p->y);
		sprite.setScale(scale->x, scale->y);

		stdwin->draw(sprite);
	}

	void draw_texture(const texture& tex, rect<double> area)
	{
		draw_texture(tex, area->min, area->size / tex.size().cast<double>());
	}

}
