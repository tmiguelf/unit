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

#include <unit/_p/dimension.hpp>
#include "multipliers.hpp"

namespace unit::multi
{

template<int8_t rank> using yotta	= _p::scalar<E, 24 * rank>;
template<int8_t rank> using zetta	= _p::scalar<E, 21 * rank>;
template<int8_t rank> using exa		= _p::scalar<E, 18 * rank>;
template<int8_t rank> using peta	= _p::scalar<E, 15 * rank>;
template<int8_t rank> using tera	= _p::scalar<E, 12 * rank>;
template<int8_t rank> using giga	= _p::scalar<E,  9 * rank>;
template<int8_t rank> using mega	= _p::scalar<E,  6 * rank>;
template<int8_t rank> using kilo	= _p::scalar<E,  3 * rank>;
template<int8_t rank> using hecto	= _p::scalar<E,  2 * rank>;
template<int8_t rank> using deca	= _p::scalar<E,  1 * rank>;

template<int8_t rank> using deci	= _p::scalar<E, - 1 * rank>;
template<int8_t rank> using centi	= _p::scalar<E, - 2 * rank>;
template<int8_t rank> using milli	= _p::scalar<E, - 3 * rank>;
template<int8_t rank> using micro	= _p::scalar<E, - 6 * rank>;
template<int8_t rank> using nano	= _p::scalar<E, - 9 * rank>;
template<int8_t rank> using pico	= _p::scalar<E, -12 * rank>;
template<int8_t rank> using femto	= _p::scalar<E, -15 * rank>;
template<int8_t rank> using atto	= _p::scalar<E, -18 * rank>;
template<int8_t rank> using zepto	= _p::scalar<E, -21 * rank>;
template<int8_t rank> using yocto	= _p::scalar<E, -24 * rank>;

} //namespace unit::multi
