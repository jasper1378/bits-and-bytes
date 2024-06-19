#ifndef BITS_AND_BYTES_MOVE_ELEM_TO_HPP
#define BITS_AND_BYTES_MOVE_ELEM_TO_HPP

#include <iterator>
#include <utility>

namespace bits_and_bytes {
namespace move_elem_to {
template <typename t_iter>
inline void move_elem_to(t_iter from, t_iter to)
  requires std::random_access_iterator<t_iter>
{
  auto temp{std::move(*from)};
  if (to > from) {
    for (t_iter i{from}; i < to; ++i) {
      *i = std::move(*(i + 1));
    }
  } else if (from > to) {
    for (t_iter i{from + 1}; i-- > to;) {
      *i = std::move(*(i - 1));
    }
  }
  *to = std::move(temp);
}
} // namespace move_elem_to
} // namespace bits_and_bytes

#endif
