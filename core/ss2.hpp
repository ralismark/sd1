#pragma once

#include <functional>
#include <utility>
#include <map>
#include <string>

template <typename... T>
class sig
{
public: // statics
	typedef void (fn_type)(T...);

	// id and parent
	typedef std::pair<std::string, void*> slot_id;
	typedef std::function<fn_type> slot_type;

	// ensures signals are never emitted to dead slots
	class slot_guard
	{
		typedef sig<T...> sig_type;
	private: // variables
		static unsigned int id_cnt;

		slot_type slot;
		sig_type* sig;
		slot_id con;

		void new_con();
	public:
		slot_guard(slot_type fn, sig_type* tgt = 0);
		template <typename C>
		slot_guard(C& obj, void (C::*fn)(T...), sig_type* tgt = 0);

		~slot_guard();

		// no copy
		slot_guard(const slot_guard&) = delete;
		slot_guard& operator=(const slot_guard&) = delete;

		void connect(sig_type* tgt); // handles null well
		void connect(sig_type& tgt);
		void disconnect();

		sig_type* get_signal() const;

		// Kills connection without going through sig
		// This should ONLY be used with dead signals
		// Live connections cannot be ended after cut
		// All of the lines go to the same column  :)
		//
		// tl;dr: Only use in emergencies!
		void cut();
	};
private: // variables
	unsigned int id_cnt = 1; // no zero
	// auto-gen funcs have "?auto{id_cnt}"
	std::map<slot_id, slot_type> slotlist;

	std::string auto_id();
public: // methods

	// auto-gen id's
	slot_id connect(slot_type slot); // functions
	template <typename C>
	slot_id connect(C& obj, void (C::*slot)(T...)); // member functions

	// user specify id
	slot_id connect(slot_id, slot_type slot); // specify special id
	slot_id connect(std::string name, slot_type slot); // function
	template <typename C>
	slot_id connect(std::string name, C& obj, void (C::*slot)(T...)); // member functions

	// dcon, return whether actually removed
	bool disconnect(slot_id slot);
	bool disconnect(std::string name); // non-member
	template <typename C>
	bool disconnect(std::string name, C& obj); // member

	void disconnect_all();

	slot_type get_slot(slot_id) const;
	slot_type get_slot(std::string name) const;
	template <typename C>
	slot_type get_slot(std::string name, C& obj);

	void emit(T... args);
	void operator()(T... args);
};
