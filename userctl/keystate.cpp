#include "keystate.hpp"

#include <keyboard.hpp>
#include "core/except.hpp"

namespace userctl
{

	keystate::keystate(key keycode)
		: bound_key(keycode)
	{ ; }

	keystate::keystate(char keychar)
		: bound_key(to_keycode(keychar))
	{
		if(bound_key == key::unknown) {
			throw except("cannot convert `%c' to keycode", keychar);
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
			throw except("cannot convert `%c' to keycode", keychar);
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
