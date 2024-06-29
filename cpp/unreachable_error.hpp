#ifndef BITS_AND_BYTES_UNREACHABLE_ERROR_HPP
#define BITS_AND_BYTES_UNREACHABLE_ERROR_HPP

#include <exception>

namespace bits_and_bytes {
class unreachable_error : public std::exception {

public:
  unreachable_error() noexcept : std::exception{} {}
  unreachable_error(const unreachable_error &other) noexcept
      : std::exception{other} {}

  virtual ~unreachable_error() {}

  unreachable_error &operator=(const unreachable_error &other) noexcept {
    std::exception::operator=(other);
    return *this;
  }

  virtual const char *what() const noexcept { return "unreachable error"; }
};
} // namespace bits_and_bytes

#endif
