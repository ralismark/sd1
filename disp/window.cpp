#include "window.hpp"

#include <stdexcept>

namespace disp
{

	window::window(const char* name)
		: sf_win(sf::VideoMode(window::width, window::height), name, sf::Style::Close)
	{
		if(window::instance != 0) {
			throw std::logic_error("Cannot create more than 1 instance of disp::window");
		}
		window::instance = this;
	}

	window::~window()
	{
		window::instance = 0;
	}

	void window::loop()
	{
		rt::loop();
		sf_win.display();
	}

	window::operator sf::RenderWindow&()
	{
		return sf_win;
	}

}
