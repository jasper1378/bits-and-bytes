#ifndef BITS_AND_BYTES_IS_SPECIALIZATION_OF_HPP
#define BITS_AND_BYTES_IS_SPECIALIZATION_OF_HPP

#include <type_traits>

namespace bits_and_bytes {
namespace is_specialization_of {

template <typename t_type, template <typename...> typename t_template>
struct is_specialization_of : std::false_type {};

template <template <typename...> typename t_template, typename... t_params>
struct is_specialization_of<t_template<t_params...>, t_template>
    : std::true_type {};

template <typename t_type, template <typename...> typename t_template>
inline constexpr bool is_specialization_of_v =
    is_specialization_of<t_type, t_template>::value;

} // namespace is_specialization_of
} // namespace bits_and_bytes

#endif
