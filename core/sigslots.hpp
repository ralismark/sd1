#pragma once

#include <functional>
#include <set>

template <typename... T>
class sig
{
public: // Statics
	typedef std::function<void(T...)> std_func_type;

	// Needed so that two functions are comparable easier
	class fn
	{
	public: // Statics
		typedef void (fn_type)(T...);
	private: // Privates
		// Mess needed for comparisons
		void* parent; // Owner of member function, null mean none
		fn_type* func;

		std_func_type call; // What actually is called
	public:
		fn() = delete;
		fn(fn_type* fun); // non-member function
		template <typename C>
		fn(C& obj, fn_type* fun); // member function

		void operator()(T... args) const; // calls callable

		bool operator<(const fn& other) const;
	};

	typedef fn slot_type;
	typedef void (slot_func)(T...);
	typedef typename std::set<slot_type>::iterator slot_id;
	static slot_id no_id; // Intentionally default initalised
private: // Privates
	std::set<slot_type> slots;
public: // Publics

	// Helper functions
	// Converts functions to std::function
	static slot_type to_slot(slot_func* slot);
	template <typename C>
	static slot_type to_slot(C& obj, slot_func* slot);

	// Connects slot
	// Slot will receive future signals
	slot_id connect(const slot_type& slot); // Functors
	slot_id connect(slot_func* slot); // Non-member functions
	template <typename C>
	slot_id connect(C& obj, slot_func* slot); // Member functions

	// Disconnects slot
	// Slot will no longer receive signals
	void disconnect(slot_id slot);
	void disconnect(slot_type slot);
	void disconnect(slot_func* slot);
	template <typename C>
	void disconnect(C& obj, slot_func* slot);

	// this->disconnect() for all slots
	void disconnect_all();

	// Gets slot id if found, otherwise sig::no_id;
	slot_id get_id(slot_type slot) const;
	slot_id get_id(slot_func* slot) const;
	template <typename C>
	slot_id get_id(C& obj, slot_func* slot) const;

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
	typedef std::function<slot_func> slot_type;

	typedef typename std::set<slot_type>::iterator slot_id;
private: // Privates
	slot_type slot;

	sig<T...>* sig;
	slot_id connection;
public: // Publics
	slot_guard() = delete; // Must construct witl slot

	slot_guard(slot_type init, sig_type* sig = 0);
	slot_guard(slot_func* init, sig_type* sig = 0);
	template <typename C>
	slot_guard(C& obj, slot_func* init, sig_type* sig = 0);

	~slot_guard(); // Disconnects from signal

	// Connect/Reconnect
	void connect(sig_type& sig);
	// Disconnect
	void disconnect();
};
