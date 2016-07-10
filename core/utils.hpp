#if defined(NEED_BIND_FIRST) && !defined(DECL_BIND_FIRST)
#undef NEED_BIND_FIRST
#define DECL_BIND_FIRST 1

#include <functional>
#include <utility>

// Metaprogramming mess
// Thank you T.C for this: http://stackoverflow.com/a/26130700

template <int N>
struct placeholder { static placeholder ph; };

template <int N>
placeholder<N> placeholder<N>::ph;

namespace std {
	template<int N>
	struct is_placeholder<::placeholder<N>> : std::integral_constant<int, N> { };
}

template <typename R, typename T, typename...Types, typename U, int... indices>
std::function<R(Types...)> bind_first(std::function<R(T, Types...)> f, U val, std::integer_sequence<int, indices...> /*seq*/) {
	return std::bind(f, val, placeholder<indices + 1>::ph...);
}

template <typename R, typename T, typename...Types, typename U>
std::function<R(Types...)> bind_first(std::function<R(T, Types...)> f, U val) {
	return bind_first(f, val, std::make_integer_sequence<int, sizeof...(Types)>());
}

// Based off above stuff
// Binds instance of a class to a class method

template <typename C, typename R, typename... T, int... indices>
std::function<R(T...)> bind_instance(R (C::*f)(T...), C& obj, std::integer_sequence<int, indices...> /*seq*/)
{
	return std::bind(f, obj, placeholder<indices + 1>::ph...);
}

template <typename C, typename R, typename... T>
std::function<R(T...)> bind_instance(R (C::*f)(T...), C& obj)
{
	return bind_instance(f, obj, std::make_integer_sequence<int, sizeof...(T)>{});
}

#endif // BIND_FIRST
