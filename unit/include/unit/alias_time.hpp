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

#include "standard/standard_time.hpp"
#include "standard/si_prefix.hpp"
#include "_p/unit_type.hpp"

namespace unit
{

//======== ======== Template Type ======== ========

template <_p::c_ValidFP T>
using second_t = typename make_unit<T, std::tuple<_p::dimension<standard::second, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using minute_t = typename make_unit<T, std::tuple<_p::dimension<standard::minute, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using hour_t = typename make_unit<T, std::tuple<_p::dimension<standard::hour, 1>>, std::tuple<>>::type;


template <_p::c_ValidFP T>
using nano_second_t = typename make_unit<T, std::tuple<_p::dimension<standard::second, 1>>, std::tuple<multi::nano<1>>>::type;

template <_p::c_ValidFP T>
using micro_second_t = typename make_unit<T, std::tuple<_p::dimension<standard::second, 1>>, std::tuple<multi::micro<1>>>::type;

template <_p::c_ValidFP T>
using milli_second_t = typename make_unit<T, std::tuple<_p::dimension<standard::second, 1>>, std::tuple<multi::milli<1>>>::type;


template <_p::c_ValidFP T>
using hertz_t = typename make_unit<T, std::tuple<_p::dimension<standard::second, -1>>, std::tuple<>>::type;


//======== ======== Default Type ======== ========

using second	= second_t	<_p::default_fp>;
using minute	= minute_t	<_p::default_fp>;
using hour		= hour_t	<_p::default_fp>;

using nano_second	= nano_second_t	<_p::default_fp>;
using micro_second	= micro_second_t<_p::default_fp>;
using milli_second	= milli_second_t<_p::default_fp>;

using hertz = hertz_t<_p::default_fp>;

} //namespace unit
