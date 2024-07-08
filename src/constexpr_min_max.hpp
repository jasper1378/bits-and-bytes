#ifndef BITS_AND_BYTES_CONSTEXPR_MIN_MAX_HPP
#define BITS_AND_BYTES_CONSTEXPR_MIN_MAX_HPP

namespace bits_and_bytes {
namespace constexpr_min_max {
template <typename T> consteval auto max(const T &x) { return x; }
template <typename T, typename... U>
consteval auto max(const T &x, const U &...y) {
  return ((x > max(y...)) ? (x) : (max(y...)));
}

template <typename T> auto consteval min(const T &x) { return x; }
template <typename T, typename... U>
consteval auto min(const T &x, const U &...y) {
  return ((x < min(y...)) ? (x) : (min(y...)));
}
} // namespace constexpr_min_max
} // namespace bits_and_bytes

#endif
