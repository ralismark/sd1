#include "image.hpp"

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

}
