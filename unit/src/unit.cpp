//======== ======== ======== ======== ======== ======== ======== ========
///	\file
///
///	\copyright
///		
//======== ======== ======== ======== ======== ======== ======== ========

#include "unit/unit.hpp"

namespace unit
{
using this_t = std::tuple<_p::dimension<standard::metre, 3>, _p::dimension<standard::second, 2>>;

using sort_t = _p::tuple_selection_sort<_p::less, this_t>::type;


using metre		= typename make_unit<double, std::tuple<_p::dimension<standard::metre, 1>>, std::tuple<>>::type;
using foot		= typename make_unit<double, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;
using foot2		= typename make_unit<long double, std::tuple<_p::dimension<standard::foot, 1>>, std::tuple<>>::type;


using metre1	= typename make_unit<double, std::tuple<_p::dimension<standard::metre, -1>>, std::tuple<>>::type;

using metre2	= typename make_unit<double, std::tuple<_p::dimension<standard::metre, 2>>, std::tuple<>>::type;


constexpr metre T1{2.l};
constexpr foot T2 = T1;
constexpr foot2 Foot2 = T2;


constexpr auto comp = T2 >= T1;

constexpr auto res = T1 + Foot2;

constexpr auto T3 = T2 / T1;
constexpr auto T4 = T2 * T1;

constexpr auto val = 1./ T1;

static_assert(std::is_same_v<decltype(val), const metre1>);



}
