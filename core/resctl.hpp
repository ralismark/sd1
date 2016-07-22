#pragma once

template <typename Val, typename Key>
class res_ctl
{
public: // Statics
	struct res_entry
	{
		std::shared_ptr<Val> res;
		
		// size_t footprint; // For memory consumption limiting
		int prio; // Custom value
		res_entry(Val* init, int plevel = 0);

		bool operator<(const res_entry& other);
	};

	struct hdl
	{
		std::shared_ptr<Val> res;

		res_hdl(res_entry init);
	};
private:
	std::map<Key, res_entry> holder;
protected: // For inherited class
	virtual Val* load(Key id) const = 0; // Loads resource specified by val, we assume that it's never 0
	virtual void free(Val* res) const = 0; // Frees a resource
public:
	void preload(Key id);
	res_hdl retrieve(Key id);

	bool in_use(Key id) const;

	void unload(Key id); // Explicit unload if possible
	void cleanup(int n); // 0 means all, >0 is low prio items, <0 is high prio items
};
