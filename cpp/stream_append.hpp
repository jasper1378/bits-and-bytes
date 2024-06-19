#ifndef BITS_AND_BYTES_STREAM_APPEND_HPP
#define BITS_AND_BYTES_STREAM_APPEND_HPP

#include <cstring>
#include <initializer_list>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <type_traits>

namespace bits_and_bytes {
namespace stream_append {
template <typename t_char, typename t_traits = std::char_traits<t_char>,
          typename t_allocator = std::allocator<t_char>>
std::basic_ostream<t_char, t_traits> &
operator+=(std::basic_ostream<t_char, t_traits> &os,
           const std::basic_string<t_char, t_traits, t_allocator> &s) {
  os.write(s.data(), s.size());
  return os;
}

template <typename t_char, typename t_traits = std::char_traits<t_char>>
std::basic_ostream<t_char, t_traits> &
operator+=(std::basic_ostream<t_char, t_traits> &os, t_char c) {
  os.put(c);
  return os;
}

template <typename t_char, typename t_traits = std::char_traits<t_char>>
std::basic_ostream<t_char, t_traits> &
operator+=(std::basic_ostream<t_char, t_traits> &os, const t_char *s) {
  os.write(s, std::strlen(s));
  return os;
}

template <typename t_char, typename t_traits = std::char_traits<t_char>>
std::basic_ostream<t_char, t_traits> &
operator+=(std::basic_ostream<t_char, t_traits> &os,
           std::initializer_list<t_char> i) {
  os.write(std::data(i), i.size());
  return os;
}

template <typename t_char, typename t_traits = std::char_traits<t_char>,
          typename t_string_view_like>
  requires((std::is_convertible_v<const t_string_view_like &,
                                  std::basic_string_view<t_char, t_traits>> ==
            true) &&
           (std::is_convertible_v<const t_string_view_like &, const t_char *> ==
            false))
std::basic_ostream<t_char, t_traits> &
operator+=(std::basic_ostream<t_char, t_traits> &os,
           const t_string_view_like s) {
  os.write(s.data(), s.size());
  return os;
}
} // namespace stream_append
} // namespace bits_and_bytes

#endif
