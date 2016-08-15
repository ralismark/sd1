#pragma once

#include "core/runtime.hpp"
#include "keycode.hpp"

namespace userctl
{

	class keystate
	{
	public: // Statics
	private: // Vars
		key bound_key;
	public: // Methods
		keystate(key keycode = key::none);
		keystate(char keychar);

		void rebind(key keycode);
		void rebind(char keychar);

		void unbind();

		virtual bool pressed() const;

		operator bool() const;
	};

}
