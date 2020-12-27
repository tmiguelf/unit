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

#include "unit_type.hpp"

namespace unit::_p
{

template <typename, typename = void>
struct has_offset: std::false_type {};
template <typename Type>
struct has_offset<Type, std::enable_if_t<std::is_same_v<decltype(Type::offset), const long double>, void>>: std::true_type {};

template <typename, typename = void>
struct has_standard: std::false_type {};
template <typename Type>
struct has_standard<Type, std::enable_if_t<is_standard_v<typename Type::standard_t>, void>>: std::true_type {};

template<typename T>
concept c_proxy_property = has_factor<T>::value;

template<c_ValidFP Type, c_proxy_property Property>
class Unit_proxy
{
public:
	using value_t		= Type;
	using prop_t		= Property;
	using standard_t	= Property::standard_t;
	using unit_pack_t	= unit_pack<std::tuple<dimension<standard_t, 1>>, std::tuple<>>;

public:
	static constexpr long double offset() { return Property::offset; }

public:

	inline constexpr Unit_proxy(): m_value{} {}
	inline constexpr Unit_proxy(const Unit_proxy&) = default;

	inline constexpr Unit_proxy(value_t p_value)
		: m_value{p_value}
	{}

	template<c_ValidFP Type2, c_unit_pack Pack2> requires
		c_interchangeable_unit_pack<unit_pack_t, typename Unit<Type2, Pack2>::unit_pack>
	inline constexpr Unit_proxy(const Unit<Type2, Pack2>& p_other)
		: m_value{p_other.value() - offset()}
	{}

	template<c_ValidFP Type2, c_unit_pack Pack2> requires
		c_weak_compatible_unit_pack<unit_pack_t, typename Unit<Type2, Pack2>::unit_pack>
	inline constexpr Unit_proxy(const Unit<Type2, Pack2>& p_other)
		: m_value{metric_conversion<Type, unit_pack_t, Pack2>(p_other.value()) - offset()}
	{}

	template<c_ValidFP Type2, c_proxy_property Prop2> requires (std::is_same_v<Property, Prop2>)
	inline constexpr Unit_proxy(const Unit_proxy<Type2, Prop2>& p_other)
		: m_value{static_cast<value_t>(p_other.value())}
	{}

	template<c_ValidFP Type2, c_proxy_property Prop2> requires
		(!std::is_same_v<Property, Prop2> && (Property::standard_t::id == Prop2::standard_t::id))
	inline constexpr Unit_proxy(const Unit_proxy<Type2, Prop2>& p_other)
		: Unit_proxy(p_other.to_unit())
	{}

	//---- Operators ----
	inline Unit_proxy& operator = (const Unit_proxy& p_other) = default;

	inline Unit_proxy& operator += (const Unit<value_t, unit_pack_t>& p_other)
	{
		m_value += p_other.value();
		return *this;
	}

	inline Unit_proxy& operator -= (const Unit<value_t, unit_pack_t>& p_other)
	{
		m_value -= p_other.value();
		return *this;
	}

	template<c_ValidFP Type2, c_unit_pack Pack2> requires
		c_interchangeable_unit_pack<unit_pack_t, typename Unit<Type2, Pack2>::unit_pack>
	inline constexpr auto operator + (const Unit<Type2, Pack2>& p_other) const
	{
		using vtype = decltype(std::declval<Type>() + std::declval<Type2>());
		return Unit_proxy<vtype, Property>{m_value + p_other.value()};
	}

	template<c_ValidFP Type2, c_unit_pack Pack2> requires
		c_weak_compatible_unit_pack<unit_pack_t, typename Unit<Type2, Pack2>::unit_pack>
	inline constexpr auto operator + (const Unit<Type2, Pack2>& p_other) const
	{
		return to_unit() + p_other;
	}

	template<c_ValidFP Type2, c_unit_pack Pack2> requires
		c_interchangeable_unit_pack<unit_pack_t, typename Unit<Type2, Pack2>::unit_pack>
	inline constexpr auto operator - (const Unit<Type2, Pack2>& p_other) const
	{
		using vtype = decltype(std::declval<Type>() - std::declval<Type2>());
		return Unit_proxy<vtype, Property>{m_value - p_other.value()};
	}

	template<c_ValidFP Type2, c_unit_pack Pack2> requires
		c_weak_compatible_unit_pack<unit_pack_t, typename Unit<Type2, Pack2>::unit_pack>
	inline constexpr auto operator - (const Unit<Type2, Pack2>& p_other) const
	{
		return to_unit() - p_other;
	}

	inline constexpr Unit<value_t, unit_pack_t> operator - (const Unit_proxy& p_other) const
	{
		return m_value + offset() - p_other.m_value;
	}

	template<c_ValidFP Type2, c_proxy_property Prop2> requires (std::is_same_v<Property, Prop2>)
	inline constexpr auto operator - (const Unit_proxy<Type2, Prop2>& p_other) const
	{
		using vtype = decltype(std::declval<Type>() - std::declval<Type2>());
		return Unit<vtype, unit_pack_t>{m_value - p_other.m_value};
	}

	template<c_ValidFP Type2, c_proxy_property Prop2> requires
		(!std::is_same_v<Property, Prop2> && (Property::standard_t::id == Prop2::standard_t::id))
	inline constexpr auto operator - (const Unit_proxy<Type2, Prop2>& p_other) const
	{
		return to_unit() - p_other;
	}

	inline constexpr bool operator <  (const Unit_proxy& p_other) const { return m_value <  p_other.value(); }
	inline constexpr bool operator >  (const Unit_proxy& p_other) const { return m_value >  p_other.value(); }
	inline constexpr bool operator <= (const Unit_proxy& p_other) const { return m_value <= p_other.value(); }
	inline constexpr bool operator >= (const Unit_proxy& p_other) const { return m_value >= p_other.value(); }
	inline constexpr bool operator == (const Unit_proxy& p_other) const { return m_value == p_other.value(); }
	inline constexpr bool operator != (const Unit_proxy& p_other) const { return m_value != p_other.value(); }

	inline constexpr operator Unit<value_t, unit_pack_t>() const
	{
		return m_value + offset();
	}

	inline constexpr Unit<value_t, unit_pack_t> to_unit() const { return operator Unit<value_t, unit_pack_t>(); }
	inline constexpr value_t value() const { return m_value; }

private:
	value_t m_value;
};


} //namespace unit::_p
