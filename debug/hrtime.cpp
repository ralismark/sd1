#include "hrtime.hpp"

#include "os_api.hpp"
#include <windows.h>

namespace hr
{

	count_t time()
	{
		LARGE_INTEGER time;
		if(!QueryPerformanceCounter(&time)) {
			throw os_lasterr();
		}
		return time.QuadPart;
	}

	count_t res()
	{
		LARGE_INTEGER res;
		if(!QueryPerformanceFrequency(&res)) {
			throw os_lasterr();
		}
		return res.QuadPart;
	}

}
