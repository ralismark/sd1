#include "keystate.hpp"

#include <sfml/window/keyboard.hpp>
#include <stdexcept>
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
			throw std::logic_error(std::string() + "cannot convert `" + keychar + "' to keycode");
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
			throw std::logic_error(std::string() + "cannot convert `" + keychar + "' to keycode");
		}
	}

	void keystate::unbind()
	{
		bound_key = key::none;
	}

	bool keystate::pressed() const
	{
		if(bound_key == key::none) {
			return false;
		}

		return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(bound_key));
	}

	keystate::operator bool() const
	{
		return this->pressed();
	}

}
