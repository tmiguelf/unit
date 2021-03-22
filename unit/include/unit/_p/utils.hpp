//======== ======== ======== ======== ======== ======== ======== ========
///	\file
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
#include <tuple>
#include <vector>

namespace unit::_p
{

// \brief used to check if tuple like template is of a specific template type
template <template <typename...> typename Template, typename>
struct is_tuple_like : public std::false_type {};
template <template <typename...> typename Template, typename ...Type>
struct is_tuple_like<Template, Template<Type...>> : public std::true_type{};

// \brief supported value types
template<typename T>
concept c_ValidFP = std::is_floating_point_v<T> && !std::is_const_v<T>;

template<typename T>
concept c_arithmethic = std::is_arithmetic_v<T>;

template<typename T>
concept c_tuple = is_tuple_like<std::tuple, T>::value;

template<typename T>
constexpr bool is_tuple_empty_v = std::tuple_size_v<T> == 0;

//======== ======== tuple utilities ======== ========

/// \brief Gets the end of a tuple
template<uintptr_t StartIndex, c_tuple Tuple>
struct sub_tuple
{
private:
	static constexpr uintptr_t tuple_size = std::tuple_size_v<Tuple>;

	template<typename Acumulated = std::tuple<>, uintptr_t Index = StartIndex>
	static constexpr auto sub()
	{
		if constexpr(Index < tuple_size)
		{
			using NthType = typename std::tuple_element<Index, Tuple>::type;
			return sub<decltype(std::tuple_cat(std::declval<Acumulated>(), std::declval<std::tuple<NthType>>())), Index + 1>();
		}
		else
		{
			return Acumulated{};
		}
	}
public:
	using type = decltype(sub());
};


/// \brief Transforms all types in a tuple in acordance to a transformation template
/// \tparam Transformation - Transformation template
/// \tparam Tuple - tuple to transform
template<template <typename> typename Transformation, c_tuple Tuple>
struct tuple_transform
{
private:
	static constexpr uintptr_t tuple_size = std::tuple_size_v<Tuple>;

	template<typename Acumulated = std::tuple<>, uintptr_t Index = 0>
	static constexpr auto transform()
	{
		if constexpr(Index < tuple_size)
		{
			using NthType = typename std::tuple_element<Index, Tuple>::type;
			using tr_Type = typename Transformation<NthType>::type;
			return transform<decltype(std::tuple_cat(std::declval<Acumulated>(), std::declval<std::tuple<tr_Type>>())), Index + 1>();
		}
		else
		{
			return Acumulated{};
		}
	}
public:
	using type = decltype(transform());
};

/// \brief Checks if any of the types in the tuple satisfies the Predicate
template<template <typename> typename Predicate, c_tuple Tuple>
struct tuple_find
{
private:
	static constexpr uintptr_t tuple_size = std::tuple_size_v<Tuple>;

	template<uintptr_t Index = 0>
	static constexpr bool find()
	{
		if constexpr(Index < tuple_size)
		{
			if constexpr (Predicate<std::tuple_element_t<Index, Tuple>>::value)
			{
				return true;
			}
			else
			{
				return find<Index + 1>();
			}
		}
		else
		{
			return false;
		}
	}

public:
	static constexpr bool value = find();
};

/// \brief Multiplies elements in a tuple
template<template <typename> typename Getter, c_tuple Tuple>
struct tuple_multiply
{
private:
	static constexpr uintptr_t tuple_size = std::tuple_size_v<Tuple>;

	template<uintptr_t Index = 0>
	static constexpr long double result()
	{
		if constexpr(Index < tuple_size)
		{
			constexpr long double this_v = Getter<std::tuple_element_t<Index, Tuple>>::get();
			return result<Index + 1>() * this_v;
		}
		else
		{
			return 1.l;
		}
	}

public:
	static constexpr long double value = result();
};

//======== ======== tuple selection sort ======== ========

template <std::uintptr_t i, std::uintptr_t j, c_tuple Tuple>
struct tuple_element_swap
{
private:
	template <class IndexSequence>
	struct tuple_element_swap_impl;

	template <std::uintptr_t... indices>
	struct tuple_element_swap_impl<std::index_sequence<indices...>>
	{
		using type = std::tuple<std::tuple_element_t<indices != i && indices != j ? indices : indices == i ? j : i, Tuple>...>;
	};

public:
	using type = typename tuple_element_swap_impl<std::make_index_sequence<std::tuple_size<Tuple>::value>>::type;
};

template <template <typename, typename> typename Comparator, c_tuple Tuple>
struct tuple_selection_sort
{
private:
	template <std::uintptr_t i, std::uintptr_t j, std::uintptr_t tuple_size, c_tuple LoopTuple>
	struct tuple_selection_sort_impl
	{
		using tuple_type = std::conditional_t<
			Comparator<
				std::tuple_element_t<i, LoopTuple>, std::tuple_element_t<j, LoopTuple>
			>::value,
			LoopTuple,
			typename tuple_element_swap<i, j, LoopTuple>::type
		>;

		using type = typename tuple_selection_sort_impl<i, j + 1, tuple_size, tuple_type>::type;
	};

	template <std::uintptr_t i, std::uintptr_t tuple_size, c_tuple LoopTuple>
	struct tuple_selection_sort_impl<i, tuple_size, tuple_size, LoopTuple>
	{
		using type = typename tuple_selection_sort_impl<i + 1, i + 2, tuple_size, LoopTuple>::type;
	};

	template <std::uintptr_t j, std::uintptr_t tuple_size, c_tuple LoopTuple>
	struct tuple_selection_sort_impl<tuple_size, j, tuple_size, LoopTuple>
	{
		using type = LoopTuple;
	};

public:
	using type = typename tuple_selection_sort_impl<0, 1, std::tuple_size<Tuple>::value, Tuple>::type;
};


/// \brief checks if types in a tuple are strictly sorted (i.e sorted with no repeated elements)
template <template <typename, typename> typename Comparator, c_tuple Tuple>
struct is_tuple_strictly_sorted
{
private:
	static constexpr uintptr_t tuple_size = std::tuple_size_v<Tuple>;

	template<uintptr_t Index = 0>
	static constexpr bool check()
	{
		if constexpr(Index + 1 < tuple_size)
		{
			if constexpr (Comparator<std::tuple_element_t<Index, Tuple>, std::tuple_element_t<Index + 1, Tuple>>::value)
			{
				return check<Index + 1>();
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
public:
	static constexpr bool value = check();
};


//======== ======== compile time pow ======== ========

constexpr long double cpow(long double p_val, int8_t p_power)
{
	//static_assert(std::is_constant_evaluated());

	if(p_power > 0)
	{
		return cpow(p_val, p_power - 1) * p_val;
	}
	else if(p_power < 0)
	{
		return cpow(p_val, p_power + 1) / p_val;
	}
	return 1.l;
}

consteval long double pow(long double p_val, int8_t p_power) { return cpow(p_val, p_power); }

}
