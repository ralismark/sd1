#include "window.hpp"

#include <stdexcept>

namespace disp
{

	window* window::instance = 0;

	window::window(const char* name)
		: sf_win(sf::VideoMode(window::width, window::height), name, sf::Style::Close)
		, open(true)
	{
		if(window::instance != 0) {
			throw std::logic_error("Cannot create more than 1 instance of disp::window");
		}
		window::instance = this;

		sf_win.setFramerateLimit(60);
		sf_win.setKeyRepeatEnabled(false);
	}

	window::~window()
	{
		this->close();
		window::instance = 0;
	}

	void window::loop()
	{
		rt::loop();
		sf_win.display();
	}

	void window::close()
	{
		sf_win.close();
		open = false;
	}

	bool window::is_open()
	{
		return open;
	}

	window::operator sf::RenderWindow&()
	{
		return sf_win;
	}

	sf::RenderWindow* window::operator->()
	{
		return &sf_win;
	}

	window stdwin = {"Main Window"};

	sf::Color as_color(int argb)
	{
		sf::Color c = {
			        (argb & (0xff << 16)) >> 16, // red
			        (argb & (0xff <<  8)) >>  8, // green
			        (argb & (0xff <<  0)) >>  0, // blue
			0xff - ((argb & (0xff << 24)) >> 24) };
		return c;
	}

	int as_int_color(sf::Color co)
	{
		int red = (co.r & 0xff) << 16;
		int green = (co.g & 0xff) << 8;
		int blue = (co.b & 0xff) << 0;
		int alpha = 0xff - ((co.a & 0xff) << 24);
		return red | green | blue | alpha;
	}

}
