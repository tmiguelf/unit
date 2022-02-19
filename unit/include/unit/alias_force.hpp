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

#include "standard/standard_mass.hpp"
#include "standard/standard_lenght.hpp"
#include "standard/standard_time.hpp"

namespace unit
{

//======== ======== Template Type ======== ========

template <_p::c_ValidFP T>
using newton_t = typename make_unit<T, std::tuple<_p::dimension<standard::si_mass, 1>, _p::dimension<standard::metre, 1>, _p::dimension<standard::second, -2>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using kilogram_force_t = typename make_unit<T, std::tuple<_p::dimension<standard::si_mass, 1>, _p::dimension<standard::metre, 1>, _p::dimension<standard::second, -2>>, std::tuple<_p::scalar<multi::g0_si, 1>>>::type;

template <_p::c_ValidFP T>
using pound_av_force_t = typename make_unit<T, std::tuple<_p::dimension<standard::pound_av, 1>, _p::dimension<standard::foot, 1>, _p::dimension<standard::second, -2>>, std::tuple<_p::scalar<multi::g0_imp, 1>>>::type;

template <_p::c_ValidFP T>
using poundal_t = typename make_unit<T, std::tuple<_p::dimension<standard::pound_av, 1>, _p::dimension<standard::foot, 1>, _p::dimension<standard::second, -2>>, std::tuple<>>::type;


//======== ======== Default Type ======== ========

using newton			= newton_t			<_p::default_fp>;
using kilogram_force	= kilogram_force_t	<_p::default_fp>;
using pound_av_force	= pound_av_force_t	<_p::default_fp>;
using poundal			= poundal_t			<_p::default_fp>;

} //namespace unit