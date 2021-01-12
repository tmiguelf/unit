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

//======== ======== Template Type ======== ========

template <_p::c_ValidFP T>
using metre_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using foot_t = typename make_unit<T, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using inch_t = typename make_unit<T, std::tuple<_p::dimension<standard::inch, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using yard_t = typename make_unit<T, std::tuple<_p::dimension<standard::yard, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using mile_t = typename make_unit<T, std::tuple<_p::dimension<standard::mile, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using nautical_mile_t = typename make_unit<T, std::tuple<_p::dimension<standard::nautical_mile, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using light_second_t = typename make_unit<T, std::tuple<_p::dimension<standard::light_second, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using light_year_t = typename make_unit<T, std::tuple<_p::dimension<standard::light_year, 1>>, std::tuple<>>::type;





template <_p::c_ValidFP T>
using nano_metre_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 1>>, std::tuple<multi::nano<1>>>::type;

template <_p::c_ValidFP T>
using micro_metre_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 1>>, std::tuple<multi::micro<1>>>::type;

template <_p::c_ValidFP T>
using milli_metre_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 1>>, std::tuple<multi::milli<1>>>::type;

template <_p::c_ValidFP T>
using centi_metre_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 1>>, std::tuple<multi::centi<1>>>::type;

template <_p::c_ValidFP T>
using kilo_metre_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 1>>, std::tuple<multi::kilo<1>>>::type;

//======== ======== Default Type ======== ========

using metre			= metre_t			<_p::default_fp>;
using foot			= foot_t			<_p::default_fp>;
using inch			= inch_t			<_p::default_fp>;
using yard			= yard_t			<_p::default_fp>;
using mile			= mile_t			<_p::default_fp>;
using nautical_mile	= nautical_mile_t	<_p::default_fp>;
using light_second	= light_second_t	<_p::default_fp>;
using light_year	= light_year_t		<_p::default_fp>;


using nano_metre	= nano_metre_t		<_p::default_fp>;
using micro_metre	= micro_metre_t		<_p::default_fp>;
using milli_metre	= milli_metre_t		<_p::default_fp>;
using centi_metre	= centi_metre_t		<_p::default_fp>;
using kilo_metre	= kilo_metre_t		<_p::default_fp>;

} //namespace unit
