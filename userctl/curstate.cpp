#include "curstate.hpp"

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

	bool keystate::pressed()
	{
		if(bound_key == button::none) {
			return false;
		}
		
		return sf::isButtonPressed(bound_button);
	}

}
