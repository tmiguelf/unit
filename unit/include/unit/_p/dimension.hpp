//======== ======== ======== ======== ======== ======== ======== ========
///	\file
///
///	\copyright
///		Copyright (c) Tiago Miguel Oliveira Freire
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

#include <cstdint>
#include <type_traits>

#include "utils.hpp"
#include "metric_type.hpp"

namespace unit::_p
{

//check if structures have specific elements
template <typename>
struct has_unit_id: std::false_type {};

template <typename Type> requires is_metric_t<typename Type::metric_t>::value
struct has_unit_id<Type>: std::true_type {};


template <typename>
struct is_valid_gauge_type: std::false_type {};

template <typename Type> requires std::is_floating_point_v<Type>
struct is_valid_gauge_type<Type>: std::true_type {};

template <typename Type>
constexpr bool is_valid_gauge_type_v = is_valid_gauge_type<Type>::value;



template <typename>
struct has_gauge: std::false_type {};

template <typename Type> requires is_valid_gauge_type_v<decltype(Type::gauge)>
struct has_gauge<Type>: std::true_type {};


template <typename>
struct has_factor: std::false_type {};

template <typename Type> requires is_valid_gauge_type_v<decltype(Type::factor)>
struct has_factor<Type>: std::true_type {};



template <typename>
struct has_offset: std::false_type {};

template <typename Type> requires is_valid_value_type_v<decltype(Type::offset)>
struct has_offset<Type>: std::true_type {};


//A measurment standard requires a gauge, and must refer to a specific physical property
template<typename T>
constexpr bool is_standard_v = has_unit_id<T>::value && has_gauge<T>::value;
template<typename T>
concept c_standard = is_standard_v<T>;

//A multiplier just needs to a value that can multiply
template<typename T>
concept c_mutiplier = has_factor<T>::value;


template <typename>
struct has_standard: std::false_type {};

template <typename Type> requires is_standard_v<typename Type::standard_t>
struct has_standard<Type>: std::true_type {};


//for biased units like Celcius or farenheit
template<typename T>
concept c_proxy_property = has_offset<T>::value && has_standard<T>::value;


template <typename, typename>
struct less;

template<typename>
struct invert;

//======== ======== Dimension Handling ======== ========

/// \brief Represents a dimension, requires a standard and a non-zero rank
template <c_standard Standard, int8_t Rank>
struct dimension
{
	using standard_t = Standard;
	using metric_t = Standard::metric_t;
	static constexpr int8_t			rank		= Rank;
	static constexpr long double	base_gauge	= standard_t::gauge;
	static constexpr long double	factor		= pow(base_gauge, rank);

	static_assert(Rank != 0, "Rank must not be 0");
};


template<typename T>
struct is_dimension: public std::false_type {};

template<typename T1, int8_t V1>
struct is_dimension<dimension<T1, V1>>: public std::true_type {};


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
struct less<T, U>: public std::conditional_t<
	//(T::id == U::id)
	compare_equal_metric_v<typename T::metric_t, typename U::metric_t>
	? (T::base_gauge < U::base_gauge) :
	compare_less_metric_v<typename T::metric_t, typename U::metric_t>
	//(T::id < U::id)
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
	using type = dimension<typename standard::SI_standard<typename T::metric_t>::type, T::rank>;
};


//======== ======== Scalar Handling ======== ========
/// \brief Represents a scalar, requires a multiplier and a non-zero power
template <c_mutiplier Scalar, int8_t Power>
struct scalar
{
	using scalar_t = Scalar;
	static constexpr int8_t			power		= Power;
	static constexpr long double	base_factor	= scalar_t::factor;
	static constexpr long double	factor		= pow(base_factor, power);

	static_assert(Power != 0, "Power must not be 0");
};


template<typename T>
struct is_scalar: public std::false_type {};

template<typename T1, int8_t V1>
struct is_scalar<scalar<T1, V1>>: public std::true_type {};


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
struct less<T, U>: public std::conditional_t<
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
struct get_factor { static constexpr auto get() { return T::factor; }};

} //namespace unit::_p
