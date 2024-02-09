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

#include "metric_type.hpp"
#include "dimension.hpp"
#include "utils.hpp"
#include "metric_pack.hpp"

namespace unit::_p
{

template<c_ValidFP Type, c_proxy_property Property>
class Unit_proxy;


template<c_ValidFP Type, c_unit_pack Pack>
class Unit
{
public:
	using value_t = Type;
	using unit_pack = Pack;

public:
	inline constexpr Unit(): m_value{} {}
	inline constexpr Unit(const Unit&) = default;
	
	inline explicit constexpr Unit(value_t p_value)
		: m_value{p_value}
	{}

	template<c_ValidFP Type2, c_unit_pack Pack2> requires
		c_interchangeable_unit_pack<unit_pack, typename Unit<Type2, Pack2>::unit_pack>
	inline constexpr Unit(const Unit<Type2, Pack2>& p_other)
		: m_value{static_cast<value_t>(p_other.value())}
	{}

	template<c_ValidFP Type2, c_unit_pack Pack2> requires
		c_weak_compatible_unit_pack<unit_pack, typename Unit<Type2, Pack2>::unit_pack>
	inline constexpr Unit(const Unit<Type2, Pack2>& p_other)
		: m_value{metric_conversion<Type, unit_pack, Pack2>(p_other.value())}
	{}

	template<c_ValidFP Type2, c_proxy_property Prop2> requires
		(is_compatible_unit_pack<unit_pack, typename Unit_proxy<Type2, Prop2>::unit_pack_t>::value)
	inline constexpr Unit(const Unit_proxy<Type2, Prop2>& p_other)
		: Unit(p_other.to_unit())
	{}

	//---- Operators ----
	inline Unit& operator = (const Unit&) = default;

	template<c_ValidFP Type2, c_proxy_property Prop2> requires
		(is_compatible_unit_pack<unit_pack, typename Unit_proxy<Type2, Prop2>::unit_pack_t>::value)
	inline Unit& operator = (const Unit_proxy<Type2, Prop2>& p_other)
	{
		return operator = (p_other.to_unit());
	}

	inline Unit& operator += (const Unit& p_other)
	{
		m_value += p_other.value();
		return *this;
	}

	inline Unit& operator -= (const Unit& p_other)
	{
		m_value -= p_other.value();
		return *this;
	}

	template<_p::c_arithmethic Type2>
	inline Unit& operator *= (Type2 p_val)
	{
		m_value *= p_val;
		return *this;
	}

	template<_p::c_arithmethic Type2>
	inline Unit& operator /= (Type2 p_val)
	{
		m_value /= p_val;
		return *this;
	}

	inline constexpr Unit operator + (const Unit& p_other) const
	{
		return Unit{m_value + p_other.value()};
	}

	template <c_ValidFP Type2, c_unit_pack Pack2> requires
		c_interchangeable_unit_pack<unit_pack, typename Unit<Type2, Pack2>::unit_pack>
	inline constexpr auto operator + (const Unit<Type2, Pack2>& p_other) const
	{
		using vtype = decltype(std::declval<Type>() + std::declval<Type2>());
		return Unit<vtype, Pack>{m_value + p_other.value()};
	}

	template <c_ValidFP Type2, c_unit_pack Pack2> requires
		c_weak_compatible_unit_pack<unit_pack, typename Unit<Type2, Pack2>::unit_pack>
	inline constexpr auto operator + (const Unit<Type2, Pack2>& p_other) const
	{
		using vtype = decltype(std::declval<Type>() + std::declval<Type2>());
		return Unit<vtype, Pack>{m_value + metric_conversion<vtype, unit_pack, Pack2>(p_other.value())};
	}

	inline constexpr Unit operator - (const Unit& p_other) const
	{
		return Unit{m_value - p_other.value()};
	}

	template <c_ValidFP Type2, c_unit_pack Pack2> requires
		c_interchangeable_unit_pack<unit_pack, typename Unit<Type2, Pack2>::unit_pack>
	inline constexpr auto operator - (const Unit<Type2, Pack2>& p_other) const
	{
		using vtype = decltype(std::declval<Type>() - std::declval<Type2>());
		return Unit<vtype, Pack>{m_value - p_other.value()};
	}

	template <c_ValidFP Type2, c_unit_pack Pack2> requires
		c_weak_compatible_unit_pack<unit_pack, typename Unit<Type2, Pack2>::unit_pack>
	inline constexpr auto operator - (const Unit<Type2, Pack2>& p_other) const
	{
		using vtype = decltype(std::declval<Type>() - std::declval<Type2>());
		return Unit<vtype, Pack>{m_value - metric_conversion<vtype, unit_pack, Pack2>(p_other.value())};
	}

	template<c_arithmethic Type2>
	inline constexpr auto operator * (Type2 p_val) const
	{
		return Unit<decltype(m_value * p_val), unit_pack>{m_value * p_val};
	}

	template<c_ValidFP Type2, c_unit_pack Pack2>
	inline constexpr auto operator * (const Unit<Type2, Pack2>& p_other) const
	{
		auto result = metric_multiply<Pack, Pack2>(m_value, p_other.value());
		using out_t = typename decltype(result)::type;
		if constexpr(is_unit_pack_v<out_t>)
		{
			return Unit<decltype(result.m_result), out_t>{result.m_result};
		}
		else
		{
			return result.m_result;
		}
	}

	template<c_arithmethic Type2>
	inline constexpr auto operator / (Type2 p_val) const
	{
		return Unit<decltype(m_value / p_val), unit_pack>{m_value / p_val};
	}

	template<c_ValidFP Type2, c_unit_pack Pack2>
	inline constexpr auto operator / (const Unit<Type2, Pack2>& p_other) const
	{
		auto result = metric_divide<Pack, Pack2>(m_value, p_other.value());
		using out_t = typename decltype(result)::type;
		if constexpr(is_unit_pack_v<out_t>)
		{
			return Unit<decltype(result.m_result), out_t>{result.m_result};
		}
		else
		{
			return result.m_result;
		}
	}


	inline constexpr bool operator <  (const Unit& p_other) const { return m_value <  p_other.value(); }
	inline constexpr bool operator >  (const Unit& p_other) const { return m_value >  p_other.value(); }
	inline constexpr bool operator <= (const Unit& p_other) const { return m_value <= p_other.value(); }
	inline constexpr bool operator >= (const Unit& p_other) const { return m_value >= p_other.value(); }
	inline constexpr bool operator == (const Unit& p_other) const { return m_value == p_other.value(); }
	inline constexpr bool operator != (const Unit& p_other) const { return m_value != p_other.value(); }

	inline constexpr Unit operator -() const { return Unit{-m_value}; }
	inline constexpr value_t value() const { return m_value; }


	//TODO: Figure out how to implement this taking into consideration proper type promotion
#if 0
	inline Unit& operator %= (const Unit& p_other)
	{
		m_value %= p_other.value();
		return *this;
	}

	inline constexpr Unit operator % (const Unit& p_other) const
	{
		return m_value % p_other.value();
	}

	template <c_ValidFP Type2, c_unit_pack Pack2> requires
		c_interchangeable_unit_pack<unit_pack, typename Unit<Type2, Pack2>::unit_pack>
		inline constexpr auto operator % (const Unit<Type2, Pack2>& p_other) const
	{
		using vtype = decltype(std::declval<Type>() / std::declval<Type2>());
		return Unit<vtype, Pack>{m_value % p_other.value()};
	}

	template <c_ValidFP Type2, c_unit_pack Pack2> requires
		c_weak_compatible_unit_pack<unit_pack, typename Unit<Type2, Pack2>::unit_pack>
		inline constexpr auto operator % (const Unit<Type2, Pack2>& p_other) const
	{
		using vtype = decltype(std::declval<Type>() / std::declval<Type2>());
		return Unit<vtype, Pack>{m_value % metric_conversion<vtype, unit_pack, typename std::remove_cvref_t<decltype(p_other)>::unit_pack>(p_other.value())};
	}
#endif

private:
	value_t m_value;
};

template <c_arithmethic valueL_t, c_ValidFP valueR_t, c_unit_pack Pack2>
constexpr auto operator * (valueL_t p_left, const Unit<valueR_t, Pack2>& p_right)
{
	return p_right * p_left;
}

template <c_arithmethic valueL_t, c_ValidFP valueR_t, c_unit_pack Pack2>
constexpr auto operator / (valueL_t p_left, const Unit<valueR_t, Pack2>& p_right)
{
	using val_t	= decltype(p_left / p_right.value());
	using dim2	= typename inverse_tuple_pack<typename Pack2::dimension_pack>::type;
	using scal2	= typename inverse_tuple_pack<typename Pack2::scalar_pack>::type;

	return Unit<val_t, unit_pack<dim2, scal2>>{p_left / p_right.value()};
}







}	//namespace unit::_p


namespace unit
{

template<_p::c_ValidFP Type, _p::c_tuple Dimensions, _p::c_tuple Scalars>
struct make_unit
{
private:
	static_assert(!_p::tuple_find<_p::not_dimension, Dimensions>::value, "Dimension pack can only contain dimensions");
	static_assert(!_p::tuple_find<_p::not_scalar, Scalars>::value, "Scalar pack can only contain scalars");

	using sorted_dim	= typename _p::tuple_selection_sort<_p::less, Dimensions>::type;
	using sorted_scal	= typename _p::tuple_selection_sort<_p::less, Scalars>::type;

public:
	using type = _p::Unit<Type, _p::unit_pack<sorted_dim, sorted_scal>>;
};

} //namespace unit
