#pragma once

#include <memory>
#include <map>

template <typename Val, typename Key>
class res_ctl
{
public: // Statics
	struct res_entry
	{
		std::shared_ptr<Val> res;
		
		// size_t footprint; // For memory consumption limiting
		int prio; // Custom value
		res_entry(Val* init = 0, int plevel = 0);

		bool operator<(const res_entry& other);
	private:
		static void noop(Val*); // For shared_ptr 'destructor'
	};

private:
	std::map<Key, res_entry> holder;
protected: // For inherited class
	virtual Val* load(Key id) const = 0; // Loads resource specified by val, we assume 0 is error
	virtual void free(Val* res) const = 0; // Frees a resource
public:
	~res_ctl();

	void preload(Key id);
	std::shared_ptr<Val> retrieve(Key id);

	bool in_use(Key id) const;

	void unload(Key id); // Explicit unload if possible
	void cleanup(int n = 0); // 0 means all, >0 is low prio items, <0 is high prio items
};

#ifndef NO_INC_RESCTL_CPP
#include "resctl.cpp"
#else
#undef NO_INC_RESCTL_CPP
#endif
