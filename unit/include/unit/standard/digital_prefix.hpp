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

#include <unit/_p/dimension.hpp>
#include "multipliers.hpp"

namespace unit::multi
{

template<int8_t rank> using yobi = _p::scalar<bi, 24 * rank>;
template<int8_t rank> using zebi = _p::scalar<bi, 21 * rank>;
template<int8_t rank> using exbi = _p::scalar<bi, 18 * rank>;
template<int8_t rank> using pebi = _p::scalar<bi, 15 * rank>;
template<int8_t rank> using tebi = _p::scalar<bi, 12 * rank>;
template<int8_t rank> using gibi = _p::scalar<bi,  9 * rank>;
template<int8_t rank> using mebi = _p::scalar<bi,  6 * rank>;
template<int8_t rank> using kibi = _p::scalar<bi,  3 * rank>;

} //namespace unit::multi
