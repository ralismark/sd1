#include "capability.hpp"

cap::~cap() // blank basically
{ ; }

bool cap::filter(int id) const
{
	(void)(id);
	return true;
}
