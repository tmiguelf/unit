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

#include "standard/standard_charge.hpp"
#include "standard/multipliers.hpp"
#include "standard/si_prefix.hpp"
#include "_p/unit_type.hpp"

namespace unit
{

//======== ======== Template Type ======== ========

template <_p::c_ValidFP T>
using coloumb_t = typename make_unit<T, std::tuple<_p::dimension<standard::coloumb, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using amper_hour_t = typename make_unit<T, std::tuple<_p::dimension<standard::coloumb, 1>>, std::tuple<_p::scalar<multi::seconds_in_hour, 1>>>::type;

template <_p::c_ValidFP T>
using milli_amper_hour_t = typename make_unit<T, std::tuple<_p::dimension<standard::coloumb, 1>>, std::tuple<multi::milli<1>, _p::scalar<multi::seconds_in_hour, 1>>>::type;


//======== ======== Default Type ======== ========

using coloumb			= coloumb_t			<_p::default_fp>;

using amper_hour		= amper_hour_t		<_p::default_fp>;
using milli_amper_hour	= milli_amper_hour_t<_p::default_fp>;

} //namespace unit
