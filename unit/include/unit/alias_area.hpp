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

#include "standard/standard_lenght.hpp"
#include "standard/si_prefix.hpp"
#include "_p/unit_type.hpp"

namespace unit
{

namespace multi
{
struct square_yards_in_acre
{
	static constexpr long double factor = 4840.l;
};
} // namespace multi

//======== ======== Template Type ======== ========
template <_p::c_ValidFP T>
using square_metre_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 2>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using square_foot_t = typename make_unit<T, std::tuple<_p::dimension<standard::foot, 2>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using hectare_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 2>>, std::tuple<multi::hecto<2>>>::type;

template <_p::c_ValidFP T>
using acre_t = typename make_unit<T, std::tuple<_p::dimension<standard::yard, 2>>, std::tuple<_p::scalar<multi::square_yards_in_acre, 1>>>::type;

template <_p::c_ValidFP T>
using square_mile_t = typename make_unit<T, std::tuple<_p::dimension<standard::mile, 2>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using square_kilo_metre_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 2>>, std::tuple<multi::kilo<2>>>::type;

//======== ======== Default Type ======== ========

using square_metre	= square_metre_t<_p::default_fp>;
using square_foot	= square_foot_t	<_p::default_fp>;
using hectare		= hectare_t		<_p::default_fp>;
using acre			= acre_t		<_p::default_fp>;
using square_mile	= square_mile_t	<_p::default_fp>;

using square_kilo_metre	= square_kilo_metre_t<_p::default_fp>;


} //namespace unit
