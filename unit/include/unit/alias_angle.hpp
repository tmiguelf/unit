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

#pragma once

#include "standard/standard_angle.hpp"
#include "_p/unit_type.hpp"

namespace unit
{

//======== ======== Template Type ======== ========

template <_p::c_ValidFP T>
using radian_t = typename make_unit<T, std::tuple<_p::dimension<standard::radian, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using degree_t = typename make_unit<T, std::tuple<_p::dimension<standard::degree, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using arc_minute_t = typename make_unit<T, std::tuple<_p::dimension<standard::arc_minute, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using arc_second_t = typename make_unit<T, std::tuple<_p::dimension<standard::arc_second, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using turn_t = typename make_unit<T, std::tuple<_p::dimension<standard::turn, 1>>, std::tuple<>>::type;


//======== ======== Default Type ======== ========

using radian		= radian_t		<_p::default_fp>;
using degree		= degree_t		<_p::default_fp>;
using arc_minute	= arc_minute_t	<_p::default_fp>;
using arc_second	= arc_second_t	<_p::default_fp>;
using turn			= turn_t		<_p::default_fp>;

} //namespace unit
