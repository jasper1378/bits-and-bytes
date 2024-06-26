#ifndef BITS_AND_BYTES_CONSTEXPR_HASH_STRING_HPP
#define BITS_AND_BYTES_CONSTEXPR_HASH_STRING_HPP

#include <bit>
#include <climits>
#include <cstddef>
#include <cstring>
#include <string>
#include <string_view>
#include <type_traits>

namespace bits_and_bytes {
namespace constexpr_hash_string {
// copied from GCC implementation of std::hash<std::string>, modified to execute
// at compile time

constexpr std::size_t hash(const std::string &str);
constexpr std::size_t hash(const std::string_view str);
constexpr std::size_t hash(const char *str);

namespace impl {
inline constexpr std::size_t strlen(const char *str);
inline std::size_t unaligned_load(const char *p);
template <typename T = void>
inline constexpr std::size_t unaligned_load_c(const char *p);
inline constexpr std::size_t load_bytes(const char *p, int n);
inline constexpr std::size_t shift_mix(std::size_t v);

static constexpr std::size_t k_default_seed{0xc70f6907UL};

template <std::size_t sizeof_size_t> struct hash {
  static constexpr std::size_t do_hash(const char *ptr, std::size_t len,
                                       std::size_t seed);
};

template <> struct hash<4> {
  static constexpr std::size_t do_hash(const char *ptr, std::size_t len,
                                       std::size_t seed);
};

template <> struct hash<8> {
  static constexpr std::size_t do_hash(const char *ptr, std::size_t len,
                                       std::size_t sed);
};
} // namespace impl

constexpr std::size_t hash(const std::string &str) {
  return impl::hash<sizeof(std::size_t)>::do_hash(str.data(), str.size(),
                                                  impl::k_default_seed);
}

constexpr std::size_t hash(const std::string_view str) {
  return impl::hash<sizeof(std::size_t)>::do_hash(str.data(), str.size(),
                                                  impl::k_default_seed);
}

constexpr std::size_t hash(const char *str) {
  return impl::hash<sizeof(std::size_t)>::do_hash(str, impl::strlen(str),
                                                  impl::k_default_seed);
}

inline constexpr std::size_t impl::strlen(const char *str) {
  const char *end{str};
  while (*end != '\0') {
    ++end;
  }
  return end - str;
}

inline std::size_t impl::unaligned_load(const char *p) {
  std::size_t result;
  std::memcpy(&result, p, sizeof(result));
  return result;
}

template <typename T>
inline constexpr std::size_t impl::unaligned_load_c(const char *p) {
  std::size_t result{0};
  if constexpr (std::endian::native == std::endian::big) {
    for (std::size_t i{0}; i < sizeof(result); ++i) {
      result |= (static_cast<decltype(result)>(p[i])
                 << (CHAR_BIT * (sizeof(result) - (i + 1))));
    }
  } else {
    for (std::size_t i{0}; i < sizeof(result); ++i) {
      result |= (static_cast<decltype(result)>(p[i]) << (CHAR_BIT * i));
    }
  }
  return result;
}

inline constexpr std::size_t impl::load_bytes(const char *p, int n) {
  std::size_t result = 0;
  --n;
  do {
    result = (result << 8) + static_cast<unsigned char>(p[n]);
  } while (--n >= 0);
  return result;
}

inline constexpr std::size_t impl::shift_mix(std::size_t v) {
  return v ^ (v >> 47);
}

template <std::size_t sizeof_size_t>
constexpr std::size_t impl::hash<sizeof_size_t>::do_hash(const char *ptr,
                                                         std::size_t len,
                                                         std::size_t seed) {
  std::size_t hash = seed;
  const char *cptr = reinterpret_cast<const char *>(ptr);
  for (; len; --len) {
    hash = (hash * 131) + *cptr++;
  }
  return hash;
}

constexpr std::size_t impl::hash<4>::do_hash(const char *ptr, std::size_t len,
                                             std::size_t seed) {
  const std::size_t m = 0x5bd1e995;
  std::size_t hash = seed ^ len;
  const char *buf = static_cast<const char *>(ptr);

  while (len >= 4) {
    std::size_t k;
    if (std::is_constant_evaluated()) {
      k = unaligned_load_c(buf);
    } else {
      k = unaligned_load(buf);
    }
    k *= m;
    k ^= k >> 24;
    k *= m;
    hash *= m;
    hash ^= k;
    buf += 4;
    len -= 4;
  }

  switch (len) {
  case 3:
    hash ^= static_cast<unsigned char>(buf[2]) << 16;
  case 2:
    hash ^= static_cast<unsigned char>(buf[1]) << 8;
  case 1:
    hash ^= static_cast<unsigned char>(buf[0]);
    hash *= m;
  }

  hash ^= hash >> 13;
  hash *= m;
  hash ^= hash >> 15;
  return hash;
}

constexpr std::size_t impl::hash<8>::do_hash(const char *ptr, std::size_t len,
                                             std::size_t seed) {
  /*static*/ const std::size_t mul =
      (((std::size_t)0xc6a4a793UL) << 32UL) + (size_t)0x5bd1e995UL;
  const char *const buf = static_cast<const char *>(ptr);

  const std::size_t len_aligned = len & ~(std::size_t)0x7;
  const char *const end = buf + len_aligned;
  std::size_t hash = seed ^ (len * mul);
  for (const char *p = buf; p != end; p += 8) {
    std::size_t data;
    if (std::is_constant_evaluated()) {
      data = shift_mix(unaligned_load_c(p) * mul) * mul;
    } else {
      data = shift_mix(unaligned_load(p) * mul) * mul;
    }
    hash ^= data;
    hash *= mul;
  }
  if ((len & 0x7) != 0) {
    const std::size_t data = load_bytes(end, len & 0x7);
    hash ^= data;
    hash *= mul;
  }
  hash = shift_mix(hash) * mul;
  hash = shift_mix(hash);
  return hash;
}

} // namespace constexpr_hash_string
} // namespace bits_and_bytes

#endif
