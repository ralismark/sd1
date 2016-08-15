#include "curstate.hpp"

#include <sfml/window/mouse.hpp>

namespace userctl
{

	curstate::curstate(button b)
		: bound_button(b)
	{ ; }

	void curstate::rebind(button b)
	{
		bound_button = b;
	}

	void curstate::unbind()
	{
		bound_button = button::none;
	}

	bool curstate::pressed() const
	{
		if(bound_button == button::none) {
			return false;
		}
		
		return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(bound_button));
	}
	
	curstate::operator bool() const
	{
		return this->pressed();
	}

}
