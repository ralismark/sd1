#pragma once

namespace userctl
{
	class keystate
	{
	public: // Statics
		enum struct key {
			none = -2,
			unknown = -1,

			a = 0,
			b, c, d, e, f,
			g, h, i, j, k,
			l, m, n, o, p,
			q, r, s, t, u,
			v, w, x, y, z,

			num0, num1, num2,
			num3, num4, num5,
			num6, num7, num8,
			num9,

			escape,

			lctrl, lshift, lalt, lsys,
			rctrl, rshift, ralt, rsys,

			menu,

			lsqrbracket,
			rsqrbracket,
			semicolon,
			comma,
			period,
			quote,
			slash,
			backslash,
			tilde,
			equal,
			dash,

			space,
			enter,
			backspace,
			tab,
			pageup,
			pagedown,
			end,
			home,
			insert,
			del,

			// Not the same as plus, minus, star and slash
			add, subtract, multiply, divide,

			left, right, up, down,

			numpad0, numpad1, numpad2,
			numpad3, numpad4, numpad5,
			numpad6, numpad7, numpad8,
			numpad9,

			f1, f2, f3,
			f4, f5, f6,
			f7, f8, f9,
			f10, f11, f12,
			f13, f14, f15,

			pause,

			enum_max
		};

		static keystate::key to_keycode(char keychar);
	private: // Vars
		keystate::key key;
	public: // Methods
		keystate(keystate::key keycode = keystate::key::none);
		keystate(char keychar);

		void rebind(keystate::key keycode);
		void rebind(char keychar);

		void unbind();

		virtual bool pressed();
	};
}
