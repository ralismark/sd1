#include "ctl.hpp"

template <typename Val, typename Key>
res_ctl<Val, Key>::res_entry::res_entry(Val* init, int plevel)
	: res(init), prio(plevel)
{ ; }

template <typename Val, typename Key>
bool res_ctl<Val, Key>::res_entry::operator<(const res_entry& other)
{
	if(prio != other.prio) {
		return prio < other.prio;
	} else {
		return res < other.res; //  Arbitrary relation
	}
}

template <typename Val, typename Key>
res_ctl<Val, Key>::hdl::hdl(res_entry init)
	: res(init.res)
{ ; }

template <typename Val, typename Key>
void res_ctl<Val, Key>::preload(Key id)
{
	if(!holder.count(id)) {
		Val* r = this->load(id);
		holder[id] = r;
	}
}

template <typename Val, typename Key>
typename res_ctl<Val, Key>::hdl res_ctl<Val, Key>::retrieve(Key id)
{
	this->preload(id);
	return holder[id];
}

template <typename Val, typename Key>
bool res_ctl<Val, Key>::in_use(Key id) const
{
	if(!holder.count(id)) {
		return false;
	}
	return holder[id].res.unique();
}

template <typename Val, typename Key>
void res_ctl<Val, Key>::unload(Key id)
{
	if(!this->in_use(id) && holder.count(key)) { // If no longer used
		this->free(holder[id].res.get());
		holder.erase(id);
	}
}

template <typename Val, typename Key>
void res_ctl<Val, Key>::cleanup(int n)
{
	auto it  = n >= 0 ? holder.begin() : holder.rbegin();
	auto end = n >= 0 ? holder.end() : holder.rend();
	n = n > 0 ? n : -n; // Make positive

	bool use_cnt = n != 0;

	while(it != end && (!use_cnt || n != 0)) {
		if(it->res.unique()) { // Unused resources
			if(use_cnt) {
				--n;
			}
			auto ptr = it++; // Stop using invalid iterators

			this->free(ptr->res.get());
			holder.erase(ptr);
		} else {
			++it;
		}
	}
}
