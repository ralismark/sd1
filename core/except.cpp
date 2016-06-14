#include "except.hpp"
#include <cstdio>
#include <cstdarg>

except::except()
	: msg(dflt_msg)
{ ; }

except::except(const char* fmt, ...)
{
	va_list vl, vl_cpy;
	va_start(vl, fmt);
	va_copy(vl_cpy, vl);

	int sz = 1 + vsnprintf(0, 0, fmt, vl);
	char* str = new char[sz];
	vsnprintf(str, sz, fmt, vl_cpy);
	msg = str;
}

const char* except::what() const noexcept
{
	return msg;
}
