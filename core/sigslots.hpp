#pragma once

#include <functional>
#include <set>

template <typename... T>
class sig
{
public: // Statics
	typedef void (slot_func)(T...);
	typedef std::function<slot_func> slot_type;
	typedef typename std::set<slot_type>::iterator slot_id;
	
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
	slot_id connect(slot_func* slot); // Non-member functions
	template <typename C>
	slot_id connect(C& obj, slot_func* slot); // Member functions
	slot_id connect(slot_type slot); // Functors

	// Disconnects slot
	// Slot will no longer receive signals
	void disconnect(slot_id slot);
	void disconnect(slot_type slot);
	void disconnect(slot_func* slot);
	template <typename C>
	void disconnect(C& obj, slot_func* slot);

	// this->disconnect() for all slots
	void disconnect_all();

	// Checks if certain slot is connected
	bool is_connect(void (*slot)(T...)) const; // Non-member functions
	template <typename C>
	bool is_connect(C& obj, void (*slot)(T...)) const; // Member functions
	bool is_connect(slot_type slot) const; // Functors

	// Send signal
	void emit(T... args) const;

	// Alias for emit
	void operator()(T... args) const; 
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
