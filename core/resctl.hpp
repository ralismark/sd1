#pragma once

#include <memory>
#include <map>

/*
 *      class res_ctl
 *
 * This class is intended to facilitate the handling of resources e.g.
 * textures, etc. It does this by internally handling resources, which can be
 * accessed through its methods (preload and retrieve).
 *
 * To allow for use of any resource, this is a semi-generic base class, which
 * should be inherited with load and free overwritten to allocate and free the
 * required resource, correspondingly.
 */

template <typename Val, typename Key>
class res_ctl
{
public: // Statics
	/* completely internal class for storing values */
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

	/* */
	virtual Val* load(Key id) const = 0;
	/* frees resource from pointer */
	virtual void free(Val* res) const = 0;

	/*
	 * loads desired resource from specified key

	 * Note: it may be desirable to have a map from resource names to
	 * the actual resource location. This allows a further layer of
	 * abstraction.
	 */
public:
	/*
	 * frees all resources during destruction

	 * exception warning:
	 * if any resources are still loaded, this function WILL throw and kill
	 * the program
	 */
	~res_ctl();

	/* loads a resource prematurely, such as before a level */
	void preload(Key id);
	/* gets resource, loading if necessary */
	std::shared_ptr<Val> retrieve(Key id);

	/* checks if a resource is currently loaded and used */
	bool in_use(Key id) const;

	/* unloads a resource if not currently used */
	void unload(Key id); // Explicit unload if possible
	/* cleans up unused resources, such as after a level */
	void cleanup(int n = 0); // 0 means all, >0 is low prio items, <0 is high prio items
};

#include "resctl.tpp"
