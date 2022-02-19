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

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <type_traits>
#include <limits>
#include <typeinfo>

#include <unit/_p/unit_type.hpp>

#include <unit/alias_lenght.hpp>
#include <unit/alias_mass.hpp>
#include <unit/alias_temperature.hpp>

#include "test_utils.hpp"

namespace unit
{

TEST(type_conversion, invariant_multiply_composition)
{
	//simple units same type
	{
		constexpr double val1 = 1.3 / 3.5;
		constexpr double val2 = 4.1;
		constexpr auto val_expect = val1 * val2;

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::pound_av, 1>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} * type2_test_t{val2};
		using expected_type_t = typename make_unit<std::remove_cv_t<decltype(val_expect)>, std::tuple<_p::dimension<standard::foot, 1>, _p::dimension<standard::pound_av, 1>>, std::tuple<>>::type;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(binarySame(result.value(), val_expect));
	}

	//simple units different type
	{
		constexpr float val1 = 1.3f / 3.5f;
		constexpr double val2 = 4.1;
		constexpr auto val_expect = val1 * val2;

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::pound_av, 1>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} * type2_test_t{val2};
		using expected_type_t = typename make_unit<std::remove_cv_t<decltype(val_expect)>, std::tuple<_p::dimension<standard::foot, 1>, _p::dimension<standard::pound_av, 1>>, std::tuple<>>::type;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(binarySame(result.value(), val_expect));
	}

	//complex units same type
	{
		constexpr double val1 = 1.3 / 3.5;
		constexpr double val2 = 4.1;
		constexpr auto val_expect = val1 * val2;

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 4>, _p::dimension<standard::rankine, 2>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::pound_av, -3>, _p::dimension<standard::rankine, -5>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} * type2_test_t{val2};
		using expected_type_t = typename make_unit<std::remove_cv_t<decltype(val_expect)>, std::tuple<_p::dimension<standard::pound_av, -3>, _p::dimension<standard::foot, 4>, _p::dimension<standard::rankine, -3>>, std::tuple<>>::type;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(binarySame(result.value(), val_expect));
	}

	//complex units different type
	{
		constexpr float val1 = 1.3f / 3.5f;
		constexpr long double val2 = 4.1l;
		constexpr auto val_expect = val1 * val2;

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 4>, _p::dimension<standard::rankine, 2>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::pound_av, -3>, _p::dimension<standard::rankine, -5>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} * type2_test_t{val2};
		using expected_type_t = typename make_unit<std::remove_cv_t<decltype(val_expect)>, std::tuple<_p::dimension<standard::pound_av, -3>, _p::dimension<standard::foot, 4>, _p::dimension<standard::rankine, -3>>, std::tuple<>>::type;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(binarySame(result.value(), val_expect));
	}

	//complete cancelation
	{
		constexpr float val1 = 1.3f / 3.5f;
		constexpr long double val2 = 4.1l;
		constexpr auto val_expect = val1 * val2;

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 4>, _p::dimension<standard::rankine, 2>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::foot, -4>, _p::dimension<standard::rankine, -2>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} * type2_test_t{val2};
		using expected_type_t = std::remove_cv_t<decltype(val_expect)>;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(binarySame(result, val_expect));
	}
}

TEST(type_conversion, invariant_divide_composition)
{
	//simple units same type
	{
		constexpr double val1 = 1.3 / 3.5;
		constexpr double val2 = 4.1;
		constexpr auto val_expect = val1 / val2;

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::pound_av, 1>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} / type2_test_t{val2};
		using expected_type_t = typename make_unit<std::remove_cv_t<decltype(val_expect)>, std::tuple<_p::dimension<standard::foot, 1>, _p::dimension<standard::pound_av, -1>>, std::tuple<>>::type;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(binarySame(result.value(), val_expect));
	}

	//simple units different type
	{
		constexpr float val1 = 1.3f / 3.5f;
		constexpr double val2 = 4.1;
		constexpr auto val_expect = val1 / val2;

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::pound_av, 1>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} / type2_test_t{val2};
		using expected_type_t = typename make_unit<std::remove_cv_t<decltype(val_expect)>, std::tuple<_p::dimension<standard::foot, 1>, _p::dimension<standard::pound_av, -1>>, std::tuple<>>::type;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(binarySame(result.value(), val_expect));
	}

	//complex units same type
	{
		constexpr double val1 = 1.3 / 3.5;
		constexpr double val2 = 4.1;
		constexpr auto val_expect = val1 / val2;

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 4>, _p::dimension<standard::rankine, 2>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::pound_av, -3>, _p::dimension<standard::rankine, -5>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} / type2_test_t{val2};
		using expected_type_t = typename make_unit<std::remove_cv_t<decltype(val_expect)>, std::tuple<_p::dimension<standard::pound_av, 3>, _p::dimension<standard::foot, 4>, _p::dimension<standard::rankine, 7>>, std::tuple<>>::type;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(binarySame(result.value(), val_expect));
	}

	//complex units different type
	{
		constexpr float val1 = 1.3f / 3.5f;
		constexpr long double val2 = 4.1l;
		constexpr auto val_expect = val1 / val2;

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 4>, _p::dimension<standard::rankine, 2>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::pound_av, -3>, _p::dimension<standard::rankine, -5>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} / type2_test_t{val2};
		using expected_type_t = typename make_unit<std::remove_cv_t<decltype(val_expect)>, std::tuple<_p::dimension<standard::pound_av, 3>, _p::dimension<standard::foot, 4>, _p::dimension<standard::rankine, 7>>, std::tuple<>>::type;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(binarySame(result.value(), val_expect));
	}

	//complete cancelation
	{
		constexpr float val1 = 1.3f / 3.5f;
		constexpr long double val2 = 4.1l;
		constexpr auto val_expect = val1 / val2;

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 4>, _p::dimension<standard::rankine, 2>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::foot, 4>, _p::dimension<standard::rankine, 2>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} / type2_test_t{val2};

		ASSERT_TRUE((std::is_same_v<decltype(result), decltype(val_expect)>));
		ASSERT_TRUE(binarySame(result, val_expect));
	}
}

TEST(type_conversion, multiply)
{
	constexpr long double ld_extra = (sizeof(long double) == 16) ? 2048. : 1.;

	//simple elimination
	{
		constexpr double val1 = 0.3714285714285714413;
		constexpr double val2 = 4.1;
		constexpr auto val_res = (val1 * val2);
		constexpr decltype(val_res) val_expect = val_res / (5280.0);

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::mile, -1>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} * type2_test_t{val2};

		ASSERT_TRUE((std::is_same_v<decltype(result), decltype(val_expect)>));
		ASSERT_TRUE(closeEnough(result, val_expect, std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect));
	}

	//complex elimination
	{
		constexpr float val1 = 0.3714285714285714413f;
		constexpr long double val2 = 4.1l;
		constexpr auto val_res = (val1 * val2);
		constexpr decltype(val_res) val_expect = val_res * (4096.0 / (5280.0 * 5280.0));

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 2>, _p::dimension<standard::ounce_av, -3>, _p::dimension<standard::rankine, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::mile, -2>, _p::dimension<standard::pound_av, 3>, _p::dimension<standard::rankine, -1>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} * type2_test_t{val2};


		ASSERT_TRUE((std::is_same_v<decltype(result), decltype(val_expect)>));
		ASSERT_TRUE(closeEnough(result, val_expect, std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect * ld_extra));
	}

	//composition
	{
		constexpr double val1 = 0.3714285714285714413;
		constexpr double val2 = 4.1;
		constexpr auto val_res = (val1 * val2);
		constexpr decltype(val_res) val_expect = val_res * (.3048 * 1609.344);

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::mile, 1>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} * type2_test_t{val2};
		using expected_type_t = typename make_unit<std::remove_cv_t<decltype(val_expect)>, std::tuple<_p::dimension<standard::SI_standard<::unit::_p::unit_id::length>::type, 2>>, std::tuple<>>::type;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(closeEnough(result.value(), val_expect, std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect));
	}

	//complex composition
	{
		constexpr float val1 = 0.3714285714285714413f;
		constexpr long double val2 = 4.1l;
		constexpr auto val_res = (val1 * val2);
		constexpr decltype(val_res) val_expect = val_res * ((1609.344 * .45359237l * .45359237l * 16. * 16. * 9.)
			/ (.3048 * .3048 * .3048 * 5. ));

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, -3>, _p::dimension<standard::ounce_av, -2>, _p::dimension<standard::kelvin, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::mile, 1>, _p::dimension<standard::pound_av, 4>, _p::dimension<standard::rankine, -1>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} * type2_test_t{val2};
		using expected_type_t = typename make_unit<std::remove_cv_t<decltype(val_expect)>, std::tuple<_p::dimension<standard::SI_standard<::unit::_p::unit_id::length>::type, -2>, _p::dimension<standard::SI_standard<::unit::_p::unit_id::mass>::type, 2>>, std::tuple<>>::type;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(closeEnough(result.value(), val_expect, std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect * 3. * ld_extra));
	}
}

TEST(type_conversion, divide)
{
	constexpr long double ld_extra = (sizeof(long double) == 16) ? 2048. : 1.;

	//simple elimination
	{
		constexpr double val1 = 0.3714285714285714413;
		constexpr double val2 = 4.1;
		constexpr auto val_res = (val1 / val2);
		constexpr decltype(val_res) val_expect = val_res / (5280.0);

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::mile, 1>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} / type2_test_t{val2};

		ASSERT_TRUE((std::is_same_v<decltype(result), decltype(val_expect)>));
		ASSERT_TRUE(closeEnough(result, val_expect, std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect));
	}

	//complex elimination
	{
		constexpr float val1 = 0.3714285714285714413f;
		constexpr long double val2 = 4.1l;
		constexpr auto val_res = (val1 / val2);
		constexpr decltype(val_res) val_expect = val_res * (4096.0 / (5280.0 * 5280.0));

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 2>, _p::dimension<standard::ounce_av, -3>, _p::dimension<standard::rankine, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::mile, 2>, _p::dimension<standard::pound_av, -3>, _p::dimension<standard::rankine, 1>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} / type2_test_t{val2};

		ASSERT_TRUE((std::is_same_v<decltype(result), decltype(val_expect)>));
		ASSERT_TRUE(closeEnough(result, val_expect, std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect * 2. * ld_extra));
	}

	//composition
	{
		constexpr double val1 = 0.3714285714285714413;
		constexpr double val2 = 4.1;
		constexpr auto val_res = (val1 / val2);
		constexpr decltype(val_res) val_expect = val_res * (.3048 * 1609.344);

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::mile, -1>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} / type2_test_t{val2};
		using expected_type_t = typename make_unit<std::remove_cv_t<decltype(val_expect)>, std::tuple<_p::dimension<standard::SI_standard<::unit::_p::unit_id::length>::type, 2>>, std::tuple<>>::type;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(closeEnough(result.value(), val_expect, std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect)) << result.value() << " " << val_expect;
	}

	//complex composition
	{
		constexpr float val1 = 0.3714285714285714413f;
		constexpr long double val2 = 4.1l;
		constexpr auto val_res = (val1 / val2);
		constexpr decltype(val_res) val_expect = val_res * ((1609.344 * .45359237l * .45359237l * 16. * 16. * 9.)
			/ (.3048 * .3048 * .3048 * 5. ));

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, -3>, _p::dimension<standard::ounce_av, -2>, _p::dimension<standard::kelvin, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::mile, -1>, _p::dimension<standard::pound_av, -4>, _p::dimension<standard::rankine, 1>>, std::tuple<>>::type;

		constexpr auto result = type1_test_t{val1} / type2_test_t{val2};
		using expected_type_t = typename make_unit<std::remove_cv_t<decltype(val_expect)>, std::tuple<_p::dimension<standard::SI_standard<::unit::_p::unit_id::length>::type, -2>, _p::dimension<standard::SI_standard<::unit::_p::unit_id::mass>::type, 2>>, std::tuple<>>::type;

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(closeEnough(result.value(), val_expect, std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect * 3. * ld_extra));
	}
}

TEST(type_conversion, add_assign)
{
	//simple
	{
		constexpr double val1 = 0.3714285714285714413;
		constexpr double val2 = 4.1;

		std::remove_cv_t<decltype(val1)> val_expect = val1;
		val_expect += (val2 * 5280.);

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::mile, 1>>, std::tuple<>>::type;

		type1_test_t result{val1};
		constexpr type2_test_t aux{val2};
		result += aux;

		ASSERT_TRUE(closeEnough(result.value(), val_expect, std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect));
	}

	//complex
	{
		constexpr float val1 = 0.3714285714285714413f;
		constexpr long double val2 = 4.1;

		std::remove_cv_t<decltype(val1)> val_expect = val1;
		val_expect += static_cast<decltype(val1)>(val2 * 5280. * 5280. / 4096.);

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 2>, _p::dimension<standard::ounce_av, -3>, _p::dimension<standard::rankine, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::mile, 2>, _p::dimension<standard::pound_av, -3>, _p::dimension<standard::rankine, 1>>, std::tuple<>>::type;

		type1_test_t result{val1};
		constexpr type2_test_t aux{val2};
		result += aux;

		ASSERT_TRUE(closeEnough(result.value(), val_expect, std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect));
	}
}

TEST(type_conversion, subtract_assign)
{
	//simple
	{
		constexpr double val1 = 0.3714285714285714413;
		constexpr double val2 = 4.1;

		std::remove_cv_t<decltype(val1)> val_expect = val1;
		val_expect -= (val2 * 5280.);

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::mile, 1>>, std::tuple<>>::type;

		type1_test_t result{val1};
		constexpr type2_test_t aux{val2};
		result -= aux;

		ASSERT_TRUE(closeEnough(result.value(), val_expect, -std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect)) << result.value() << " " << val_expect;
	}

	//complex
	{
		constexpr float val1 = 0.3714285714285714413f;
		constexpr long double val2 = 4.1;

		std::remove_cv_t<decltype(val1)> val_expect = val1;
		val_expect -= static_cast<decltype(val1)>(val2 * 5280. * 5280. / 4096.);

		using type1_test_t = typename make_unit<std::remove_cv_t<decltype(val1)>, std::tuple<_p::dimension<standard::foot, 2>, _p::dimension<standard::ounce_av, -3>, _p::dimension<standard::rankine, 1>>, std::tuple<>>::type;
		using type2_test_t = typename make_unit<std::remove_cv_t<decltype(val2)>, std::tuple<_p::dimension<standard::mile, 2>, _p::dimension<standard::pound_av, -3>, _p::dimension<standard::rankine, 1>>, std::tuple<>>::type;

		type1_test_t result{val1};
		constexpr type2_test_t aux{val2};
		result -= aux;

		ASSERT_TRUE(closeEnough(result.value(), val_expect, -std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect));
	}
}

} //namespace unit
