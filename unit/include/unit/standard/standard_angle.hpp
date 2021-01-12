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

#include <MathLib/constants.hpp>
#include "unit/_p/unit_id.hpp"

namespace unit::standard
{

struct angle_standard { static constexpr ::unit::_p::unit_id id = ::unit::_p::unit_id::angle; };


struct radian final: public angle_standard
{
	static constexpr long double gauge = 1.l;
};

struct grad final: public angle_standard
{
	static constexpr long double gauge = mathlib::pi<long double> / 200.l;
};

struct degree final: public angle_standard
{
	static constexpr long double gauge = mathlib::pi<long double> / 180.l;
};

struct arc_minute final: public angle_standard
{
	static constexpr long double gauge = degree::gauge / 60.l;
};

struct arc_second final: public angle_standard
{
	static constexpr long double gauge = degree::gauge / 3600.l;
};

struct turn final: public angle_standard
{
	static constexpr long double gauge = mathlib::tau<long double>;
};

template<>
struct SI_standard<::unit::_p::unit_id::angle>
{
	using type = radian;
	static_assert(type::gauge == 1.l, "SI standard must have a gauge of 1");
};

} //namespace unit::standard
