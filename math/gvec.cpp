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
	return other -= *this;
}

template <typename T, size_t N>
gvec<T, N> gvec<T, N>::operator*(gvec<T, N> other) const
{
	return other *= *this;
}

template <typename T, size_t N>
gvec<T, N> gvec<T, N>::operator/(gvec<T, N> other) const
{
	return other /= *this;
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
gvec<T, N> operator/(const T& other, gvec<T, N> self)
{
	return self /= other;
}

template <typename T, size_t N>
typename detail::access<T, N>::type* gvec<T, N>::operator->()
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

int main()
{
	gvec<int, 2> v1 = 4;            // gvec(T init = T())
	gvec<int, 2> v2 = {1, 2};       // gvec(std::initializer_list<int> il)

	v1 = +v1;
	v1 = -v1;

	v1 += v2;
	v1 -= v2;
	v1 *= v2;
	v1 /= v2;

	v1 = v1 + v2;
	v1 = v1 - v2;
	v1 = v1 * v2;
	v1 = v1 / v2;
	
	v1 *= 1;
	v1 /= 1;
	v1 = 1 * v1;
	v1 = 1 * v1;

	v1[1] = v2[2];
}
