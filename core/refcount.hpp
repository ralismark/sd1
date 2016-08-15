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

	refcount& operator=(const refcount& ref);
	refcount& operator=(refcount&& ref);

	~refcount();
};
