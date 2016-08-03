#include "os_api.hpp"

#include <iostream>
#include <windows.h>
#include <conio.h>

std::system_error os_lasterr()
{
	int last_err = GetLastError();

	char* msg = 0;
	if(FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		0 /*ignored*/, last_err, 0, (char*)(&msg), 0, 0) == 0) {
		msg = 0;
	}

	std::error_code ec = { last_err, std::system_category() };
	std::system_error err = { ec, msg ? msg : "(unknown)" };

	if(msg != 0) {
		HeapFree(GetProcessHeap(), 0, msg);
	}

	return err;
}

void hit_prompt()
{
	std::clog << "\nPress any key to continue.\n";
	_getch();
}

