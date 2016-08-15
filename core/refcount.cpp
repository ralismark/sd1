#include "refcount.hpp"

void refcount::end_ref()
{ ; }

refcount::refcount()
	: refnum(new size_t(1))
{ ; }

refcount::refcount(const refcount& ref)
	: refnum(ref.refnum)
{
	++*refnum;
}

refcount::refcount(refcount&& ref)
	: refnum(ref.refnum)
{
	ref.refnum = 0;
}

refcount& refcount::operator=(const refcount& ref)
{
	if(&ref != this) {
		this->~refcount();
		refnum = ref.refnum;
		++*refnum;
	}
	return *this;
}

refcount& refcount::operator=(refcount&& ref)
{
	if(&ref != this) {
		this->~refcount();
		refnum = ref.refnum;
		ref.refnum = 0;
	}
	return *this;
}

refcount::~refcount()
{
	if(refnum != 0) {
		--*refnum;
		if(*refnum == 0) {
			delete refnum;
			refnum = 0;
			this->end_ref();
		}
	}
}
