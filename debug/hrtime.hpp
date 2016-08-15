#pragma once

namespace hr
{

	typedef unsigned long long count_t;

	count_t time(); // Absolute tick count
	count_t res(); // Ticks per second

}

// From https://msdn.microsoft.com/en-us/library/windows/desktop/dn553408(v=vs.85).aspx
//
//     How often does QPC roll over?
//        Not less than 100 years from the most recent system boot, and
//        potentially longer based on the underlying hardware timer used. For
//        most applications, rollover isn't a concern.
//
