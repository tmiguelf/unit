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

#include <cstring>
#include <cstdint>
#include <type_traits>
#include <cmath>

template <typename T>
bool binarySame(const T& p_1, const T& p_2)
{
	if constexpr (std::is_same_v<long double, T> && !std::has_unique_object_representations_v<long double> && sizeof(long double) > 8)
	{
		return (p_1 == p_2) || (std::isnan(p_1) && std::isnan(p_2));
	}
	return memcmp(&p_1, &p_2, sizeof(T)) == 0;
}

template <typename T>
constexpr bool closeEnough(const T& p_1, const T& p_2, T p_epsilon)
{
	if(p_epsilon < 0) p_epsilon = -p_epsilon;
	const T diff = p_1 - p_2;
	return (diff <= p_epsilon) && (diff >= -p_epsilon);
}
