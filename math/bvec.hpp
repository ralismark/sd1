#pragma once

#include "gvec.hpp"

#include <initializer_list>
#include <functional>

template <typename T, size_t N>
class bvec
{
	union {
		T vals[4];
		typename detail::access<T, N>::type access;
	};
	std::function<T(void)> src[N];
public:
	bvec(std::function<T(void)> init = nullptr);
	bvec(std::initializer_list<std::function<T(void)>> il);

	const typename detail::access<T, N>::type* operator->() const;
	T operator[](size_t n) const;

	void rebind(size_t i, std::function<T(void)> upd = nullptr);

	gvec<T, N> operator+() const;
	
	operator gvec<T, N>() const;
};

#ifndef NO_INC_BVEC_CPP
#include "bvec.cpp"
#else
#undef NO_INC_BVEC_CPP
#endif
