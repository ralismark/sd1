#pragma once

#include <ostream>

template <typename T>
class tree
{
public: // Statics
	typedef T value_type;

	typedef T& reference;
	typedef const T& const_reference;

	typedef T* pointer;
	typedef const T* const_pointer;

	struct tree_node {
		T value;

		tree_node* parent;
		tree_node* first_child, *last_child;
		tree_node* prev_sibling, *next_sibling;

		// Makeshift optional
		tree_node(const T& init);
	};

	class pre_iterator
	{
	public:
		tree_node* node;

		pre_iterator() = delete;
		pre_iterator(tree_node* init);

		T& operator*() const;
		T* operator->() const;

		bool operator==(const pre_iterator& other) const;
		bool operator!=(const pre_iterator& other) const;

		pre_iterator operator++();
		pre_iterator operator--();
		pre_iterator operator++(int);
		pre_iterator operator--(int);

		operator tree_node*() const;
	};

	class const_pre_iterator
	{
	public:
		const tree_node* node;

		const_pre_iterator() = delete;
		const_pre_iterator(const tree_node* init);
		const_pre_iterator(const pre_iterator& it);

		const T& operator*() const;
		const T* operator->() const;

		bool operator==(const const_pre_iterator& other) const;
		bool operator!=(const const_pre_iterator& other) const;

		const_pre_iterator operator++();
		const_pre_iterator operator--();
		const_pre_iterator operator++(int);
		const_pre_iterator operator--(int);

		operator const tree_node*() const;
	};

	typedef pre_iterator iterator;
	typedef const_pre_iterator const_iterator;
private: // Variables
	tree_node head; // Head is the root of all nodes
	tree_node tail; // Pseudo-node for eof

	static const tree_node* next_node(const tree_node* node);
	static tree_node* next_node(tree_node* node);

	static const tree_node* prev_node(const tree_node* node);
	static tree_node* prev_node(tree_node* node);
public: // Methods
	tree(T val = T()); // Initalize head
	tree(const tree_node& node);
	// tree(const tree_node*& node);

	~tree(); // Destructor

	tree(const tree<T>& other); // Copy
	tree(tree<T>&& other); // Move
	tree<T>& operator=(const tree<T>& other); // Copy assign
	tree<T>& operator=(tree<T>&& other); // Move assign

	// Iterators
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	// Info
	size_t size_of(const_iterator it) const;
	size_t size() const; // Total nodes
	size_t depth_of(const_iterator it) const; // Distance from head, head is 0
	size_t child_count(const_iterator it) const;

	// Modifications
	void set_head(T val);
	iterator reparent(const iterator& dst, const iterator& src); // add src's children to dst's children
	iterator hide_children(const iterator& node);
	tree_node* transfer(); // hides own tree, moves out head

	// Deletion
	void clear();
	iterator erase(const iterator& node); // Deletes subtree, returns next item
	void erase_children(const iterator& node); // Deletes all children

	// Insertion
	iterator prepend_child(const iterator& pos, tree_node val);
	iterator append_child(const iterator& pos, tree_node val);

	iterator insert_before(const iterator& pos, tree_node val);
	iterator insert_after(const iterator& pos, tree_node val);

	// Tree ops
	tree<T> extract_node(const_iterator pos) const;

	// Debug
	bool verify() const; // true if fine

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const tree<T>& tree);

	operator tree_node() const;
};

#include "tree.tpp"
