#ifndef BITS_AND_BYTES_TIMER_HPP
#define BITS_AND_BYTES_TIMER_HPP

#include <chrono>
#include <utility>

namespace bits_and_bytes {

class timer {
public:
  timer();

  timer(const timer &other);

  timer(timer &&other) noexcept;

  ~timer();

private:
  using clock_type = std::chrono::steady_clock;
  using second_type = std::chrono::duration<double, std::ratio<1>>;

private:
  std::chrono::time_point<clock_type> m_time;

public:
  void reset();
  double elapsed() const;

public:
  timer &operator=(const timer &other);
  timer &operator=(timer &&other) noexcept;
};

} // namespace bits_and_bytes

bits_and_bytes::timer::timer() : m_time{clock_type::now()} {}

bits_and_bytes::timer::timer(const timer &other) : m_time{other.m_time} {}

bits_and_bytes::timer::timer(timer &&other) noexcept : m_time{other.m_time} {}

bits_and_bytes::timer::~timer() {}

void bits_and_bytes::timer::reset() { m_time = clock_type::now(); }

double bits_and_bytes::timer::elapsed() const {
  return std::chrono::duration_cast<second_type>(clock_type::now() - m_time)
      .count();
}

bits_and_bytes::timer &bits_and_bytes::timer::operator=(const timer &other) {
  m_time = other.m_time;

  return *this;
}

bits_and_bytes::timer &
bits_and_bytes::timer::operator=(timer &&other) noexcept {
  m_time = std::move(other.m_time);

  return *this;
}

#endif
