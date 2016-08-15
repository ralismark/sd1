#pragma once

#include "gvec.hpp"

template <typename T, size_t N>
gvec<T, N>::gvec(T init)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] = init;
	}
}

template <typename T, size_t N>
gvec<T, N>::gvec(std::initializer_list<T> il)
{
	auto it = il.begin();
	for(size_t i = 0; i < il.size() && i < N; ++i) {
		vals[i] = *it++;
	}
}

template <typename T, size_t N>
gvec<T, N> gvec<T, N>::operator+() const
{
	return *this;
}

template <typename T, size_t N>
gvec<T, N> gvec<T, N>::operator-() const
{
	auto copy = *this;
	for(size_t i = 0; i < N; ++i) {
		copy.vals[i] = -copy.vals[i];
	}
	return copy;
}

template <typename T, size_t N>
gvec<T, N>& gvec<T, N>::operator+=(const gvec<T, N>& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] += other.vals[i];
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N>& gvec<T, N>::operator-=(const gvec<T, N>& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] -= other.vals[i];
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N>& gvec<T, N>::operator*=(const gvec<T, N>& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] *= other.vals[i];
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N>& gvec<T, N>::operator/=(const gvec<T, N>& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] /= other.vals[i];
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N> gvec<T, N>::operator+(gvec<T, N> other) const
{
	return other += *this;
}

template <typename T, size_t N>
gvec<T, N> gvec<T, N>::operator-(gvec<T, N> other) const
{
	other -= *this;
	return -other;
}

template <typename T, size_t N>
gvec<T, N> gvec<T, N>::operator*(gvec<T, N> other) const
{
	return other *= *this;
}

template <typename T, size_t N>
gvec<T, N> operator/(gvec<T, N> self, const gvec<T, N>& other)
{
	return self /= other;
}

template <typename T, size_t N>
gvec<T, N>& gvec<T, N>::operator*=(const T& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] *= other;
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N>& gvec<T, N>::operator/=(const T& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] /= other;
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N> operator*(gvec<T, N> self, const T& other)
{
	return self *= other;
}

template <typename T, size_t N>
gvec<T, N> operator/(gvec<T, N> self, const T& other)
{
	return self /= other;
}

template <typename T, size_t N>
gvec<T, N> operator*(const T& other, gvec<T, N> self)
{
	return self *= other;
}

template <typename T, size_t N>
bool gvec<T, N>::operator==(const gvec<T, N>& other) const
{
	for(size_t i = 0; i < N; ++i) {
		if(vals[i] != other[i]) {
			return false;
		}
	}
	return true;
}

template <typename T, size_t N>
bool gvec<T, N>::operator!=(const gvec<T, N>& other) const
{
	return !(*this == other);
}

template <typename T, size_t N>
typename detail::access<T, N>::type* gvec<T, N>::operator->()
{
	return &access;
}

template <typename T, size_t N>
const typename detail::access<T, N>::type* gvec<T, N>::operator->() const
{
	return &access;
}

template <typename T, size_t N>
const T& gvec<T, N>::operator[](size_t n) const
{
	return vals[n];
}

template <typename T, size_t N>
T& gvec<T, N>::operator[](size_t n)
{
	return vals[n];
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const gvec<T, N>& gv)
{
	os << "[ ";
	for(size_t i = 0; i < N; ++i) {
		if(i != 0) {
			os << ", ";
		}
		os << gv[i];
	}
	os << " ]";
	return os;
}

template <typename T, size_t N>
template <typename C>
gvec<typename std::enable_if<std::is_convertible<T, C>::value, C>::type, N> gvec<T, N>::cast() const
{
	gvec<C, N> out;
	for(size_t i = 0; i < N; ++i) {
		out[i] = vals[i];
	}
	return out;
}

template <typename O, typename... T>
gvec<O, sizeof...(T)> make_vec(T... vals)
{
	gvec<O, sizeof...(T)> gv = {vals...};
	return gv;
}
