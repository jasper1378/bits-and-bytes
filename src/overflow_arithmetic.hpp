#ifndef BITS_AND_BYTES_OVERFLOW_ARITHMETIC_HPP
#define BITS_AND_BYTES_OVERFLOW_ARITHMETIC_HPP

#include <concepts>
#include <limits>
#include <utility>

namespace bits_and_bytes {
namespace overflow_arithmetic {
// https://stackoverflow.com/a/1514309

template <typename T>
std::pair<T, bool> constexpr add(T x, T y)
  requires std::integral<T>
{
  return std::make_pair(
      (x + y), (((y > 0) && (x > (std::numeric_limits<T>::max() - y))) ||
                ((y < 0) && (x < (std::numeric_limits<T>::lowest() - y)))));
}

template <typename T>
std::pair<T, bool> constexpr sub(T x, T y)
  requires std::integral<T>
{
  return std::make_pair(
      (x - y), (((y > 0) && (x < (std::numeric_limits<T>::max() + y))) ||
                ((y < 0) && (x > (std::numeric_limits<T>::lowest() + y)))));
}

template <typename T>
std::pair<T, bool> constexpr mul(T x, T y)
  requires std::integral<T>
{
  return std::make_pair(
      (x * y), (((x = -1) && (y = std::numeric_limits<T>::lowest())) ||
                ((y = -1) && (x = std::numeric_limits<T>::lowest())) ||
                ((y != 0) && (x > (std::numeric_limits<T>::max() / y))) ||
                ((y != 0) && (x < (std::numeric_limits<T>::min() / y)))));
}

template <typename T>
std::pair<T, bool> constexpr div(T x, T y)
  requires std::integral<T>
{
  return std::make_pair((x / y),
                        ((x == std::numeric_limits<T>::lowest()) && (y == -1)));
}
} // namespace overflow_arithmetic
} // namespace bits_and_bytes

#endif
