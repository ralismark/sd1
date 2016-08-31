#pragma once

#include <sfml/graphics/renderwindow.hpp>
#include <sfml/graphics/color.hpp>

#include "core/runtime.hpp"
#include "userctl/keycode.hpp"
#include "userctl/cursor.hpp"

namespace disp
{

	// Singleton, we won't have multiple windows
	class window
	{
	public: // Statics
		enum struct win_event
		{
			close,

			lose_focus,
			gain_focus,

			enum_max
		};

		enum struct kbd_event
		{
			key_down,
			key_up,

			enum_max
		};

		enum struct cur_event
		{
			button_down,
			button_up,

			enum_max
		};

		static const size_t width = 1024;
		static const size_t height = 600;

		static window* instance; // One and only instance
	public: // Vars
		sf::RenderWindow sf_win;

		sig<window::win_event> win_events; // Sends window::event
		sig<window::kbd_event, userctl::key> kbd_events;
		sig<window::cur_event, userctl::button> cur_events;

		bool open;
	public: // Methods
		window(const char* name); // Will throw if more than 1 is made
		~window();

		void loop();
		void dispatch(); // Sends events
		void close();

		bool is_open();

		operator sf::RenderWindow&();
		sf::RenderWindow* operator->();
	};

	extern window stdwin;

	sf::Color as_color(int argb);
	int as_int_color(sf::Color co);

}
