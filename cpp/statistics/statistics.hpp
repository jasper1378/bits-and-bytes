#ifndef BITS_AND_BYTES_STATISTICS_HPP
#define BITS_AND_BYTES_STATISTICS_HPP

#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <iterator>

namespace bits_and_bytes {
namespace statistics {
template <typename t_num = double, typename t_iterator>
  requires std::floating_point<t_num>
t_num min(t_iterator first, t_iterator last) {
  return *std::min_element(first, last);
}

template <typename t_num = double, typename t_iterator>
  requires std::floating_point<t_num>
t_num max(t_iterator first, t_iterator last) {
  return *std::max_element(first, last);
}

template <typename t_num = double, typename t_iterator>
  requires std::floating_point<t_num>
t_num mean(t_iterator first, t_iterator last) {
  t_num mean{0};
  for (t_iterator i{first}; i != last; ++i) {
    mean += *i;
  }
  mean /= std::distance(first, last);

  return mean;
}

template <typename t_num = double, typename t_iterator>
  requires std::floating_point<t_num>
t_num stdev(t_iterator first, t_iterator last, const t_num mean,
            const bool bessel_correction) {
  std::size_t size{static_cast<std::size_t>(std::distance(first, last))};

  t_num sum_square_diffs{0};
  for (t_iterator i{first}; i != last; ++i) {
    sum_square_diffs += std::pow((*i - mean), 2);
  }

  return (std::sqrt((sum_square_diffs) /
                    ((bessel_correction) ? (size - 1) : (size))));
}

template <typename t_num = double, typename t_iterator>
  requires std::floating_point<t_num>
t_num stdev(t_iterator first, t_iterator last, const bool bessel_correction) {
  return stdev(first, last, mean(first, last), bessel_correction);
}

namespace online {
// https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm

template <typename t_num = double>
  requires(std::floating_point<t_num> || std::integral<t_num>)
struct min_state {
  std::size_t count;
  t_num min;
};
template <typename t_num = double>
  requires(std::floating_point<t_num> || std::integral<t_num>)
t_num min(const t_num num, min_state<t_num> &state) {
  state.min = (((num < state.min) || (state.count == 0)) ? (num) : (state.min));
  ++state.count;
  return state.min;
}

template <typename t_num = double>
  requires(std::floating_point<t_num> || std::integral<t_num>)
struct max_state {
  std::size_t count;
  t_num max;
};
template <typename t_num = double>
  requires(std::floating_point<t_num> || std::integral<t_num>)
t_num max(const t_num num, max_state<t_num> &state) {
  state.max = (((num > state.max) || (state.count == 0)) ? (num) : (state.max));
  ++state.count;
  return state.max;
}

template <typename t_num = double>
  requires std::floating_point<t_num>
struct mean_state {
  std::size_t count;
  t_num mean;
};
template <typename t_num = double>
  requires std::floating_point<t_num>
t_num mean(const t_num num, mean_state<t_num> &state) {
  state.mean = ((state.count == 0)
                    ? (num)
                    : (state.mean + ((num - state.mean) / (state.count + 1))));
  ++state.count;
  return state.mean;
}

template <typename t_num = double>
  requires std::floating_point<t_num>
struct stdev_state {
  std::size_t count;
  mean_state<t_num> mean;
  t_num sum_squares_diffs;
};
template <typename t_num = double>
  requires std::floating_point<t_num>
t_num stdev(const t_num num, stdev_state<t_num> &state,
            const bool bessel_correction) {
  const t_num mean_previous = state.mean.mean;
  mean(num, state.mean);
  state.sum_squares_diffs =
      ((state.count == 0)
           ? (0)
           : (state.sum_squares_diffs +
              ((num - mean_previous) * (num - state.mean.mean))));
  ++state.count;
  return std::sqrt(state.sum_squares_diffs /
                   ((bessel_correction) ? (state.count - 1) : (state.count)));
}
} // namespace online
} // namespace statistics
} // namespace bits_and_bytes

#endif
