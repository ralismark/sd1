#include "window.hpp"

#include <sfml/window/event.hpp>

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

	void window::dispatch()
	{
		sf::Event event;
		while(sf_win.pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed:
				win_events(win_event::close);
				this->close();
				break;
			case sf::Event::LostFocus:
				win_events(win_event::lose_focus);
				break;
			case sf::Event::GainedFocus:
				win_events(win_event::gain_focus);
				break;

			case sf::Event::KeyPressed:
				kbd_events(kbd_event::key_down, static_cast<userctl::key>(event.key.code));
				break;
			case sf::Event::KeyReleased:
				kbd_events(kbd_event::key_up, static_cast<userctl::key>(event.key.code));
				break;

			case sf::Event::MouseButtonPressed:
				cur_events(cur_event::button_down, static_cast<userctl::button>(event.mouseButton.button));
				break;
			case sf::Event::MouseButtonReleased:
				cur_events(cur_event::button_up, static_cast<userctl::button>(event.mouseButton.button));
				break;

			default:
				; // We don't care about the other events right now
			}
		}
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

	vec2 as_scr_coords(vec2 p)
	{
		double new_y = window::height - p->y;
		return { p->x, new_y };
	}

	vec2 as_loc_coords(vec2 p)
	{
		// symmetric!
		return as_scr_coords(p);
	}

}
