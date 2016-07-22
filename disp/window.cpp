#include "window.hpp"

#include "core/except.hpp"

#include <sfml/window.hpp>

namespace disp
{

	window::window(const char* name)
		: sf_win(sf::VideoMode(window::width, window::height), name, sf::Style::close)
	{
		if(instance != 0) {
			throw except("Cannot create more than 1 instance of disp::window");
		}
		instance = this;
	}

	window::~window
	{
		instance = 0;
	}

	void window::loop()
	{
		rt::loop();
		sf_win.display();
	}
	
}
