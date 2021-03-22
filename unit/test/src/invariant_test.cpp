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

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <type_traits>
#include <limits>
#include <utility>
#include <vector>

#include <unit/_p/unit_type.hpp>
#include <unit/alias_lenght.hpp>
#include <unit/alias_angle.hpp>
#include <unit/alias_area.hpp>
#include <unit/alias_pressure.hpp>

#include "test_utils.hpp"

namespace unit
{

template <typename>
struct is_Unit: std::false_type  {};

template <typename T1, typename T2>
struct is_Unit<_p::Unit<T1, T2>>: std::true_type  {};

template<typename T>
concept c_Unit = is_Unit<T>::value;


//======== ======== ======== Typed test suit  ======== ======== ========

template<typename T>
class Invariant_T : public testing::Test {
protected:
	Invariant_T() {}
};

using InvariantTestTypes =
	::testing::Types<
		metre_t<float>,
		metre_t<double>,
		metre_t<long double>,
		foot_t<double>,
		radian_t<double>,
		square_metre_t<double>,
		pascal_t<double>,
		poundal_per_square_foot_t<double>
	>;

TYPED_TEST_SUITE(Invariant_T, InvariantTestTypes);

template <typename T> requires std::is_floating_point_v<T>
const std::vector<T>& getInvariantCases()
{
	static const std::vector<T> g_testCases =
	{
		static_cast<T>( 0.l),
		static_cast<T>(-0.l),
		static_cast<T>( 1.l),
		static_cast<T>(-1.l),
		static_cast<T>(  .12345l),
		static_cast<T>(- .012345l),
		static_cast<T>(8458852.l),
		 std::numeric_limits<T>::denorm_min(),
		-std::numeric_limits<T>::denorm_min(),
		 std::numeric_limits<T>::epsilon(),
		 std::numeric_limits<T>::max(),
		 std::numeric_limits<T>::min(),
		 std::numeric_limits<T>::infinity(),
		-std::numeric_limits<T>::infinity(),
		 std::numeric_limits<T>::quiet_NaN(),
		 std::numeric_limits<T>::signaling_NaN(),
	};
	return g_testCases;
}


//======== Actual tests ========

TYPED_TEST(Invariant_T, initialize)
{
	using unit_t	= TypeParam;
	using value_t	= typename unit_t::value_t;

	const std::vector<value_t>& t_cases = getInvariantCases<value_t>();

	for(const value_t expected: t_cases)
	{
		const unit_t result{expected};
		ASSERT_TRUE(binarySame(result.value(), expected)) << "Case: " << expected;
	}
}

TYPED_TEST(Invariant_T, negate)
{
	using unit_t	= TypeParam;
	using value_t	= typename unit_t::value_t;

	const std::vector<value_t>& t_cases = getInvariantCases<value_t>();

	for(const value_t tvalue1: t_cases)
	{
		const unit_t temp1{tvalue1};
		const value_t expected = -tvalue1;
		const unit_t result = -temp1;
		ASSERT_TRUE(binarySame(result.value(), expected)) << "Case: -(" << tvalue1 << ')';
	}
}

TYPED_TEST(Invariant_T, add)
{
	using unit_t	= TypeParam;
	using value_t	= typename unit_t::value_t;

	const std::vector<value_t>& t_cases = getInvariantCases<value_t>();

	for(const value_t tvalue1: t_cases)
	{
		const unit_t temp1{tvalue1};
		for(const value_t tvalue2 : t_cases)
		{
			const unit_t temp2{tvalue2};
			const unit_t result = temp1 + temp2;
			const value_t expected = tvalue1 + tvalue2;
			ASSERT_TRUE(binarySame(result.value(), expected)) << "Case: " << tvalue1 << " + " << tvalue2;
		}
	}
}

TYPED_TEST(Invariant_T, add_assign)
{
	using unit_t	= TypeParam;
	using value_t	= typename unit_t::value_t;

	const std::vector<value_t>& t_cases = getInvariantCases<value_t>();

	for(const value_t tvalue1: t_cases)
	{
		const unit_t temp1{tvalue1};
		for(value_t tvalue2 : t_cases)
		{
			unit_t temp2{tvalue2};
			tvalue2 += tvalue1;
			temp2   += temp1;
			ASSERT_TRUE(binarySame(temp2.value(), tvalue2)) << "Case: " << tvalue2 << " += " << tvalue1;
		}
	}
}

TYPED_TEST(Invariant_T, subtract)
{
	using unit_t	= TypeParam;
	using value_t	= typename unit_t::value_t;

	const std::vector<value_t>& t_cases = getInvariantCases<value_t>();

	for(const value_t tvalue1: t_cases)
	{
		const unit_t temp1{tvalue1};
		for(const value_t tvalue2 : t_cases)
		{
			const unit_t temp2{tvalue2};
			const unit_t result = temp1 - temp2;
			const value_t expected = tvalue1 - tvalue2;
			ASSERT_TRUE(binarySame(result.value(), expected)) << "Case: " << tvalue1 << " - " << tvalue2;
		}
	}
}

TYPED_TEST(Invariant_T, subtract_assign)
{
	using unit_t	= TypeParam;
	using value_t	= typename unit_t::value_t;

	const std::vector<value_t>& t_cases = getInvariantCases<value_t>();

	for(const value_t tvalue1: t_cases)
	{
		const unit_t temp1{tvalue1};
		for(value_t tvalue2 : t_cases)
		{
			unit_t temp2{tvalue2};
			tvalue2 -= tvalue1;
			temp2   -= temp1;
			ASSERT_TRUE(binarySame(temp2.value(), tvalue2)) << "Case: " << tvalue2 << " -= " << tvalue1;
		}
	}
}

TYPED_TEST(Invariant_T, scalar_multiply)
{
	using unit_t	= TypeParam;
	using value_t	= typename unit_t::value_t;

	const std::vector<value_t>& t_cases = getInvariantCases<value_t>();

	for(const value_t tvalue1: t_cases)
	{
		const unit_t temp1{tvalue1};
		for(const value_t tvalue2 : t_cases)
		{
			const unit_t result = temp1 * tvalue2;
			const value_t expected = tvalue1 * tvalue2;
			ASSERT_TRUE(binarySame(result.value(), expected)) << "Case: " << tvalue1 << " * " << tvalue2;
		}
	}
}

TYPED_TEST(Invariant_T, scalar_multiply_assign)
{
	using unit_t	= TypeParam;
	using value_t	= typename unit_t::value_t;

	const std::vector<value_t>& t_cases = getInvariantCases<value_t>();

	for(const value_t tvalue1: t_cases)
	{
		for(value_t tvalue2 : t_cases)
		{
			unit_t temp{tvalue2};
			tvalue2 *= tvalue1;
			temp    *= tvalue1;
			ASSERT_TRUE(binarySame(temp.value(), tvalue2)) << "Case: " << tvalue2 << " *= " << tvalue1;
		}
	}
}

TYPED_TEST(Invariant_T, scalar_divide)
{
	using unit_t	= TypeParam;
	using value_t	= typename unit_t::value_t;

	const std::vector<value_t>& t_cases = getInvariantCases<value_t>();

	for(const value_t tvalue1: t_cases)
	{
		const unit_t temp1{tvalue1};
		for(const value_t tvalue2 : t_cases)
		{
			const unit_t  result = temp1 / tvalue2;
			const value_t expected = tvalue1 / tvalue2;
			ASSERT_TRUE(binarySame(result.value(), expected)) << "Case: " << tvalue1 << " / " << tvalue2;
		}
	}
}

TYPED_TEST(Invariant_T, scalar_divide_assign)
{
	using unit_t	= TypeParam;
	using value_t	= typename unit_t::value_t;

	const std::vector<value_t>& t_cases = getInvariantCases<value_t>();

	for(const value_t tvalue1: t_cases)
	{
		for(value_t tvalue2 : t_cases)
		{
			unit_t temp{tvalue2};
			tvalue2 /= tvalue1;
			temp    /= tvalue1;
			ASSERT_TRUE(binarySame(temp.value(), tvalue2)) << "Case: " << tvalue2 << " /= " << tvalue1;
		}
	}
}

TYPED_TEST(Invariant_T, compare)
{
	using unit_t	= TypeParam;
	using value_t	= typename unit_t::value_t;

	const std::vector<value_t>& t_cases = getInvariantCases<value_t>();

	for(const value_t tvalue1: t_cases)
	{
		const unit_t temp1{tvalue1};
		for(const value_t tvalue2 : t_cases)
		{
			const unit_t temp2{tvalue2};
			ASSERT_EQ((temp1 <  temp2), (tvalue1 <  tvalue2)) << "Case: " << tvalue1 << ',' << tvalue2;
			ASSERT_EQ((temp1 >  temp2), (tvalue1 >  tvalue2)) << "Case: " << tvalue1 << ',' << tvalue2;
			ASSERT_EQ((temp1 <= temp2), (tvalue1 <= tvalue2)) << "Case: " << tvalue1 << ',' << tvalue2;
			ASSERT_EQ((temp1 >= temp2), (tvalue1 >= tvalue2)) << "Case: " << tvalue1 << ',' << tvalue2;
			ASSERT_EQ((temp1 == temp2), (tvalue1 == tvalue2)) << "Case: " << tvalue1 << ',' << tvalue2;
			ASSERT_EQ((temp1 != temp2), (tvalue1 != tvalue2)) << "Case: " << tvalue1 << ',' << tvalue2;
		}
	}
}

} //namespace unit
