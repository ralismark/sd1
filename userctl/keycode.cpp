#include "keycode.cpp"

#include <cctype>

namespace userctl
{

	// NOTE: not all characters are accepted
	//       inval characters evaluate to key::unknown
	key to_keycode(char keychar)
	{
		keychar = std::tolower(keychar);

		if(std::isalpha(keychar)) {
			return key::a + (keychar - 'a');
		} else if(std::isdigit(keychar)) {
			return key::num0 + (keychar - '0');
		} else switch(keychar) {

		case '[':
			return key::lsqrbracket;
		case ']':
			return key::rsqrbracket;
		case ';':
			return key::semicolon;
		case ',':
			return key::comma;
		case '.':
			return key::period;
		case '\'':
			return key::quote;
		case '/':
			return key::slash;
		case '\\':
			return key::backslash;
		case '`':
			return key::tilde;
		case '=':
			return key::equal;
		case '-':
			return key::dash;
		case ' ':
			return key::space;
		case '\r':
		case '\n':
			return key::enter;
		case '\b':
			return key::backspace;
		case '\t':
			return key::tab;
		case '\0':
			return key::none;

		}

		return key::unknown;
	}

}
