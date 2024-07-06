#ifndef BITS_AND_BYTES_IS_SAME_TEMPLATE_HPP
#define BITS_AND_BYTES_IS_SAME_TEMPLATE_HPP

#include <type_traits>

namespace bits_and_bytes {
namespace is_same_template {

template <template <typename...> typename T, template <typename...> typename U>
struct is_same : std::false_type {};

template <template <typename...> typename T>
struct is_same<T, T> : std::true_type {};

template <template <typename...> typename T, template <typename...> typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;

} // namespace is_same_template
} // namespace bits_and_bytes

#endif
