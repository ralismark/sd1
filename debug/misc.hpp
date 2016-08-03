#pragma once

#include <iostream>

template <typename T>
void _expr(const char* str, const T& val)
{
	std::cout << str << ": " << val << '\n';
}
#define expr(e) _expr((#e), (e))

#define debugger do { std::cout << "debug marker " << __FILE__ << ':' << __LINE__ << " (in " << __func__ << ")\n"; } while(0)
