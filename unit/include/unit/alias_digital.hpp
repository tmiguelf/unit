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

#include "_p/unit_type.hpp"
#include "standard/standard_digital.hpp"
#include "standard/digital_prefix.hpp"

namespace unit
{

//======== ======== Template Type ======== ========
template <_p::c_ValidFP T>
using bit_t = typename make_unit<T, std::tuple<_p::dimension<standard::bit, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using byte_t = typename make_unit<T, std::tuple<_p::dimension<standard::byte, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using doublet_t = typename make_unit<T, std::tuple<_p::dimension<standard::doublet, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using quadlet_t = typename make_unit<T, std::tuple<_p::dimension<standard::quadlet, 1>>, std::tuple<>>::type;

template <_p::c_ValidFP T>
using octlet_t = typename make_unit<T, std::tuple<_p::dimension<standard::octlet, 1>>, std::tuple<>>::type;


template <_p::c_ValidFP T>
using kibibyte_t = typename make_unit<T, std::tuple<_p::dimension<standard::byte, 1>>, std::tuple<multi::kibi<1>>>::type;

template <_p::c_ValidFP T>
using mebibyte_t = typename make_unit<T, std::tuple<_p::dimension<standard::byte, 1>>, std::tuple<multi::mebi<1>>>::type;

template <_p::c_ValidFP T>
using gibibyte_t = typename make_unit<T, std::tuple<_p::dimension<standard::byte, 1>>, std::tuple<multi::gibi<1>>>::type;

template <_p::c_ValidFP T>
using tebibyte_t = typename make_unit<T, std::tuple<_p::dimension<standard::byte, 1>>, std::tuple<multi::tebi<1>>>::type;

template <_p::c_ValidFP T>
using pebibyte_t = typename make_unit<T, std::tuple<_p::dimension<standard::byte, 1>>, std::tuple<multi::pebi<1>>>::type;

//======== ======== Default Type ======== ========


using bit		= bit_t		<_p::default_fp>;
using byte		= byte_t	<_p::default_fp>;
using doublet	= doublet_t	<_p::default_fp>;
using quadlet	= quadlet_t	<_p::default_fp>;
using octlet	= octlet_t	<_p::default_fp>;

using kibibyte = kibibyte_t<_p::default_fp>;
using mebibyte = mebibyte_t<_p::default_fp>;
using gibibyte = gibibyte_t<_p::default_fp>;
using tebibyte = tebibyte_t<_p::default_fp>;
using pebibyte = pebibyte_t<_p::default_fp>;

} //namespace unit
