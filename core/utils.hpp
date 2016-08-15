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

#if defined(NEED_OPERATORS) && !defined(DECL_OPERATORS)
#undef NEED_OPERATORS
#define DECL_OPERATORS 1

#include <type_traits>

// Specialise enable_feature<T>::value to be true for ops
//
//   e.g. template<> struct enable_feature<T> : public std::true_type {};
//
// Based on https://www.justsoftwaresolutions.co.uk/cplusplus/using-enum-classes-as-bitfields.html

template <typename T>
struct enable_enum_cast : public std::false_type
{ };

template <typename T>
operator typename std::enable_if<enable_enum_cast<T>::value, typename std::underlying_type<T>::type>::type(T eval)
{
	return static_cast<typename std::enable_if<enable_enum_cast<T>::value, typename std::underlying_type<T>::type>::type>(eval);
}

// Bitwise ops for enums

template <typename T>
struct enable_bitwise_ops : public std::false_type
{ };

template <typename T>
typename std::enable_if<enable_bitwise_ops<T>::value, T>::type
	operator|(T left, T right)
{
	typedef typename std::underlying_type<T>::type under;
	return static_cast<T>(static_cast<under>(left) | static_cast<under>(right));
}

template <typename T>
typename std::enable_if<enable_bitwise_ops<T>::value, T>::type
	operator&(T left, T right)
{
	typedef typename std::underlying_type<T>::type under;
	return static_cast<T>(static_cast<under>(left) & static_cast<under>(right));
}

template <typename T>
typename std::enable_if<enable_bitwise_ops<T>::value, T>::type
	operator^(T left, T right)
{
	typedef typename std::underlying_type<T>::type under;
	return static_cast<T>(static_cast<under>(left) ^ static_cast<under>(right));
}

template <typename T>
typename std::enable_if<enable_bitwise_ops<T>::value, T>::type
	operator~(T left)
{
	typedef typename std::underlying_type<T>::type under;
	return static_cast<T>(~static_cast<under>(left));
}

template <typename T>
typename std::enable_if<enable_bitwise_ops<T>::value, T&>::type
	operator|=(T& left, const T& right)
{
	return left = left | right;
}

template <typename T>
typename std::enable_if<enable_bitwise_ops<T>::value, T&>::type
	operator&=(T& left, const T& right)
{
	return left = left & right;
}

template <typename T>
typename std::enable_if<enable_bitwise_ops<T>::value, T&>::type
	operator^=(T& left, const T& right)
{
	return left = left ^ right;
}

// Specialise enable_cmp_ops

template <typename T>
struct enable_cmp_ops : public std::false_type
{ };

template <typename T>
typename std::enable_if<enable_cmp_ops<T>::value, bool>::type
	operator>(const T& left, const T& right)
{
	return right < left;
}

template <typename T>
typename std::enable_if<enable_cmp_ops<T>::value, bool>::type
	operator==(const T& left, const T& right)
{
	return !(left < right || right > left);
}

template <typename T>
typename std::enable_if<enable_cmp_ops<T>::value, bool>::type
	operator!=(const T& left, const T& right)
{
	return left < right || right < left;
}

template <typename T>
typename std::enable_if<enable_cmp_ops<T>::value, bool>::type
	operator<=(const T& left, const T& right)
{
	return !(right < left);
}

template <typename T>
typename std::enable_if<enable_cmp_ops<T>::value, bool>::type
	operator>=(const T& left, const T& right)
{
	return !(left < right);
}

#endif // OPERATORS
