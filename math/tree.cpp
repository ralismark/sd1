#include "tree.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

template <typename T>
void dump_node(const typename tree<T>::tree_node& node)
{
	return;
	std::cout << '[' << node.parent << " ]" << node.value << " @" << &node << '\n';
	std::cout << "  sib: " << node.prev_sibling << " <-> " << node.next_sibling << '\n';
	std::cout << "  chl: " << node.first_child << "..." << node.last_child << '\n';
}

template <typename T>
tree<T>::tree_node::tree_node(const T& init)
	: value(init), parent(0), first_child(0), last_child(0), prev_sibling(0), next_sibling(0)
{ ; }

// pre_iterator {{{

template <typename T>
tree<T>::pre_iterator::pre_iterator(tree_node* init)
	: node(init)
{ ; }

template <typename T>
T& tree<T>::pre_iterator::operator*() const
{
	return node->value;
}

template <typename T>
T* tree<T>::pre_iterator::operator->() const
{
	return &(node->value);
}

template <typename T>
bool tree<T>::pre_iterator::operator==(const pre_iterator& other) const
{
	return node == other.node;
}

template <typename T>
bool tree<T>::pre_iterator::operator!=(const pre_iterator& other) const
{
	return node != other.node;
}

template <typename T>
typename tree<T>::pre_iterator tree<T>::pre_iterator::operator++()
{
	return node = tree<T>::next_node(node);
}

template <typename T>
typename tree<T>::pre_iterator tree<T>::pre_iterator::operator--()
{
	return node = tree<T>::prev_node(node);
}

template <typename T>
typename tree<T>::pre_iterator tree<T>::pre_iterator::operator++(int)
{
	pre_iterator copy = *this;
	++(*this);
	return copy;
}

template <typename T>
typename tree<T>::pre_iterator tree<T>::pre_iterator::operator--(int)
{
	pre_iterator copy = *this;
	--(*this);
	return copy;
}

template <typename T>
tree<T>::pre_iterator::operator tree_node*() const
{
	return node;
}

// }}}
// const_pre_iterator {{{

template <typename T>
tree<T>::const_pre_iterator::const_pre_iterator(const tree_node* init)
	: node(init)
{ ; }

template <typename T>
tree<T>::const_pre_iterator::const_pre_iterator(const pre_iterator& it)
	: node(it.node)
{ ; }

template <typename T>
const T& tree<T>::const_pre_iterator::operator*() const
{
	return node->value;
}

template <typename T>
const T* tree<T>::const_pre_iterator::operator->() const
{
	return &(node->value);
}

template <typename T>
bool tree<T>::const_pre_iterator::operator==(const const_pre_iterator& other) const
{
	return node == other.node;
}

template <typename T>
bool tree<T>::const_pre_iterator::operator!=(const const_pre_iterator& other) const
{
	return node != other.node;
}

template <typename T>
typename tree<T>::const_pre_iterator tree<T>::const_pre_iterator::operator++()
{
	return node = tree<T>::next_node(node);
}

template <typename T>
typename tree<T>::const_pre_iterator tree<T>::const_pre_iterator::operator--()
{
	return node = tree<T>::prev_node(node);
}

template <typename T>
typename tree<T>::const_pre_iterator tree<T>::const_pre_iterator::operator++(int)
{
	const_pre_iterator copy = *this;
	node = tree<T>::next_node(node);
	return copy;
}

template <typename T>
typename tree<T>::const_pre_iterator tree<T>::const_pre_iterator::operator--(int)
{
	const_pre_iterator copy = *this;
	node = tree<T>::prev_node(node);
	return copy;
}

template <typename T>
tree<T>::const_pre_iterator::operator const tree_node*() const
{
	return node;
}

// }}}
// tree - private methods {{{

template <typename T>
const typename tree<T>::tree_node* tree<T>::next_node(const tree_node* node)
{
	if(node == 0 || node->parent == 0) {
//		std::clog << "at tail\n";
		return node;
	}

//	std::clog << "at " << (node ? node->value : -1);
	if(node->first_child == 0) { // Is last node
		while(node->next_sibling == 0) { // Goes up while node is last
			node = node->parent;
			if(node->parent == 0) { // Reached tail
//				std::clog << ", up to tail\n";
				return node;
			}
//			std::clog << ", up to " << (node ? node->value : -1);
		}
		node = node->next_sibling;
//		std::clog << ", across to " << (node ? node->value : -1);
	} else { // Has children
		node = node->first_child;
//		std::clog << ", down to " << (node ? node->value : -1);
	}
//	std::clog << '\n';
	return node;
}

template <typename T>
const typename tree<T>::tree_node* tree<T>::prev_node(const tree_node* node)
{
	if(node == 0) {
		return node;
	}

	if(node->parent == 0) { // At tail
//		std::clog << "at tail";
		while(node->last_child != 0) {
			node = node->last_child;
//			std::clog << ", down to " << (node ? node->value : -1);
		}
//		std::clog << '\n';
		return node;
	}

//	std::clog << "at " << (node ? node->value : -1);
	if(node->prev_sibling == 0) { // First child
		// Previous item is parent
		node = node->parent;
//		std::clog << ", up to " << (node ? node->value : -1);
	} else { // There is a previous node
		node = node->prev_sibling; // Move to that node
//		std::clog << ", back to " << (node ? node->value : -1);
		while(node->last_child) { // Move to last child
			node = node->last_child;
//			std::clog << ", down to " << (node ? node->value : -1);
		}
	}
//	std::clog << '\n';

	return node;
}

template <typename T>
typename tree<T>::tree_node* tree<T>::next_node(tree_node* node)
{
	return const_cast<tree_node*>(tree<T>::next_node(const_cast<const tree_node*>(node)));
}

template <typename T>
typename tree<T>::tree_node* tree<T>::prev_node(tree_node* node)
{
	return const_cast<tree_node*>(tree<T>::prev_node(const_cast<const tree_node*>(node)));
}

// }}}
// tree - ctor/dtor/assign {{{

template <typename T>
tree<T>::tree(T val)
	: head(val), tail(T())
{
	head.parent = &tail;
	tail.first_child = tail.last_child = &head;
}

template <typename T>
tree<T>::tree(const tree_node& node)
	: head(node), tail(T())
{
	head.parent = &tail;
	tail.first_child = tail.last_child = &head;
}

template <typename T>
tree<T>::tree(const tree<T>& other)
	: tree(other.extract_node(other.begin())) // Calls move constructor
{ ; }

template <typename T>
tree<T>::tree(tree<T>&& other)
	: tree(other.head.value)
{
	this->reparent(&head, other.begin());
}

template <typename T>
tree<T>& tree<T>::operator=(const tree<T>& other)
{
	return *this = other.extract_node(other.begin()); // Move assign
}

template <typename T>
tree<T>& tree<T>::operator=(tree<T>&& other)
{
	if(&other != this) {
		this->clear();
		
		this->reparent(&head, &other.head);
		head.value = other.head.value;
	}
	return *this;
}

template <typename T>
tree<T>::~tree()
{
	this->clear();
}

template <typename T>
tree<T>::operator tree_node() const
{
	tree<T> copy = *this;
	tree_node node = head.value;

	copy.reparent(&node, &copy.head);

	return node;
}

// }}}
// tree - iterators {{{

template <typename T>
typename tree<T>::iterator tree<T>::begin()
{
	return &head;
}

template <typename T>
typename tree<T>::iterator tree<T>::end()
{
	return &tail;
}

template <typename T>
typename tree<T>::const_iterator tree<T>::begin() const
{
	return &head;
}

template <typename T>
typename tree<T>::const_iterator tree<T>::end() const
{
	return &tail;
}

// }}}
// tree - info {{{

template <typename T>
size_t tree<T>::size_of(const_iterator it) const
{
	size_t cnt = 1; // Original node

	// Simplified version of op++
	const_iterator end = it;
	while(end.node->next_sibling == 0 && node->parent != 0) {
		end = end.node->parent;
	}
	if(end.node->next_sibling) {
		end = end.node->next_sibling;
	}

	while(++it != end) {
		++cnt;
	}
	return cnt;
}

template <typename T>
size_t tree<T>::size() const
{
	auto it = this->begin();
	size_t cnt = 1;
	while(++it != this->end()) {
		++cnt;
	}
	return cnt;
}

template <typename T>
size_t tree<T>::depth_of(const_iterator it) const
{
	size_t cnt = 0;
	while(it.node->parent != 0) {
		++cnt;
		it = it.node->parent;
	}
	return cnt - 1;
}

template <typename T>
size_t tree<T>::child_count(const_iterator it) const
{
	if(it.node->first_child == 0) {
		return 0;
	}
	size_t cnt = 1;
	it = it.node->first_child;
	while(it.node->next_sibling != 0) {
		cnt++;
		it = it.node->next_sibling;
	}
	return cnt;
}

// }}}
// tree - modification {{{

template <typename T>
void tree<T>::set_head(T val)
{
	head.value = val;
}

template <typename T>
typename tree<T>::iterator tree<T>::reparent(const iterator& dst, const iterator& src)
{
	// Change parent
	for(tree_node* it = src.node->first_child; it != 0; it = it->next_sibling) {
		it->parent = dst.node;
	}

	if(dst.node->first_child == 0) { // dst has no children, easy sway
		dst.node->first_child = src.node->first_child;
		dst.node->last_child = src.node->last_child;
	} else { // append children
		dst.node->last_child->next_sibling = src.node->first_child;
		src.node->first_child->prev_sibling = dst.node->last_child;
		dst.node->last_child = src.node->last_child;
	}

	// Hide children from src
	this->hide_children(src);
	return dst;
}

template <typename T>
typename tree<T>::iterator tree<T>::hide_children(const iterator& node)
{
	node.node->first_child = node.node->last_child = 0;
	return node;
}

template <typename T>
typename tree<T>::tree_node* tree<T>::transfer()
{
	return this->reparent(new tree_node(head.value), &head);
}

// }}}
// tree - deletion {{{

template <typename T>
void tree<T>::clear()
{
	this->erase_children(&head);
}

template <typename T>
typename tree<T>::iterator tree<T>::erase(const iterator& node)
{
	this->erase_children(node);

	auto it = node++;

	if(it.node->prev_sibling) {
		it.node->prev_sibling->next_sibling = it.node->next_sibling;
	} else {
		it.node->parent->first_child = it.node->next_sibling;
	}
	if(it.node->next_sibling) {
		it.node->next_sibling->prev_sibling = it.node->prev_sibling;
	} else {
		it.node->parent->last_child = it.node->prev_sibling;
	}

	delete it.node;

	return node;
}

template <typename T>
void tree<T>::erase_children(const iterator& node)
{
	for(tree_node* it = node.node->first_child; it != 0; ) {
		tree_node* next = it->next_sibling;
		this->erase_children(it);
		delete it;
		it = next;
	}
	node.node->first_child = node.node->last_child = 0;
}

// }}}
// tree - insertion {{{

template <typename T>
typename tree<T>::iterator tree<T>::prepend_child(const iterator& pos, tree_node val)
{
	if(pos.node->first_child) {
		return this->insert_before(pos.node->first_child, val);
	} else { // First child
		tree_node* ins = new tree_node(val.value);
		this->reparent(ins, &val);
		pos.node->first_child = pos.node->last_child = ins;
		ins->parent = pos;
		return ins;
	}
}

template <typename T>
typename tree<T>::iterator tree<T>::append_child(const iterator& pos, tree_node val)
{
	if(pos.node->last_child) {
		return this->insert_after(pos.node->last_child, val);
	} else { // First child
		tree_node* ins = new tree_node(val.value);
		this->reparent(ins, &val);
		pos.node->first_child = pos.node->last_child = ins;
		ins->parent = pos;
		return ins;
	}
}

template <typename T>
typename tree<T>::iterator tree<T>::insert_before(const iterator& pos, tree_node val)
{
	tree_node* ins = new tree_node(val.value);
	this->reparent(ins, &val);

	ins->parent = pos.node->parent;
	ins->prev_sibling = pos.node->prev_sibling;
	ins->next_sibling = pos.node;

	if(pos.node->prev_sibling) {
		pos.node->prev_sibling->next_sibling = ins;
	} else { // First child
		pos.node->parent->first_child = ins;
	}

	pos.node->prev_sibling = ins;

	return ins;
}

template <typename T>
typename tree<T>::iterator tree<T>::insert_after(const iterator& pos, tree_node val)
{
	tree_node* ins = new tree_node(val.value);
	this->reparent(ins, &val);

	ins->parent = pos.node->parent;
	ins->next_sibling = pos.node->next_sibling;
	ins->prev_sibling = pos.node;

	if(pos.node->next_sibling) {
		pos.node->next_sibling->prev_sibling = ins;
	} else { // First child
		pos.node->parent->last_child = ins;
	}

	pos.node->next_sibling = ins;

	return ins;
}

// }}}
// tree - tree ops {{{

template <typename T>
tree<T> tree<T>::extract_node(const_iterator pos) const
{
	tree<T> new_tree = *pos;

	for(const tree_node* src = pos.node->first_child; src != 0; src = src->next_sibling) {
		new_tree.append_child(new_tree.begin(), this->extract_node(src));
	}

	return new_tree;
}

// }}}
// tree - debug {{{

template <typename T>
bool tree<T>::verify() const
{
	bool err = false;
	std::cout << "tail @0x" << &tail << ", head @0x" << &head << '\n';

	if(tail.next_sibling != tail.prev_sibling) {
		std::cout << "tail has siblings\n";
		std::cout << "prev: @0x" << tail.prev_sibling << " next: @0x" << tail.next_sibling << '\n';
		err = true;
	}
	if(tail.first_child != tail.last_child) {
		std::cout << "tail has multiple children\n";
		std::cout << "first: @0x" << tail.first_child << " last: @0x" << tail.last_child << '\n';
		err = true;
	}
	if(tail.first_child != &head) {
		std::cout << "tail's child is not head\n";
		std::cout << "actually is @0x" << tail.first_child << '\n';
		err = true;
	}
	if(head.next_sibling != head.prev_sibling) {
		std::cout << "head has siblings\n";
		std::cout << "prev: @0x" << head.prev_sibling << " next: @0x" << head.next_sibling << '\n';
		err = true;
	}
	if(head.parent != &tail) {
		std::cout << "head's parent is not tail\n";
		std::cout << "actually is @0x" << head.parent << '\n';
		err = true;
	}

	int cnt = 0;
	const_iterator it = this->begin();
	for( ; cnt < 32 && it != this->end(); ++it, ++cnt) {
		if(it.node->parent != 0) {
			bool loc_err = false;
			if(it.node->prev_sibling) {
				if(it.node->prev_sibling->next_sibling != it.node) {
					auto prev = it.node->prev_sibling;
					auto np = it.node->prev_sibling->next_sibling;
					std::cout << *it << " @0x" << it.node << ": rel to prev corrupted" << '\n';
					std::cout << "    @0x" << prev << " thinks its next_sibling is @0x" << np << '\n';
					loc_err = true;
				}
			} else {
				if(it.node->parent->first_child != it.node) {
					auto par = it.node->parent;
					auto fc = it.node->parent->first_child;
					std::cout << *it << " @0x" << it.node << ": rel to parent corrupted" << '\n';
					std::cout << "    @0x" << par << " thinks its first_child is @0x" << fc << '\n';
					loc_err = true;
				}
			}
			if(it.node->next_sibling) {
				if(it.node->next_sibling->prev_sibling != it.node) {
					auto next = it.node->next_sibling;
					auto np = it.node->next_sibling->prev_sibling;
					std::cout << *it << " @0x" << it.node << ": rel to next corrupted" << '\n';
					std::cout << "    @0x" << next << " thinks its prev_sibling is @0x" << np << '\n';
					loc_err = true;
				}
			} else {
				if(it.node->parent->last_child != it.node) {
					auto par = it.node->parent;
					auto lc = it.node->parent->last_child;
					std::cout << *it << " @0x" << it.node << ": rel to parent corrupted" << '\n';
					std::cout << "    @0x" << par << " thinks its last_child is @0x" << lc << '\n';
					loc_err = true;
				}
			}
			if(loc_err) {
				err = true;
			} else {
				std::cout << *it << " @0x" << it.node << " under " << it.node->parent->value << " @0x" << it.node->parent << " is fine\n";
			}
		} else {
			std::cout << *it << " @0x" << it.node << " has no parent!\n";
			err = true;
		}
	}
	if(it != this->end()) {
		std::cout << "got to @0x" << it.node << " instead of end: @0x" << this->end() << '\n';
		err = true;
	}
	return !err;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const tree<T>& tree)
{
	std::vector<std::string> prefix_list;

	for(auto it = tree.begin(); it.node->parent != 0; ) {
		std::string prefix;
		for(auto&& i : prefix_list) {
			prefix += i;
		}

		os << prefix << (it.node->next_sibling ? "\xc3\xc4\xc4 " : "\xc0\xc4\xc4 ") << *it << '\n';

		if(it.node->first_child) { // Go to children
			prefix_list.push_back(it.node->next_sibling ? "\xb3   " : "    ");
			it = it.node->first_child;
		} else { // Is leaf, go back
			while(it.node->next_sibling == 0) {
				it = it.node->parent;
				if(it.node->parent == 0) {
					return os; // Reached tail
				}
				prefix_list.pop_back();
			}
			it = it.node->next_sibling;
		}
	}
	return os;
}

// }}}

int main()
{
	std::cout << std::boolalpha;
	tree<int> i = 1;

	auto left = i.prepend_child(i.begin(), 2);
	i.prepend_child(left, 3);
	i.append_child(left, 4);

	auto right = i.insert_after(left, 5);
	auto tgt = i.append_child(right, 7);
	i.insert_before(tgt, 6);
	std::cout << "-----\n";

	std::cout << i << i.verify() << '\n';
	std::cout << "-----\n";
	for(tree<int>::iterator it = i.begin(); it != i.end(); ++it) { }
	for(tree<int>::iterator it = i.end(); --it != i.begin(); ) { }
	std::cout << "-----\n";

	tree<int> i2 = i.extract_node(right);

	std::cout << i2 << i2.verify() << '\n';

	std::cout << "-----\n";
	
	i.append_child(tgt, i2);
	i.append_child(tgt, i);

	std::cout << i << i.verify() << '\n';
	std::cout << "-----\n";


}
