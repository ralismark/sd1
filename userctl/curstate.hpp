#pragma once

#include "core/runtime.hpp"
#include "cursor.hpp"

namespace userctl
{

	class curstate
	{
	public: // Statics
	private: // Vars
		button bound_button;
	public: // Methods
		curstate(button b = button::none);

		void rebind(button b);

		void unbind();

		virtual bool pressed();
	};

}
