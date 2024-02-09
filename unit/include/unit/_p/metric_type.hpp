#pragma once

#include <string_view>

namespace unit::_p
{
	struct metric_base_t{};


	template<typename T>
	struct is_metric_t : public std::false_type {};

	template<typename T> requires (
		std::is_base_of_v<metric_base_t, T> &&
		std::is_convertible_v<const volatile T*, const volatile metric_base_t*> &&
		std::is_final_v<T> &&
		std::is_same_v<std::u8string_view const, decltype(T::metric_name)>
		)
	struct is_metric_t<T> : public std::true_type {};

	template<typename T>
	concept c_metric_t = is_metric_t<T>::value;


	template<c_metric_t T1, c_metric_t T2>
	inline constexpr bool compare_less_metric_v = (T1::metric_name < T2::metric_name);

	template<c_metric_t T1, c_metric_t T2>
	inline constexpr bool compare_equal_metric_v = (T1::metric_name == T2::metric_name);

	using default_fp = double;
}

namespace unit::standard
{
	using std::literals::string_view_literals::operator""sv;



template<::unit::_p::c_metric_t ID>
struct SI_standard;

}
