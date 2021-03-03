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

#include "utils.hpp"
#include "dimension.hpp"

namespace unit::_p
{

/// \brief stores information about the unit
template<c_tuple Dimensions, c_tuple Scalars>
struct unit_pack
{
public:
	using dimension_pack = Dimensions;
	using scalar_pack = Scalars;

	static_assert(!tuple_find<not_dimension, dimension_pack>::value, "Dimension pack can only contain dimensions");
	static_assert(!tuple_find<not_scalar, scalar_pack>::value, "Scalar pack can only contain scalars");

	static_assert(is_tuple_strictly_sorted<less, dimension_pack>::value, "Dimension must be packed and sorted");
	static_assert(is_tuple_strictly_sorted<less, scalar_pack>::value, "Scalar must be packed and sorted");

	static_assert(std::tuple_size_v<dimension_pack> != 0, "Dimension pack must not be empty");

	static constexpr long double gauge = tuple_multiply<get_factor, dimension_pack>::value * tuple_multiply<get_factor, scalar_pack>::value;
};

template<typename T>
constexpr bool is_unit_pack_v = is_tuple_like<unit_pack, T>::value;

template<typename T>
concept c_unit_pack = is_tuple_like<unit_pack, T>::value;


/// \brief checks if 2 tuples have the same type of dimensions
template<c_tuple Pack1, c_tuple Pack2>
struct compatible_tuple_pack
{
private:
	static constexpr uintptr_t tuple1_size = std::tuple_size_v<Pack1>;
	static constexpr uintptr_t tuple2_size = std::tuple_size_v<Pack2>;

	template<uintptr_t Index = 0>
	static constexpr bool match_all()
	{
		if constexpr (Index >= tuple1_size)
		{
			return true;
		}
		else
		{
			using dim1 = std::tuple_element_t<Index, Pack1>;
			using dim2 = std::tuple_element_t<Index, Pack1>;

			if constexpr(dim1::id == dim2::id && dim1::rank == dim2::rank)
			{
				return match_all<Index + 1>();
			}
			else
			{
				return false;
			}
		}
	}

	static constexpr bool check()
	{
		if constexpr (tuple1_size == tuple2_size)
		{
			return match_all();
		}
		else
		{
			return false;
		}
	}

public:
	static constexpr bool value = check();
};


template<c_unit_pack Pack1, c_unit_pack Pack2>
using is_compatible_unit_pack = compatible_tuple_pack<typename Pack1::dimension_pack, typename Pack2::dimension_pack>;

template<typename Pack1, typename Pack2>
concept c_compatible_unit_pack = is_compatible_unit_pack<Pack1, Pack2>::value;

/// \brief packs are not only compatible, they have the same gauge
template<typename Pack1, typename Pack2>
concept c_interchangeable_unit_pack = is_compatible_unit_pack<Pack1, Pack2>::value && Pack1::gauge == Pack2::gauge;

/// \brief packs are only compatible and do not have the same gauge
template<typename Pack1, typename Pack2>
concept c_weak_compatible_unit_pack = is_compatible_unit_pack<Pack1, Pack2>::value && Pack1::gauge != Pack2::gauge;


/// \brief inverts a tuple pack with either dimension or scalar
template<c_tuple Pack>
struct inverse_tuple_pack
{
	using type = typename tuple_transform<invert, Pack>::type;
};


/// \brief Checks if 2 sorted tuples of dimensions have conflicting units
/// \warning Requires tuples to be sorted
template<c_tuple Pack1, c_tuple Pack2>
struct has_conflicting_units
{
private:
	static constexpr uintptr_t tuple1_size = std::tuple_size_v<Pack1>;
	static constexpr uintptr_t tuple2_size = std::tuple_size_v<Pack2>;

	template<uintptr_t Index1 = 0, uintptr_t Index2 = 0>
	static constexpr bool check()
	{
		if constexpr(Index1 < tuple1_size && Index2 < tuple2_size)
		{
			using type1 = typename std::tuple_element_t<Index1, Pack1>;
			using type2 = typename std::tuple_element_t<Index2, Pack2>;
			if constexpr(type1::id == type2::id)
			{
				if constexpr(std::is_same_v<typename type1::standard_t, typename type2::standard_t>)
				{
					return check<Index1 + 1, Index2 + 1>();
				}
				else
				{
					return true;
				}
			}
			else
			{
				if constexpr(type1::id < type2::id)
				{
					return check<Index1 + 1, Index2>();
				}
				else
				{
					return check<Index1, Index2 + 1>();
				}
			}
		}
		else
		{
			return false;
		}
	}

public:
	static constexpr bool value = check();
};


/// \brief Merges 2 sorted tuple lists of dimensions, assumes that there are no conflicting units
/// \warning Requires tuples to be sorted, and units must not conflict
template<c_tuple Pack1, c_tuple Pack2>
struct dimension_merge_clober
{
private:
	static constexpr uintptr_t tuple1_size = std::tuple_size_v<Pack1>;
	static constexpr uintptr_t tuple2_size = std::tuple_size_v<Pack2>;

	template<typename Acumulated = std::tuple<>, uintptr_t Index1 = 0, uintptr_t Index2 = 0>
	static constexpr auto merge()
	{
		if constexpr (Index1 < tuple1_size)
		{
			if constexpr(Index2 < tuple2_size)
			{
				using type1 = typename std::tuple_element_t<Index1, Pack1>;
				using type2 = typename std::tuple_element_t<Index2, Pack2>;

				if constexpr(type1::id == type2::id)
				{
					constexpr int8_t res_rank = type1::rank + type2::rank;
					if constexpr(res_rank == 0)
					{
						return merge<Acumulated, Index1 + 1, Index2 + 1>();
					}
					else
					{
						return merge<
							decltype(
								std::tuple_cat(std::declval<Acumulated>(),
								std::declval<std::tuple<dimension<typename type1::standard_t, res_rank>>>()))
							, Index1 + 1, Index2 + 1>();
					}
				}
				else
				{
					if constexpr(type1::id < type2::id)
					{
						return merge<
							decltype(
								std::tuple_cat(std::declval<Acumulated>(),
								std::declval<std::tuple<type1>>()))
							, Index1 + 1, Index2>();
					}
					else
					{
						return merge<
							decltype(
								std::tuple_cat(std::declval<Acumulated>(),
									std::declval<std::tuple<type2>>()))
							, Index1, Index2 + 1>();
					}
				}
			}
			else
			{
				return decltype(std::tuple_cat(std::declval<Acumulated>(), std::declval<typename sub_tuple<Index1, Pack1>::type>())){};
			}
		}
		else
		{
			if constexpr(Index2 < tuple2_size)
			{
				return decltype(std::tuple_cat(std::declval<Acumulated>(), std::declval<typename sub_tuple<Index2, Pack2>::type>())){};
			}
			else
			{
				return Acumulated{};
			}
		}
	}


public:
	using type = decltype(merge());
};


/// \brief Merges 2 sorted tuple lists of dimensions
/// \warning Requires tuples to be sorted
template<c_tuple Pack1, c_tuple Pack2>
struct dimension_merge_no_clober
{
private:
	static constexpr uintptr_t tuple1_size = std::tuple_size_v<Pack1>;
	static constexpr uintptr_t tuple2_size = std::tuple_size_v<Pack2>;

	template<typename Acumulated = std::tuple<>, uintptr_t Index1 = 0, uintptr_t Index2 = 0>
	static constexpr auto merge()
	{
		if constexpr (Index1 < tuple1_size)
		{
			if constexpr(Index2 < tuple2_size)
			{
				using type1 = typename std::tuple_element_t<Index1, Pack1>;
				using type2 = typename std::tuple_element_t<Index2, Pack2>;

				if constexpr(type1::id == type2::id && type1::base_gauge == type2::base_gauge)
				{
					constexpr int8_t res_rank = type1::rank + type2::rank;
					if constexpr(res_rank == 0)
					{
						return merge<Acumulated, Index1 + 1, Index2 + 1>();
					}
					else
					{
						return merge<
							decltype(
								std::tuple_cat(std::declval<Acumulated>(),
									std::declval<std::tuple<dimension<typename type1::standard_t, res_rank>>>()))
							, Index1 + 1, Index2 + 1>();
					}
				}
				else
				{
					if constexpr(type1::id == type2::id ? type1::base_gauge < type2::base_gauge : type1::id < type2::id)
					{
						return merge<
							decltype(
								std::tuple_cat(std::declval<Acumulated>(),
									std::declval<std::tuple<type1>>()))
							, Index1 + 1, Index2>();
					}
					else
					{
						return merge<
							decltype(
								std::tuple_cat(std::declval<Acumulated>(),
									std::declval<std::tuple<type2>>()))
							, Index1, Index2 + 1>();
					}
				}
			}
			else
			{
				return decltype(std::tuple_cat(std::declval<Acumulated>(), std::declval<typename sub_tuple<Index1, Pack1>::type>())){};
			}
		}
		else
		{
			if constexpr(Index2 < tuple2_size)
			{
				return decltype(std::tuple_cat(std::declval<Acumulated>(), std::declval<typename sub_tuple<Index2, Pack2>::type>())){};
			}
			else
			{
				return Acumulated{};
			}
		}
	}


public:
	using type = decltype(merge());
};


/// \brief Merges 2 sorted tuple lists of scalars
/// \warning Requires tuples to be sorted
template<c_tuple Pack1, c_tuple Pack2>
struct scalar_merge
{
	static constexpr uintptr_t tuple1_size = std::tuple_size_v<Pack1>;
	static constexpr uintptr_t tuple2_size = std::tuple_size_v<Pack2>;

	template<typename Acumulated = std::tuple<>, uintptr_t Index1 = 0, uintptr_t Index2 = 0>
	static constexpr auto merge()
	{
		if constexpr (Index1 < tuple1_size)
		{
			if constexpr(Index2 < tuple2_size)
			{
				using type1 = typename std::tuple_element_t<Index1, Pack1>;
				using type2 = typename std::tuple_element_t<Index2, Pack2>;

				if constexpr(type1::base_factor == type2::base_factor)
				{
					constexpr int8_t res_power = type1::power + type2::power;
					if constexpr(res_power == 0)
					{
						return merge<Acumulated, Index1 + 1, Index2 + 1>();
					}
					else
					{
						return merge<
							decltype(
								std::tuple_cat(std::declval<Acumulated>(),
									std::declval<std::tuple<scalar<typename type1::scalar_t, res_power>>>()))
							, Index1 + 1, Index2 + 1>();
					}
				}
				else
				{
					if constexpr(type1::base_factor < type2::base_factor)
					{
						return merge<
							decltype(
								std::tuple_cat(std::declval<Acumulated>(),
									std::declval<std::tuple<type1>>()))
							, Index1 + 1, Index2>();
					}
					else
					{
						return merge<
							decltype(
								std::tuple_cat(std::declval<Acumulated>(),
									std::declval<std::tuple<type2>>()))
							, Index1, Index2 + 1>();
					}
				}
			}
			else
			{
				return decltype(std::tuple_cat(std::declval<Acumulated>(), std::declval<typename sub_tuple<Index1, Pack1>::type>())){};
			}
		}
		else
		{
			if constexpr(Index2 < tuple2_size)
			{
				return decltype(std::tuple_cat(std::declval<Acumulated>(), std::declval<typename sub_tuple<Index2, Pack2>::type>())){};
			}
			else
			{
				return Acumulated{};
			}
		}
	}

public:
	using type = decltype(merge());
};


//======== ======== Conversion operations ======== ========

template<c_ValidFP value_t, c_unit_pack Pack1, c_unit_pack Pack2, c_ValidFP value_t2> requires c_compatible_unit_pack<Pack1, Pack2>
inline constexpr value_t metric_conversion(value_t2 p_t2)
{
	using dim1	= typename inverse_tuple_pack<typename Pack1::dimension_pack>::type;
	using scal1	= typename inverse_tuple_pack<typename Pack1::scalar_pack>::type;
	using dim2	= typename Pack2::dimension_pack;
	using scal2	= typename Pack2::scalar_pack;

	constexpr long double scalar_factor = tuple_multiply<get_factor, typename scalar_merge<scal2, scal1>::type>::value;
	constexpr long double conversion = tuple_multiply<get_factor, typename dimension_merge_no_clober<dim2, dim1>::type>::value * scalar_factor;

//	constexpr long double conversion = Pack2::gauge / Pack1::gauge;
	return static_cast<value_t>(p_t2 * conversion);
}


/// \brief encodes information regarding the result type of an operation
template <c_ValidFP ValueType, typename ResultType>
struct op_result_t
{
public:
	constexpr op_result_t(ValueType p_value): m_result(p_value){}
	
	ValueType m_result;

	using type = ResultType;
};

template<c_unit_pack Pack1, c_unit_pack Pack2, c_ValidFP value_t1, c_ValidFP value_t2>
inline constexpr auto metric_multiply(value_t1 p_t1, value_t2 p_t2)
{
	using dim1	= typename Pack1::dimension_pack;
	using scal1	= typename Pack1::scalar_pack;
	using dim2	= typename Pack2::dimension_pack;
	using scal2	= typename Pack2::scalar_pack;

	auto t_result = p_t1 * p_t2;
	using vtype = decltype(t_result);


	using scalar_tuple = typename scalar_merge<scal1, scal2>::type;
	constexpr long double scalar_factor = tuple_multiply<get_factor, scalar_tuple>::value;


	if constexpr(has_conflicting_units<dim1, dim2>::value)
	{
		using real_dimension_tuple = typename dimension_merge_no_clober<dim1, dim2>::type;

		constexpr long double real_gauge = tuple_multiply<get_factor, real_dimension_tuple>::value * scalar_factor;

		using result_dimension_tuple =
			typename dimension_merge_clober<
				typename tuple_transform<standardize, dim1>::type,
				typename tuple_transform<standardize, dim2>::type
			>::type;

		if constexpr(is_tuple_empty_v<result_dimension_tuple>)
		{
			return op_result_t<vtype, vtype>{static_cast<vtype>(t_result * real_gauge)};
		}
		else
		{
			return op_result_t<vtype, unit_pack<result_dimension_tuple, std::tuple<>>>{static_cast<vtype>(t_result * real_gauge)};
		}
	}
	else
	{
		using result_dimension_tuple =
			typename dimension_merge_clober<
				dim1,
				dim2
			>::type;
		if constexpr(is_tuple_empty_v<result_dimension_tuple>)
		{
			return op_result_t<vtype, vtype>{static_cast<vtype>(t_result * scalar_factor)};
		}
		else
		{
			return op_result_t<vtype, unit_pack<result_dimension_tuple, scalar_tuple>>{t_result};
		}
	}
}

template<c_unit_pack Pack1, c_unit_pack Pack2, c_ValidFP value_t1, c_ValidFP value_t2>
inline constexpr auto metric_divide(value_t1 p_t1, value_t2 p_t2)
{
	using dim1	= typename Pack1::dimension_pack;
	using scal1	= typename Pack1::scalar_pack;
	using dim2	= typename inverse_tuple_pack<typename Pack2::dimension_pack>::type;
	using scal2	= typename inverse_tuple_pack<typename Pack2::scalar_pack>::type;

	auto t_result = p_t1 / p_t2;
	using vtype = decltype(t_result);


	using scalar_tuple = typename scalar_merge<scal1, scal2>::type;
	constexpr long double scalar_factor = tuple_multiply<get_factor, scalar_tuple>::value;


	if constexpr(has_conflicting_units<dim1, dim2>::value)
	{
		using real_dimension_tuple = typename dimension_merge_no_clober<dim1, dim2>::type;

		constexpr long double real_gauge = tuple_multiply<get_factor, real_dimension_tuple>::value * scalar_factor;

		using result_dimension_tuple =
			typename dimension_merge_clober<
				typename tuple_transform<standardize, dim1>::type,
				typename tuple_transform<standardize, dim2>::type
			>::type;

		if constexpr(is_tuple_empty_v<result_dimension_tuple>)
		{
			return op_result_t<vtype, vtype>{static_cast<vtype>(t_result * real_gauge)};
		}
		else
		{
			return op_result_t<vtype, unit_pack<result_dimension_tuple, std::tuple<>>>{static_cast<vtype>(t_result * real_gauge)};
		}
	}
	else
	{
		using result_dimension_tuple =
			typename dimension_merge_clober<
				dim1,
				dim2
			>::type;
		if constexpr(is_tuple_empty_v<result_dimension_tuple>)
		{
			return op_result_t<vtype, vtype>{static_cast<vtype>(t_result * scalar_factor)};
		}
		else
		{
			return op_result_t<vtype, unit_pack<result_dimension_tuple, scalar_tuple>>{t_result};
		}
	}
}

} //namespace unit::_p
