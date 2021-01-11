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

#include "_p/unit_type.hpp"
#include "standard/standard_mass.hpp"
#include "standard/standard_lenght.hpp"
#include "standard/standard_time.hpp"
#include "standard/si_prefix.hpp"

namespace unit
{

namespace multi
{

struct inch_mercury32_factor
{
	static constexpr long double factor = 3386.38l;
};

struct inch_mercury60_factor
{
	static constexpr long double factor = 3376.85l;
};

struct atmosphere_factor
{
	static constexpr long double factor = 101325.l;
};

} //namespace multi

  //======== ======== Template Type ======== ========
template <_p::c_ValidFP T>
using pascal_t = typename make_unit<T, std::tuple<_p::dimension<standard::si_mass, 1>, _p::dimension<standard::metre, -1>, _p::dimension<standard::second, -2>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using kilopascal_t = typename make_unit<T, std::tuple<_p::dimension<standard::si_mass, 1>, _p::dimension<standard::metre, -1>, _p::dimension<standard::second, -2>>, std::tuple<multi::kilo<1>>>::type;

template <_p::c_ValidFP T>
using bar_t = typename make_unit<T, std::tuple<_p::dimension<standard::si_mass, 1>, _p::dimension<standard::metre, -1>, _p::dimension<standard::second, -2>>, std::tuple<_p::scalar<multi::E, 5>>>::type;

template <_p::c_ValidFP T>
using pound_av_force_per_square_inch_t = typename make_unit<T, std::tuple<_p::dimension<standard::pound_av, 1>, _p::dimension<standard::inch, -1>, _p::dimension<standard::second, -2>>, std::tuple<_p::scalar<multi::g0_si, 1>, _p::scalar<multi::inches_in_meter, 1>>>::type;

template <_p::c_ValidFP T>
using inch_mercury32_t = typename make_unit<T, std::tuple<_p::dimension<standard::si_mass, 1>, _p::dimension<standard::metre, -1>, _p::dimension<standard::second, -2>>, std::tuple<_p::scalar<multi::inch_mercury32_factor, 1>>>::type;

template <_p::c_ValidFP T>
using inch_mercury60_t = typename make_unit<T, std::tuple<_p::dimension<standard::si_mass, 1>, _p::dimension<standard::metre, -1>, _p::dimension<standard::second, -2>>, std::tuple<_p::scalar<multi::inch_mercury60_factor, 1>>>::type;

template <_p::c_ValidFP T>
using inch_mercury_t = inch_mercury32_t<T>;

template <_p::c_ValidFP T>
using atmosphere_t = typename make_unit<T, std::tuple<_p::dimension<standard::si_mass, 1>, _p::dimension<standard::metre, -1>, _p::dimension<standard::second, -2>>, std::tuple<_p::scalar<multi::atmosphere_factor, 1>>>::type;

template <_p::c_ValidFP T>
using poundal_per_square_foot_t = typename make_unit<T, std::tuple<_p::dimension<standard::pound_av, 1>, _p::dimension<standard::foot, -1>, _p::dimension<standard::second, -2>>, std::tuple<>>::type;



//======== ======== Default Type ======== ========
using pascal					= pascal_t					<_p::default_fp>;
using kilopascal				= kilopascal_t				<_p::default_fp>;
using bar						= bar_t						<_p::default_fp>;
using pound_av_force_per_square_inch = pound_av_force_per_square_inch_t<_p::default_fp>;
using inch_mercury32			= inch_mercury32_t			<_p::default_fp>;
using inch_mercury60			= inch_mercury60_t			<_p::default_fp>;
using inch_mercury				= inch_mercury_t			<_p::default_fp>;
using atmosphere				= atmosphere_t				<_p::default_fp>;
using poundal_per_square_foot	= poundal_per_square_foot_t	<_p::default_fp>;




} //namespace unit
