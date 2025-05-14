#ifndef BITS_AND_BYTES_RANDOM_NUM_HPP
#define BITS_AND_BYTES_RANDOM_NUM_HPP

#include <cassert>
#include <chrono>
#include <random>

namespace bits_and_bytes {
template <typename T>
  requires(std::integral<T> || std::floating_point<T>)
class random_num {
private:
  template <typename U> struct distribution {};
  template <std::integral U> struct distribution<U> {
    using type = std::uniform_int_distribution<U>;
  };
  template <std::floating_point U> struct distribution<U> {
    using type = std::uniform_real_distribution<U>;
  };
  template <typename U> using distribution_t = typename distribution<U>::type;

private:
  std::seed_seq m_seed;
  std::mt19937 m_engine;
  distribution_t<T> m_dist;

public:
  random_num(T min, T max)
      : m_seed{[]() {
          std::random_device rd{};
          return std::seed_seq{
              static_cast<std::seed_seq::result_type>(
                  std::chrono::steady_clock::now().time_since_epoch().count()),
              rd(),
              rd(),
              rd(),
              rd(),
              rd(),
              rd(),
              rd(),
              rd()};
        }()},
        m_engine{m_seed}, m_dist{min, max} {}

  ~random_num() = default;

  random_num(const random_num &other) = delete;
  random_num(random_num &&other) = delete;

public:
  T operator()() { return m_dist(m_engine); }

public:
  random_num &operator=(const random_num &other) = delete;
  random_num &operator==(random_num &&other) = delete;
};
} // namespace bits_and_bytes

#endif
