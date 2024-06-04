#ifndef BITS_AND_BYTES_TIMER_HPP
#define BITS_AND_BYTES_TIMER_HPP

#include <chrono>
#include <utility>

namespace bits_and_bytes {

class timer {
private:
  using clock_type = std::chrono::steady_clock;
  using second_type = std::chrono::duration<double, std::ratio<1>>;

private:
  std::chrono::time_point<clock_type> m_time;

public:
  timer() : m_time{clock_type::now()} {}

  timer(const timer &other) : m_time{other.m_time} {}

  timer(timer &&other) noexcept : m_time{other.m_time} {}

  ~timer() {}

public:
  void reset() { m_time = clock_type::now(); }

  double elapsed() const {
    return std::chrono::duration_cast<second_type>(clock_type::now() - m_time)
        .count();
  }

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
