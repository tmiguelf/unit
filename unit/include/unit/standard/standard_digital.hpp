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

#include <unit/_p/unit_id.hpp>

namespace unit::standard
{

struct digital_info_standard { static constexpr ::unit::_p::unit_id id = ::unit::_p::unit_id::digital_info; };


struct bit final: public digital_info_standard
{
	static constexpr long double gauge = 1.l;
};

struct byte final: public digital_info_standard
{
	static constexpr long double gauge = 8.l;
};

struct doublet final: public digital_info_standard
{
	static constexpr long double gauge = byte::gauge * 2.l;
};

struct quadlet final: public digital_info_standard
{
	static constexpr long double gauge = byte::gauge * 4.l;
};

struct octlet final: public digital_info_standard
{
	static constexpr long double gauge = byte::gauge * 8.l;
};

template<>
struct SI_standard<::unit::_p::unit_id::digital_info>
{
	using type = bit;
	static_assert(type::gauge == 1.l, "SI standard must have a gauge of 1");
};

} //namespace unit::standard
