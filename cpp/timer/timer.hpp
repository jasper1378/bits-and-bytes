#ifndef BITS_AND_BYTES_TIMER_HPP
#define BITS_AND_BYTES_TIMER_HPP

#include <chrono>
#include <ratio>
#include <utility>

#include "../type_traits/type_traits.hpp"

namespace bits_and_bytes {

template <typename t_duration = std::chrono::duration<double, std::ratio<1>>,
          typename t_clock = std::chrono::steady_clock>
  requires(bits_and_bytes::type_traits::is_specialization_of_v<
               t_duration, std::chrono::duration>,
           std::chrono::is_clock_v<t_clock>)
class timer {
private:
  std::chrono::time_point<t_clock> m_time;

public:
  timer() : m_time{t_clock::now()} {}

  timer(const timer &other) : m_time{other.m_time} {}

  timer(timer &&other) noexcept : m_time{other.m_time} {}

  ~timer() {}

public:
  void reset() { m_time = t_clock::now(); }

  t_duration elapsed() const {
    return std::chrono::duration_cast<t_duration>(t_clock::now() - m_time);
  }

  double elapsed_c() const { return elapsed().count(); }

public:
  timer &operator=(const timer &other) {
    m_time = other.m_time;
    return *this;
  }

  timer &operator=(timer &&other) noexcept {
    m_time = std::move(other.m_time);
    return *this;
  }
};

} // namespace bits_and_bytes

#endif
