#pragma once

#include <sfml/window.hpp>
#include "core/runtime.hpp"
#include "userctl/keycode.hpp"

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

		static const size_t width = 800;
		static const size_t height = 600;

		static window* instance; // One and only instance
	public: // Vars
		sf::RenderWindow sf_win;
		sig<window::win_event> win_events; // Sends window::event
		sig<window::kbd_event> kbd_events;
	public: // Methods
		window(const char* name); // Will throw if more than 1 is made
		~window();

		void loop();
	};

	window stdwin = "Main Window";

}
