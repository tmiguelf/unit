//======== ======== ======== ======== ======== ======== ======== ========
///	\file
///
///	\author Tiago Freire
///
///	\copyright
///		Copyright (c) 2020 Tiago Miguel Oliveira Freire
///		
///		Permission is hereby granted, free of charge, to any person obtaining a copy
///		of this software and associated documentation files (the "Software"), to deal
///		in the Software without restriction, including without limitation the rights
///		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
///		copies of the Software, and to permit persons to whom the Software is
///		furnished to do so, subject to the following conditions:
///		
///		The above copyright notice and this permission notice shall be included in all
///		copies or substantial portions of the Software.
///		
///		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
///		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
///		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
///		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
///		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
///		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
///		SOFTWARE.
//======== ======== ======== ======== ======== ======== ======== ========

#pragma once

#include <type_traits>

#include "utils.hpp"
#include "unit_id.hpp"


namespace unit::_p
{

//check if structures have specific elements
template <typename, typename = void>
struct has_unit_id: std::false_type {};
template <typename Type>
struct has_unit_id<Type, std::enable_if_t<std::is_same_v<decltype(Type::id), const unit_id>, void>>: std::true_type {};

template <typename, typename = void>
struct has_gauge: std::false_type {};
template <typename Type>
struct has_gauge<Type, std::enable_if_t<std::is_same_v<decltype(Type::gauge), const long double>, void>>: std::true_type {};

template <typename, typename = void>
struct has_factor: std::false_type {};
template <typename Type>
struct has_factor<Type, std::enable_if_t<std::is_same_v<decltype(Type::factor), const long double>, void>>: std::true_type {};


//A measurment standard requires a gauge, and must refer to a specific physical property
template<typename T>
concept c_standard = has_unit_id<T>::value && has_gauge<T>::value;

//A multiplier just needs to a value that can multiply
template<typename T>
concept c_mutiplier = has_factor<T>::value;

template <typename, typename>
struct less;

template<typename>
struct invert;

//======== ======== Dimension Handling ======== ========

/// \brief Represents a dimension, requires a standard and a non-zero rank
template <c_standard Standard, int8_t Rank>
class dimension
{
public:
	using standard_t = Standard;
	static constexpr unit_id		id			= standard_t::id;
	static constexpr int8_t			rank		= Rank;
	static constexpr long double	base_gauge	= standard_t::gauge;
	static constexpr long double	factor		= pow(base_gauge, rank);

	static_assert(Rank != 0, "Rank must not be 0");
};

//
template <template <c_standard, int8_t> typename Template, typename>
struct is_dimension_like : public std::false_type {};
template <template <c_standard, int8_t> typename Template, typename T1, int8_t V1>
struct is_dimension_like<Template, Template<T1, V1>> : public std::true_type{};

template<typename T>
using is_dimension = is_dimension_like<dimension, T>;

/// \brief used to detect things that are not dimensions
template<typename T>
struct not_dimension
{
	static constexpr bool value = !is_dimension<T>::value;
};

template<typename T>
concept c_dimension = is_dimension<T>::value;

//----
template <c_dimension T, c_dimension U>
struct less<T, U>: std::conditional_t<
	(T::id == U::id) ? (T::base_gauge < U::base_gauge) : (T::id < U::id)
	, std::true_type, std::false_type>
{};

//======== Dimension transformations ========
template<c_dimension T>
struct invert<T>
{
	using type = dimension<typename T::standard_t, -T::rank>;
};

template<c_dimension T>
struct standardize
{
	using type = dimension<typename standard::SI_standard<T::id>::type, T::rank>;
};


//======== ======== Scalar Handling ======== ========
/// \brief Represents a scalar, requires a multiplier and a non-zero power
template <c_mutiplier Scalar, int8_t Power>
class scalar
{
	using scalar_t = Scalar;
	static constexpr int8_t			power		= Power;
	static constexpr long double	base_factor	= scalar_t::factor;
	static constexpr long double	factor		= pow(base_factor, power);

	static_assert(Power != 0, "Power must not be 0");
};


template <template <c_mutiplier, int8_t> typename Template, typename>
struct is_scalar_like : public std::false_type {};
template <template <c_mutiplier, int8_t> typename Template, c_mutiplier T1, int8_t V1>
struct is_scalar_like<Template, Template<T1, V1>> : public std::true_type{};

template<typename T>
using is_scalar = is_scalar_like<scalar, T>;

/// \brief used to detect things that are not scalar
template<typename T>
struct not_scalar
{
	static constexpr bool value = !is_scalar<T>::value;
};

template<typename T>
concept c_scalar = is_scalar<T>::value;

//----
template <c_scalar T, c_scalar U>
struct less<T, U>: std::conditional_t<
	(T::base_factor < U::base_factor)
	, std::true_type, std::false_type>
{};

//======== scalar transformations ========
template<c_scalar T>
struct invert<T>
{
	using type = scalar<typename T::scalar_t, -T::power>;
};


//======== ======== Common to dimensions and scalars ======== ========

template<typename T>
struct get_factor { static constexpr long double get() { return T::factor; }};

} //namespace unit::_p
