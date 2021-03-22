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

#include <unit/alias_temperature.hpp>

#include "test_utils.hpp"

namespace unit
{

TEST(proxy_type, to_unit)
{
	//compatible types
	{
		constexpr double val = 4.1;
		constexpr double val_expect = static_cast<decltype(val)>(val + 459.67l);

		using test_t			= fahrenheit_t<std::remove_const_t<decltype(val)>>;
		using expected_type_t	= rankine_t<std::remove_const_t<decltype(val_expect)>>;

		constexpr auto result = test_t{val}.to_unit();

		ASSERT_TRUE((std::is_same_v<decltype(result), const expected_type_t>));
		ASSERT_TRUE(closeEnough(result.value(), val_expect, std::numeric_limits<decltype(val_expect)>::epsilon() * val_expect));
	}
}

} //namespace unit
