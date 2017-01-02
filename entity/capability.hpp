#pragma once

#include "predecl.hpp"

#include <cstdint>

// properties of an entity
// intended to be inherited

/* list of event id's:
 * 0x0000 - core rt signal e.g. frame
 *      0 - frame
 *      1 - frame_early
 *      2 - frame_late
 *      3 - render
 *      4 - post_render
 *      5 - frame_end
 *
 * 0x0101 - post-step
 *      0 - own step
 *      1 - region step
 *
 * 0x0102 - collision
 *      passes other object or parent if hitting region bounds
 */

class cap
{
public: // statics
public: // variables
	entity* const parent; // cannot change to point to something else
public: // methods
	cap(entity* owner = nullptr);
	virtual ~cap() = default; // default, for OO

	virtual bool filter(int id) const; // filters events to responder, defaults to accept all
	virtual void responder(int id, uintptr_t data) = 0;
};
