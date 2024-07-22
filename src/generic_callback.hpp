#ifndef BITS_AND_BYTES_GENERIC_CALLBACK_HPP
#define BITS_AND_BYTES_GENERIC_CALLBACK_HPP

#include <utility>

namespace bits_and_bytes {
template <typename... T> struct generic_callback {
  void (*func)(void *userdata, T... args);
  void *userdata;
  template <typename... U> void call(U &&...args) {
    func(userdata, std::forward<U>(args)...);
  }
};
}
#endif
