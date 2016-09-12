#pragma once

#include <memory>
#include <string>
#include <sfml/graphics/image.hpp>
#include <sfml/graphics/texture.hpp>

#include "math/rect.hpp"
#include "math/vec.hpp"

namespace disp
{

	class image
	{
	public: // statics
		static image* load(std::string path); // as with fontface
		static void free(image* res);

		class pix_ref
		{
		private: // Variables
			image* parent;
			gvec<size_t, 2> offset;
			int value;
		public: // Methods
			pix_ref(image* p, size_t x, size_t y, int v);
			pix_ref(const pix_ref& other) = delete; // No copying
			pix_ref& operator=(const pix_ref& other) = delete; // No replacing

			~pix_ref(); // Sets value

			int operator=(const int& v);
			operator int();
		};
	public: // Variables
		sf::Image resource;
	public: // Methods
		image(); // blank image
		image(size_t x, size_t y); // blank image of certain size
		image(const sf::Image& img); // from existing image (copy)

		// Setting individual pixels
		// format: 0xaarrggbb, alpha is inverted (255 is transparent, 0 is opaque)
		pix_ref operator()(size_t x, size_t y);
		int operator()(size_t x, size_t y) const;

		vec2i size() const;

		operator sf::Image&();
	};

	class texture
	{
	public: // statics
		static texture* load(const image& img, rect<size_t> region = rect<size_t>()); // load subregion of image
		static void free(texture* res);
	public: // Variables
		sf::Texture resource;
	public:
		texture(); // blank
		texture(const image& img, rect<size_t> region = rect<size_t>()); // subregion
		texture(const sf::Texture& tex); // copy from existing

		vec2i size() const;

		operator sf::Texture&();
	};

	void draw_texture(const texture& tex, vec2 p, vec2 scale = {1.0, 1.0});
	void draw_texture(const texture& tex, rect<double> area);

}
