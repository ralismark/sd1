#include "keystate.hpp"

#include <keyboard.hpp>
#include <string>

namespace userctl
{

	keystate::keystate(key keycode)
		: bound_key(keycode)
	{ ; }

	keystate::keystate(char keychar)
		: bound_key(to_keycode(keychar))
	{
		if(bound_key == key::unknown) {
			throw except(std::string() + "cannot convert `" + keychar + "' to keycode");
		}
	}

	void keystate::rebind(key keycode)
	{
		bound_key = keycode;
	}

	void keystate::rebind(char keychar)
	{
		bound_key = to_keycode(keychar);
		if(bound_key == key::unknown) {
			throw except(std::string() + "cannot convert `" + keychar + "' to keycode");
		}
	}

	void keystate::unbind()
	{
		bound_key = key::none;
	}

	bool keystate::pressed()
	{
		if(bound_key == key::none) {
			return false;
		}

		return sf::Keyboard::isKeyPressed(bound_key);
	}

}
