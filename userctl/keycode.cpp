#include "keycode.hpp"

#include <cctype>

namespace userctl
{

	// NOTE: not all characters are accepted
	//       inval characters evaluate to key::unknown
	key to_keycode(char keychar)
	{
		switch(keychar) {

			// Don't worry, I didn't do this manually
			// It's like this since strongly-typed enums are strongly typed
			// Also since I broke my keyboard (haha)
		case 'a': case 'A': return key::a;
		case 'b': case 'B': return key::b;
		case 'c': case 'C': return key::c;
		case 'd': case 'D': return key::d;
		case 'e': case 'E': return key::e;
		case 'f': case 'F': return key::f;
		case 'g': case 'G': return key::g;
		case 'h': case 'H': return key::h;
		case 'i': case 'I': return key::i;
		case 'j': case 'J': return key::j;
		case 'k': case 'K': return key::k;
		case 'l': case 'L': return key::l;
		case 'm': case 'M': return key::m;
		case 'n': case 'N': return key::n;
		case 'o': case 'O': return key::o;
		case 'p': case 'P': return key::p;
		case 'q': case 'Q': return key::q;
		case 'r': case 'R': return key::r;
		case 's': case 'S': return key::s;
		case 't': case 'T': return key::t;
		case 'u': case 'U': return key::u;
		case 'v': case 'V': return key::v;
		case 'w': case 'W': return key::w;
		case 'x': case 'X': return key::x;
		case 'y': case 'Y': return key::y;
		case 'z': case 'Z': return key::z;

		case '0': return key::num0;
		case '1': return key::num1;
		case '2': return key::num2;
		case '3': return key::num3;
		case '4': return key::num4;
		case '5': return key::num5;
		case '6': return key::num6;
		case '7': return key::num7;
		case '8': return key::num8;
		case '9': return key::num9;

		case '[':  return key::lsqrbracket;
		case ']':  return key::rsqrbracket;
		case ';':  return key::semicolon;
		case ',':  return key::comma;
		case '.':  return key::period;
		case '\'': return key::quote;
		case '/':  return key::slash;
		case '\\': return key::backslash;
		case '`':  return key::tilde;
		case '=':  return key::equal;
		case '-':  return key::dash;
		case ' ':  return key::space;
		case '\r':
		case '\n': return key::enter;
		case '\b': return key::backspace;
		case '\t': return key::tab;
		case '\0': return key::none;

		}

		return key::unknown;
	}

}
