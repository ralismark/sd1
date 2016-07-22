#pragma once

class refcount
{
protected:
	size_t* refnum;

	virtual void end_ref(); // When refnum reaches 0
public:
	refcount();

	refcount(const refcount& ref);
	refcount(refcount&& ref);

	refocunt& operator=(const refcount& ref);
	refocunt& operator=(refcount&& ref);

	~refcount();
};
