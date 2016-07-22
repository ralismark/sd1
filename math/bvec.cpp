#include "bvec.hpp"

#include <stdexcept>

template <typename T, size_t N>
bvec<T, N>::bvec(std::function<T(void)> init)
{
	for(size_t i = 0; i < N; ++i) {
		src[i] = init;
	}
}

template <typename T, size_t N>
bvec<T, N>::bvec(std::initializer_list<std::function<T(void)>> il)
{
	auto it = il.begin();
	for(size_t i = 0; i < il.size() && i < N; ++i) {
		src[i] = *it++;
	}
}

template <typename T, size_t N>
const typename detail::access<T, N>::type* bvec<T, N>::operator->() const
{
	for(size_t i = 0; i < N && i < 4; ++i) {
		if(src[i] == nullptr) {
			vals[i] = T();
		} else {
			vals[i] = src[i]();
		}
	}
	return &access;
}

template <typename T, size_t N>
T bvec<T, N>::operator[](size_t n) const
{
	if(src[n] == nullptr) {
		return T();
	} else {
		return src[n]();
	}
}

template <typename T, size_t N>
void bvec<T, N>::rebind(size_t i, std::function<T(void)> upd)
{
	src[i] = upd;
}

template <typename T, size_t N>
bvec<T, N>::operator gvec<T, N>() const
{
	gvec<T, N> ret;
	for(size_t i = 0; i < N; ++i) {
		ret[i] = (*this)[i];
	}
	return ret;
}

int main()
{
	bvec<int, 2> v1 = std::function<int(void)>([]() -> int { return 1; });
	gvec<int, 2> v2;
	v2 += v1;
	v2[1] = v1[0];
	v1.rebind(1, [](){ return 2; });
	v2[0] = v1->x;
}
