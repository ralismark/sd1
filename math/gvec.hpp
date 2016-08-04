#pragma once

#include <initializer_list>
#include <ostream>

namespace detail
{

	// Template Metaprogramming Mess
	// Though not as bad as utils.hpp
	template <typename T, size_t N>
	struct access
	{
		typedef access<T, 4> type;
	};

	template <typename T>
	struct access<T, 0>
	{
		struct type { };
	};

	template <typename T>
	struct access<T, 1>
	{
		struct type { T x; };
	};

	template <typename T>
	struct access<T, 2>
	{
		struct type { T x; T y; };
	};

	template <typename T>
	struct access<T, 3>
	{
		struct type { T x; T y; T z; };
	};

	template <typename T>
	struct access<T, 4>
	{
		struct type { T x; T y; T z; T w; };
	};

}

template <typename T, size_t N>
class gvec // Generic vector
{
	union {
		T vals[N]; // Internal array
		typename detail::access<T, N>::type access;
	};
public:
	gvec(T init = T());
	gvec(std::initializer_list<T> il);

	// unary
	gvec<T, N> operator+() const;
	gvec<T, N> operator-() const;

	// binary assignment ops
	gvec<T, N>& operator+=(const gvec<T, N>& other);
	gvec<T, N>& operator-=(const gvec<T, N>& other);
	gvec<T, N>& operator*=(const gvec<T, N>& other);
	gvec<T, N>& operator/=(const gvec<T, N>& other);

	// binary arithmetic ops
	gvec<T, N> operator+(gvec<T, N> other) const;
	gvec<T, N> operator-(gvec<T, N> other) const;
	gvec<T, N> operator*(gvec<T, N> other) const;
	// Implementation issues, division is NOT commutative
	template <typename T, size_t N>
	friend gvec<T, N> operator/(gvec<T, N> self, const gvec<T, N>& other);

	// single value ops
	gvec<T, N>& operator*=(const T& other);
	gvec<T, N>& operator/=(const T& other);

	template <typename T, size_t N>
	friend gvec<T, N> operator*(gvec<T, N> self, const T& other);
	template <typename T, size_t N>
	friend gvec<T, N> operator*(const T& other, gvec<T, N> self);
	template <typename T, size_t N>
	friend gvec<T, N> operator/(gvec<T, N> self, const T& other);

	//    Makes no sense:
	// template <typename T, size_t N>
	// friend gvec<T, N> operator/(const T& other, gvec<T, N> self);
	bool operator==(const gvec<T, N>& other) const;
	bool operator!=(const gvec<T, N>& other) const;

	// Access
	typename detail::access<T, N>::type* operator->();
	const typename detail::access<T, N>::type* operator->() const;

	T& operator[](size_t n);
	const T& operator[](size_t n) const;

	template <typename T, size_t N>
	friend std::ostream& operator<<(std::ostream& os, const gvec<T, N>& gv);
};

template <typename O, typename... T>
gvec<O, sizeof...(T)> make_vec(T... vals);

#include "gvec.tpp"
