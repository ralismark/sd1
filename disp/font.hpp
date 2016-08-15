#pragma once

#include <memory>
#include <string>
#include <sfml/graphics/font.hpp>
#include <sfml/graphics/text.hpp>

#define NEED_OPERATORS
#include "core/utils.hpp"

#include "math/vec.hpp"

namespace disp
{

	class fontface
	{
	public:  // Statics
		static fontface* load(std::string path); // May change to name -> path map
		static void free(fontface* res);
	public: // Variables
		sf::Font resource;
	public:  // Methods
		fontface(); // Load default font
		fontface(const sf::Font& res); // Copy font
		// TODO: Add loading of fontfaces from memory or streams
		operator sf::Font&();
	};

	class text_style // helper with fontface for sf::Text
	{
	public: // Statics
		enum class styles {
			regular   = 0,
			bold      = 1 << 0,
			italic    = 1 << 1,
			underline = 1 << 2,

			enum_max
		};
	public: // Variables
		styles style; // bitmask
		size_t size;
		std::shared_ptr<fontface> font;
		int color; // 00rrggbb

		// About the American spelling:
		// A lot of programming stuff is designed in the US, and that
		// results in the spelling of some stuff e.g. std::initaliZer_list
		// Also, I'm used to the CSS color attribute.

	public: // Methods
		text_style(std::shared_ptr<fontface> ff);
		text_style(fontface* ff = 0, size_t sz = 30, styles st = styles::regular, int co = 0xffffff);

		operator sf::Text() const;
	};

	vec2 draw_text(const text_style& ts, vec2 p, const char* str);

}

// disp::text_style::styles is a flag enum
template<> class enable_bitwise_ops<disp::text_style::styles> : public std::true_type {};
