#pragma once

#include <initializer_list>

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
	gvec<T, N> operator/(gvec<T, N> other) const;

	// single value ops
	gvec<T, N>& operator*=(const T& other);
	gvec<T, N>& operator/=(const T& other);

	friend gvec<T, N> operator*(gvec<T, N> self, const T& other);
	friend gvec<T, N> operator*(const T& other, gvec<T, N> self);
	friend gvec<T, N> operator/(gvec<T, N> self, const T& other);
	friend gvec<T, N> operator/(const T& other, gvec<T, N> self);

	// Access
	typename detail::access<T, N>::type* operator->();

	T& operator[](size_t n);
	const T& operator[](size_t n) const;
};
