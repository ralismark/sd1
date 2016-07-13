#include "keyinput.hpp"

#include <keyboard.hpp>

namespace userctl
{

	keyinput::keyinput(key keycode)
		: keystate(keycode), was_pressed(false), is_pressed(false)
	{ ; }

	keyinput::keyinput(char keychar)
		: keystate(keychar), was_pressed(false), is_pressed(false)
	{ ; }

	void keyinput::update()
	{
		was_pressed = is_pressed;
		is_pressed = keystate::pressed();
	}

	void keyinput::update()
	{
		is_pressed = keystate::pressed();
	}

	bool keyinput::moved_down()
	{
		return !was_pressed && is_pressed;
	}

	bool keyinput::moved_up()
	{
		return was_pressed && !is_pressed;
	}

	bool keyinput::moved()
	{
		return was_pressed != is_pressed;
	}

	bool keyinput::pressed()
	{
		return is_pressed;
	}

}
