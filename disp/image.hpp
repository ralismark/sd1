#pragma once

#include <string>
#include <sfml/graphics/image.hpp>

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

}
