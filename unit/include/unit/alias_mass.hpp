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

#include "standard/standard_mass.hpp"
#include "standard/si_prefix.hpp"
#include "_p/unit_type.hpp"

namespace unit
{

//======== ======== Template Type ======== ========

template <_p::c_ValidFP T>
using kilogram_t = typename make_unit<T, core::pack<_p::dimension<standard::si_mass, 1>>, core::pack<>>::type;

template <_p::c_ValidFP T>
using gram_t = typename make_unit<T, core::pack<_p::dimension<standard::gram, 1>>, core::pack<>>::type;

template <_p::c_ValidFP T>
using pound_av_t = typename make_unit<T, core::pack<_p::dimension<standard::pound_av, 1>>, core::pack<>>::type;

template <_p::c_ValidFP T>
using ounce_av_t = typename make_unit<T, core::pack<_p::dimension<standard::ounce_av, 1>>, core::pack<>>::type;

template <_p::c_ValidFP T>
using tonne_t = typename make_unit<T, core::pack<_p::dimension<standard::si_mass, 1>>, core::pack<_p::scalar<multi::E, 3>>>::type;

//======== ======== Default Type ======== ========

using kilogram	= kilogram_t<_p::default_fp>;
using gram		= gram_t	<_p::default_fp>;
using pound_av	= pound_av_t<_p::default_fp>;
using ounce_av	= ounce_av_t<_p::default_fp>;
using tonne		= tonne_t	<_p::default_fp>;

} //namespace unit
