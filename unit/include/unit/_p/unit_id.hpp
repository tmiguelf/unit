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

#include <cstdint>
#include <type_traits>

namespace unit::_p
{

enum class unit_id: uint8_t
{
	time,
	length,
	mass,
	charge,
	temperature,
	luminous_intensity,
	angle,
	digital_info,
};

inline constexpr bool operator  < (unit_id p_1, unit_id p_2){ return static_cast<std::underlying_type_t<unit_id>>(p_1)  < static_cast<std::underlying_type_t<unit_id>>(p_2); }
inline constexpr bool operator == (unit_id p_1, unit_id p_2){ return static_cast<std::underlying_type_t<unit_id>>(p_1) == static_cast<std::underlying_type_t<unit_id>>(p_2); }
//inline constexpr bool operator != (unit_id p_1, unit_id p_2){ return static_cast<std::underlying_type_t<unit_id>>(p_1) != static_cast<std::underlying_type_t<unit_id>>(p_2); }


using default_fp = double;


} //namespace unit::_p

namespace unit::standard
{
	template<::unit::_p::unit_id ID>
	struct SI_standard;
} //namespace unit::standard

