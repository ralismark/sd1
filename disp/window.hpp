#pragma once

#include <sfml/window.hpp>
#include "core/runtime.hpp"

namespace disp
{

	// Singleton, we won't have multiple windows
	class window
	{
	public: // Statics
		enum struct event // About the window only
		{
			close,

			lose_focus,
			gain_focus,

			enum_max
		};

		static const size_t width;
		static const size_t height;

		static window* instance; // One and only instance
	public: // Vars
		sf::Window sf_win;
		sig<int> win_events; // Sends window::event
	public: // Methods
		window(const char* name); // Will throw if more than 1 is made
		void loop();
		~window();
	};
	window stdwin = "Main Window";

}
