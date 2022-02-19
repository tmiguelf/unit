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

#include "_p/unit_type.hpp"
#include "standard/standard_lenght.hpp"
#include "standard/standard_time.hpp"

namespace unit
{

//======== ======== Template Type ======== ========

template <_p::c_ValidFP T>
using cubic_metre_per_second_t = typename make_unit<T, std::tuple<_p::dimension<standard::metre, 3>, _p::dimension<standard::second, -1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using cubic_foot_per_second_t = typename make_unit<T, std::tuple<_p::dimension<standard::foot, 3>, _p::dimension<standard::second, -1>>, std::tuple<>>::type;


//======== ======== Default Type ======== ========

using cubic_metres_per_second	= cubic_metre_per_second_t	<_p::default_fp>;
using cubic_foot_per_second		= cubic_foot_per_second_t	<_p::default_fp>;

} //namespace unit
