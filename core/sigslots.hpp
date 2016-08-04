#pragma once

#include <functional>
#include <set>

template <typename... T>
class sig
{
public: // Statics
	// Needed so that two functions are comparable easier
	class fn
	{
	public: // Statics
		typedef void (fn_type)(T...);
		static unsigned long long id_cnt; // Differentiates member funtions
	private: // Privates
		// Mess needed for comparisons
		void* parent; // Owner of member function, null mean none
		fn_type* func; // Use for function pointer
		unsigned long long id;

		std::function<fn_type> call; // What actually is called
	public:
		fn() = delete;
		fn(fn_type* fun); // non-member function
		template <typename C>
		fn(C& obj, void (C::*fun)(T...)); // member function
		fn(std::function<fn_type> fun); // functors

		bool owned_by(void* obj) const; // Compare with parent

		void operator()(T... args) const; // calls callable

		bool operator<(const fn& other) const;
	};

	typedef fn slot_type;
	typedef void (slot_func)(T...);
	typedef typename std::set<slot_type>::iterator slot_id;

	static const slot_id no_id; // Intentionally default initalised
	static const slot_type no_slot;

	// Helper functions
	// Converts functions to std::function
	static slot_type to_slot(slot_func* slot);
	template <typename C>
	static slot_type to_slot(C& obj, void (C::*slot)(T...));
private: // Privates
	std::set<slot_type> slots;
public: // Publics

	// Connects slot
	// Slot will receive future signals
	slot_id connect(const slot_type& slot); // Functors
	slot_id connect(slot_func* slot); // Non-member functions
	template <typename C>
	slot_id connect(C& obj, void (C::*slot)(T...)); // Member functions
	slot_id connect(std::function<slot_func> func); // Functors

	// Disconnects slot
	// Slot will no longer receive signals
	void disconnect(slot_id slot); // From created slot
	void disconnect(slot_type slot); // From slot object
	void disconnect(slot_func* slot); // From non-member function
	template <typename C>
	void disconnect(C& obj); // All for an object

	// this->disconnect() for all slots
	void disconnect_all();

	// Gets slot id if found, otherwise sig::no_id;
	slot_id get_id(slot_type slot) const;
	slot_id get_id(slot_func* slot) const;

	// Get slot object from an id
	slot_type get_slot(slot_id slot) const;

	// Send signal
	void emit(T... args);

	// Alias for emit
	void operator()(T... args); 
};

// Ensures that the signal never emits to a dead slot
template <typename... T>
class slot_guard
{
public: // Statics
	typedef sig<T...> sig_type;
	typedef void (slot_func)(T...);
	typedef typename sig_type::slot_type slot_type;

	typedef typename std::set<slot_type>::iterator slot_id;
private: // Privates
	slot_type slot;

	sig<T...>* sig;
	slot_id con;

	void connect(sig_type* new_sig); // Handles nulls without breaking
public: // Publics
	slot_guard() = delete; // Must construct witl slot

	slot_guard(slot_type slot_init, sig_type* sig_init = 0);
	slot_guard(slot_func* slot_init, sig_type* sig_init = 0);
	template <typename C>
	slot_guard(C& obj, void (C::*slot_init)(T...), sig_type* sig_init = 0);
	slot_guard(std::function<slot_func> func, sig_type* sig_init = 0);

	slot_guard(const slot_guard&) = delete; // No copying!

	~slot_guard(); // Disconnects from signal

	// Connect/Reconnect
	void connect(sig_type& new_sig);
	// Disconnect
	void disconnect();

	// Kills connection without going through sig
	// This should ONLY be used with dead signals
	// Live connections cannot be ended after cut
	// All of the lines here go to the same width
	//
	// tl;dr: Only use in emergencies!
	void cut();
};

#include "sigslots.tpp"
