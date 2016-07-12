#pragma once

#include "keystate.hpp"

namespace userctl
{
	class keyinput : public keystate {
	public: // Statics
	private: // Vars
		bool was_pressed;
		bool is_pressed;
	public:
		keyinput(keystate::key keycode = keystate::key::none);
		keystate(char keychar);

		// get new state, update was_pressed
		void update();
		// get new state, do not update was_pressed
		void extend();

		// became pressed
		bool moved_down();
		// becane released
		bool moved_up();
		// up or down
		bool moved();

		// Is pressed
		virtual bool pressed();
	};
}
