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

#include "standard/standard_lenght.hpp"
#include "standard/si_prefix.hpp"
#include "_p/unit_type.hpp"


namespace unit
{

namespace multi
{
struct cubic_metres_in_gallon
{
	static constexpr long double factor = 4.546'09E-3l;
};

struct cubic_metres_in_pint
{
	static constexpr long double factor = cubic_metres_in_gallon::factor / 8.l;
};
} //namespace multi


//======== ======== Template Type ======== ========

template <_p::c_ValidFP T>
using cubic_metre_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 3>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using litre_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 3>>, std::tuple<multi::deci<3>>>::type;

template <_p::c_ValidFP T>
using cubic_foot_t = typename make_unit<T, std::tuple<_p::dimension<standard::foot, 3>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using gallon_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 3>>, std::tuple<_p::scalar<multi::cubic_metres_in_gallon, 1>>>::type;

template <_p::c_ValidFP T>
using pint_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 3>>, std::tuple<_p::scalar<multi::cubic_metres_in_pint, 1>>>::type;


//======== ======== Default Type ======== ========

using cubic_metre	= cubic_metre_t	<_p::default_fp>;
using litre			= litre_t		<_p::default_fp>;
using cubic_foot	= cubic_foot_t	<_p::default_fp>;
using gallon		= gallon_t		<_p::default_fp>;
using pint			= pint_t		<_p::default_fp>;

} //namespace unit
