#include "capability.hpp"

cap::cap(entity* owner)
	: parent(owner)
{ ; }

bool cap::filter(int id) const
{
	(void)(id);
	return true;
}
