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

#include <unit/_p/metric_type.hpp>

namespace unit::standard
{

struct temperature_metric final: public ::unit::_p::metric_base_t
{
	static constexpr std::u8string_view metric_name = u8"temperature"sv;
};

struct temperature_standard
{
	using metric_t = temperature_metric;
};


struct kelvin final: public temperature_standard
{
	static constexpr long double gauge = 1.l;
};

struct rankine final: public temperature_standard
{
	static constexpr long double gauge = 5.l / 9.l;
};

template<>
struct SI_standard<temperature_metric>
{
	using type = kelvin;
	static_assert(type::gauge == 1.l, "SI standard must have a gauge of 1");
};


struct celcius final
{
	using standard_t = kelvin;
	static constexpr long double offset = 273.15l;
};

struct fahrenheit final
{
	using standard_t = rankine;
	static constexpr long double offset = 459.67l;
};

} //namespace unit::standard
