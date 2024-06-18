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

#include "utils.hpp"
#include "dimension.hpp"

#include "metric_type.hpp"

namespace unit::_p
{

/// \brief stores information about the unit
template<core::c_pack Dimensions, core::c_pack Scalars>
struct unit_pack
{
public:
	using dimension_pack = Dimensions;
	using scalar_pack = Scalars;

	static_assert(!core::pack_contains_v<dimension_pack, not_dimension>, "Dimension pack can only contain dimensions");
	static_assert(!core::pack_contains_v<scalar_pack, not_scalar>, "Scalar pack can only contain scalars");

	static_assert(is_pack_strictly_sorted<dimension_pack, less>::value, "Dimension must be packed and sorted");
	static_assert(is_pack_strictly_sorted<scalar_pack, less>::value, "Scalar must be packed and sorted");

	static_assert(core::pack_count_v<dimension_pack> != 0, "Dimension pack must not be empty");

	static constexpr long double gauge = pack_multiply<dimension_pack, get_factor>::value * pack_multiply<scalar_pack, get_factor>::value;
};





template<typename> struct is_unit_pack : public std::false_type {};
template<typename ...Type> struct is_unit_pack<unit_pack<Type...>> : public std::true_type{};

template<typename T>
constexpr bool is_unit_pack_v = is_unit_pack<T>::value;

template<typename T>
concept c_unit_pack = is_unit_pack_v<T>;


/// \brief checks if 2 packs have the same type of dimensions
template<core::c_pack Pack1, core::c_pack Pack2>
struct compatible_pack
{
private:
	static constexpr uintptr_t pack1_size = core::pack_count_v<Pack1>;
	static constexpr uintptr_t pack2_size = core::pack_count_v<Pack2>;

	template<uintptr_t Index = 0>
	static constexpr bool match_all()
	{
		if constexpr (Index >= pack1_size)
		{
			return true;
		}
		else
		{
			using dim1 = core::pack_get_t<Pack1, Index>;
			using dim2 = core::pack_get_t<Pack1, Index>;

			if constexpr (
				compare_equal_metric_v<typename dim1::metric_t, typename dim2::metric_t>
				&& dim1::rank == dim2::rank)
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
		if constexpr (pack1_size == pack2_size)
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
using is_compatible_unit_pack = compatible_pack<typename Pack1::dimension_pack, typename Pack2::dimension_pack>;

template<typename Pack1, typename Pack2>
concept c_compatible_unit_pack = is_compatible_unit_pack<Pack1, Pack2>::value;

/// \brief packs are not only compatible, they have the same gauge
template<typename Pack1, typename Pack2>
concept c_interchangeable_unit_pack = is_compatible_unit_pack<Pack1, Pack2>::value && Pack1::gauge == Pack2::gauge;

/// \brief packs are only compatible and do not have the same gauge
template<typename Pack1, typename Pack2>
concept c_weak_compatible_unit_pack = is_compatible_unit_pack<Pack1, Pack2>::value && Pack1::gauge != Pack2::gauge;


/// \brief inverts a pack with either dimension or scalar
template<core::c_pack Pack>
struct inverse_pack
{
	using type = typename core::pack_transform<Pack, invert>::type;
};


/// \brief Checks if 2 sorted packs of dimensions have conflicting units
/// \warning Requires packs to be sorted
template<core::c_pack Pack1, core::c_pack Pack2>
struct has_conflicting_units
{
private:
	static constexpr uintptr_t pack1_size = core::pack_count_v<Pack1>;
	static constexpr uintptr_t pack2_size = core::pack_count_v<Pack2>;

	template<uintptr_t Index1 = 0, uintptr_t Index2 = 0>
	static constexpr bool check()
	{
		if constexpr (Index1 < pack1_size && Index2 < pack2_size)
		{
			using type1 = typename core::pack_get_t<Pack1, Index1>;
			using type2 = typename core::pack_get_t<Pack2, Index2>;
			if constexpr(
				compare_equal_metric_v<typename type1::metric_t, typename type2::metric_t>
				)
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
				if constexpr(
					compare_less_metric_v<typename type1::metric_t, typename type2::metric_t>
					)
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


/// \brief Merges 2 sorted pack lists of dimensions, assumes that there are no conflicting units
/// \warning Requires packs to be sorted, and units must not conflict
template<core::c_pack Pack1, core::c_pack Pack2>
struct dimension_merge_clober
{
private:
	static constexpr uintptr_t pack1_size = core::pack_count_v<Pack1>;
	static constexpr uintptr_t pack2_size = core::pack_count_v<Pack2>;

	template<typename Acumulated = core::pack<>, uintptr_t Index1 = 0, uintptr_t Index2 = 0>
	static constexpr auto merge()
	{
		if constexpr (Index1 < pack1_size)
		{
			if constexpr (Index2 < pack2_size)
			{
				using type1 = typename core::pack_get_t<Pack1, Index1>;
				using type2 = typename core::pack_get_t<Pack2, Index2>;

				if constexpr(
					compare_equal_metric_v<typename type1::metric_t, typename type2::metric_t>
					)
				{
					constexpr int8_t res_rank = type1::rank + type2::rank;
					if constexpr(res_rank == 0)
					{
						return merge<Acumulated, Index1 + 1, Index2 + 1>();
					}
					else
					{

						return merge<
							core::pack_cat_t<
								Acumulated,
								core::pack<dimension<typename type1::standard_t, res_rank>>>
							, Index1 + 1, Index2 + 1>();
					}
				}
				else
				{
					if constexpr(
						compare_less_metric_v<typename type1::metric_t, typename type2::metric_t>
						)
					{
						return merge<core::pack_cat_t<Acumulated, core::pack<type1>>, Index1 + 1, Index2>();
					}
					else
					{
						return merge<core::pack_cat_t<Acumulated, core::pack<type2>>, Index1, Index2 + 1>();
					}
				}
			}
			else
			{
				return direct_declval<core::pack_cat_t<Acumulated, core::sub_pack_t<Pack1, Index1>>>();
			}
		}
		else
		{
			if constexpr(Index2 < pack2_size)
			{
				return direct_declval<core::pack_cat_t<Acumulated, core::sub_pack_t<Pack2, Index2>>>();
			}
			else
			{
				return direct_declval<Acumulated>();
			}
		}
	}


public:
	using type = decltype(merge());
};


/// \brief Merges 2 sorted pack lists of dimensions
/// \warning Requires packs to be sorted
template<core::c_pack Pack1, core::c_pack Pack2>
struct dimension_merge_no_clober
{
private:
	static constexpr uintptr_t pack1_size = core::pack_count_v<Pack1>;
	static constexpr uintptr_t pack2_size = core::pack_count_v<Pack2>;

	template<typename Acumulated = core::pack<>, uintptr_t Index1 = 0, uintptr_t Index2 = 0>
	static constexpr auto merge()
	{
		if constexpr (Index1 < pack1_size)
		{
			if constexpr(Index2 < pack2_size)
			{
				using type1 = typename core::pack_get_t<Pack1, Index1>;
				using type2 = typename core::pack_get_t<Pack2, Index2>;

				if constexpr(
					compare_equal_metric_v<typename type1::metric_t, typename type2::metric_t>
					&& type1::base_gauge == type2::base_gauge)
				{
					constexpr int8_t res_rank = type1::rank + type2::rank;
					if constexpr(res_rank == 0)
					{
						return merge<Acumulated, Index1 + 1, Index2 + 1>();
					}
					else
					{
						return merge<
							core::pack_cat_t<
								Acumulated,
								core::pack<dimension<typename type1::standard_t, res_rank>>>
							, Index1 + 1, Index2 + 1>();
					}
				}
				else
				{
					if constexpr(
						compare_equal_metric_v<typename type1::metric_t, typename type2::metric_t>
						? type1::base_gauge < type2::base_gauge :
						compare_less_metric_v<typename type1::metric_t, typename type2::metric_t>
						)
					{
						return merge<core::pack_cat_t<Acumulated, core::pack<type1>>, Index1 + 1, Index2>();
					}
					else
					{
						return merge<core::pack_cat_t<Acumulated, core::pack<type2>>, Index1, Index2 + 1>();
					}
				}
			}
			else
			{
				return direct_declval<core::pack_cat_t<Acumulated, core::sub_pack_t<Pack1, Index1>>>();
			}
		}
		else
		{
			if constexpr(Index2 < pack2_size)
			{
				return direct_declval<core::pack_cat_t<Acumulated, core::sub_pack_t<Pack2, Index2>>>();
			}
			else
			{
				return direct_declval<Acumulated>();
			}
		}
	}


public:
	using type = decltype(merge());
};


/// \brief Merges 2 sorted pack lists of scalars
/// \warning Requires packs to be sorted
template<core::c_pack Pack1, core::c_pack Pack2>
struct scalar_merge
{
	static constexpr uintptr_t pack1_size = core::pack_count_v<Pack1>;
	static constexpr uintptr_t pack2_size = core::pack_count_v<Pack2>;

	template<typename Acumulated = core::pack<>, uintptr_t Index1 = 0, uintptr_t Index2 = 0>
	static constexpr auto merge()
	{
		if constexpr (Index1 < pack1_size)
		{
			if constexpr(Index2 < pack2_size)
			{
				using type1 = typename core::pack_get_t<Pack1, Index1>;
				using type2 = typename core::pack_get_t<Pack2, Index2>;

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
							core::pack_cat_t<
							Acumulated,
							core::pack<scalar<typename type1::scalar_t, res_power>>>
							, Index1 + 1, Index2 + 1>();
					}
				}
				else
				{
					if constexpr(type1::base_factor < type2::base_factor)
					{
						return merge<core::pack_cat_t<Acumulated, core::pack<type1>>, Index1 + 1, Index2>();
					}
					else
					{
						return merge<core::pack_cat_t<Acumulated, core::pack<type2>>, Index1, Index2 + 1>();
					}
				}
			}
			else
			{
				return direct_declval<core::pack_cat_t<Acumulated, core::sub_pack_t<Pack1, Index1>>>();
			}
		}
		else
		{
			if constexpr(Index2 < pack2_size)
			{
				return direct_declval<core::pack_cat_t<Acumulated, core::sub_pack_t<Pack2, Index2>>>();
			}
			else
			{
				return direct_declval<Acumulated>();
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
	using dim1	= typename inverse_pack<typename Pack1::dimension_pack>::type;
	using scal1	= typename inverse_pack<typename Pack1::scalar_pack>::type;
	using dim2	= typename Pack2::dimension_pack;
	using scal2	= typename Pack2::scalar_pack;

	constexpr long double scalar_factor = pack_multiply<typename scalar_merge<scal2, scal1>::type, get_factor>::value;
	constexpr long double conversion = pack_multiply<typename dimension_merge_no_clober<dim2, dim1>::type, get_factor>::value * scalar_factor;

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


	using scalar_pack = typename scalar_merge<scal1, scal2>::type;
	constexpr long double scalar_factor = pack_multiply<scalar_pack, get_factor>::value;


	if constexpr(has_conflicting_units<dim1, dim2>::value)
	{
		using real_dimension_pack = typename dimension_merge_no_clober<dim1, dim2>::type;

		constexpr long double real_gauge = pack_multiply<real_dimension_pack, get_factor>::value * scalar_factor;

		using result_dimension_pack =
			typename dimension_merge_clober<
				typename core::pack_transform_t<dim1, standardize>,
				typename core::pack_transform_t<dim2, standardize>
			>::type;

		if constexpr(core::is_pack_empty_v<result_dimension_pack>)
		{
			return op_result_t<vtype, vtype>{static_cast<vtype>(t_result * real_gauge)};
		}
		else
		{
			return op_result_t<vtype, unit_pack<result_dimension_pack, core::pack<>>>{static_cast<vtype>(t_result * real_gauge)};
		}
	}
	else
	{
		using result_dimension_pack =
			typename dimension_merge_clober<
				dim1,
				dim2
			>::type;

		if constexpr(core::is_pack_empty_v<result_dimension_pack>)
		{
			return op_result_t<vtype, vtype>{static_cast<vtype>(t_result * scalar_factor)};
		}
		else
		{
			return op_result_t<vtype, unit_pack<result_dimension_pack, scalar_pack>>{t_result};
		}
	}
}

template<c_unit_pack Pack1, c_unit_pack Pack2, c_ValidFP value_t1, c_ValidFP value_t2>
inline constexpr auto metric_divide(value_t1 p_t1, value_t2 p_t2)
{
	using dim1	= typename Pack1::dimension_pack;
	using scal1	= typename Pack1::scalar_pack;
	using dim2	= typename inverse_pack<typename Pack2::dimension_pack>::type;
	using scal2	= typename inverse_pack<typename Pack2::scalar_pack>::type;

	auto t_result = p_t1 / p_t2;
	using vtype = decltype(t_result);

	using scalar_pack = typename scalar_merge<scal1, scal2>::type;
	constexpr long double scalar_factor = pack_multiply<scalar_pack, get_factor>::value;

	if constexpr(has_conflicting_units<dim1, dim2>::value)
	{
		using real_dimension_pack = typename dimension_merge_no_clober<dim1, dim2>::type;

		constexpr long double real_gauge = pack_multiply<real_dimension_pack, get_factor>::value * scalar_factor;

		using result_dimension_pack =
			typename dimension_merge_clober<
				typename core::pack_transform_t<dim1, standardize>,
				typename core::pack_transform_t<dim2, standardize>
			>::type;

		if constexpr(core::is_pack_empty_v<result_dimension_pack>)
		{
			return op_result_t<vtype, vtype>{static_cast<vtype>(t_result * real_gauge)};
		}
		else
		{
			return op_result_t<vtype, unit_pack<result_dimension_pack, core::pack<>>>{static_cast<vtype>(t_result * real_gauge)};
		}
	}
	else
	{
		using result_dimension_pack =
			typename dimension_merge_clober<
				dim1,
				dim2
			>::type;
		if constexpr(core::is_pack_empty_v<result_dimension_pack>)
		{
			return op_result_t<vtype, vtype>{static_cast<vtype>(t_result * scalar_factor)};
		}
		else
		{
			return op_result_t<vtype, unit_pack<result_dimension_pack, scalar_pack>>{t_result};
		}
	}
}

} //namespace unit::_p
