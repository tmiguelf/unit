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

#include <cstring>
#include <cstdint>
#include <type_traits>
#include <bit>


union aux_long_double
{
	uint64_t _int[2];
	long double _fp;
};



template <typename T>
bool binarySame(const T& p_1, const T& p_2)
{
	if constexpr(std::is_same_v<long double, T> && sizeof(T) == 16)
	{
		aux_long_double aux1;
		aux_long_double aux2;
		aux1._fp = p_1;
		aux2._fp = p_2;

		if constexpr (std::endian::native == std::endian::big)
		{
			constexpr uint64_t mask = 0x00'00'00'00'00'00'11'11;
			aux1._int[0] &= mask;
			aux2._int[0] &= mask;
		}
		else //unsure if this is correct
		{
			constexpr uint64_t mask = 0x00'00'00'00'00'00'11'11;
			aux1._int[1] &= mask;
			aux2._int[1] &= mask;
		}

		return memcmp(&aux1, &aux2, sizeof(aux_long_double)) == 0;
	}
	return memcmp(&p_1, &p_2, sizeof(T)) == 0;
}

template <typename T>
bool closeEnough(const T& p_1, const T& p_2, const T p_epsilon)
{
	const T diff = p_1 - p_2;
	return (diff <= p_epsilon) && (diff >= -p_epsilon);
}
