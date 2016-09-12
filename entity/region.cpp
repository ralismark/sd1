#include "region.hpp"

entity* region::create()
{
	entity* obj = new entity();
	obj->parent = this;
	return this->attach(obj);
}

bool region::destroy(entity* obj)
{
	if(this->detach(obj)) {
		delete obj;
		return true;
	} else {
		return false;
	}
}

entity* region::attach(entity* obj)
{
	objects.insert(obj);
	return obj;
}

bool region::detach(entity* obj)
{
	auto it = objects.find(obj);
	if(it != objects.end()) {
		objects.erase(it);
		return true;
	} else {
		return false;
	}
}
