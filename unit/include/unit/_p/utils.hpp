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

#include <type_traits>
#include <CoreLib/core_pack.hpp>

namespace unit::_p
{


	template <typename>
	struct is_valid_value_type: std::false_type {};

	template <typename Type> requires std::is_floating_point_v<Type>
	struct is_valid_value_type<Type>: std::true_type {};

	template <typename Type>
	constexpr bool is_valid_value_type_v = is_valid_value_type<Type>::value;



	// \brief supported value types
	template<typename T>
	concept c_ValidValue = is_valid_value_type_v<T> && !std::is_const_v<T>;

	template<typename T>
	concept c_ValidFP = std::is_floating_point_v<T> && !std::is_const_v<T>;

	template<typename T>
	concept c_arithmethic = std::is_arithmetic_v<T>;


	/// \brief Multiplies elements in a pack
	template<core::c_pack Pack_t, template <typename> typename Getter>
	struct pack_multiply
	{
	private:
		static constexpr uintptr_t pack_size = core::pack_count_v<Pack_t>;

		template<uintptr_t Index = 0>
		static constexpr long double result()
		{
			if constexpr(Index < pack_size)
			{
				constexpr long double this_v = Getter<core::pack_get_t<Pack_t, Index>>::get();
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


	//======== ======== pack selection sort ======== ========
	/// \brief Sorts elements in a pack
	template <core::c_pack Pack_t, template <typename, typename> typename Comparator>
	struct pack_selection_sort
	{
	private:
		static constexpr uintptr_t pack_size = core::pack_count_v<Pack_t>;


		template <core::c_pack LoopPack, std::uintptr_t i, std::uintptr_t j>
		struct pack_selection_sort_impl
		{
			using pack_type = std::conditional_t<
				Comparator<
				core::pack_get_t<LoopPack, i>, core::pack_get_t<LoopPack, j>
				>::value,
				LoopPack,
				typename core::pack_element_swap<LoopPack, i, j>::type
			>;

			using type = typename pack_selection_sort_impl<pack_type, i, j + 1>::type;
		};

		template <core::c_pack LoopPack, std::uintptr_t i>
		struct pack_selection_sort_impl<LoopPack, i, pack_size>
		{
			using type = typename pack_selection_sort_impl<LoopPack, i + 1, i + 2>::type;
		};

		template <core::c_pack LoopPack, std::uintptr_t j>
		struct pack_selection_sort_impl<LoopPack, pack_size, j>
		{
			using type = LoopPack;
		};

	public:
		using type = typename pack_selection_sort_impl<Pack_t, 0, 1>::type;
	};


	/// \brief checks if types in a pack are strictly sorted (i.e sorted with no repeated elements)
	template <core::c_pack Pack_t, template <typename, typename> typename Comparator>
	struct is_pack_strictly_sorted
	{
	private:
		static constexpr uintptr_t pack_size = core::pack_count_v<Pack_t>;

		template<uintptr_t Index = 0>
		static constexpr bool check()
		{
			if constexpr(Index + 1 < pack_size)
			{
				if constexpr (Comparator<core::pack_get_t<Pack_t, Index>, core::pack_get_t<Pack_t, Index + 1>>::value)
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

