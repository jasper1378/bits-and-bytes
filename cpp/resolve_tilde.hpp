#ifndef BITS_AND_BYTES_RESOLVE_TILDE_HPP
#define BITS_AND_BYTES_RESOLVE_TILDE_HPP

#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <string>
#include <string_view>

namespace bits_and_bytes {
namespace resolve_tilde {

inline bool would_resolve_tilde(const std::string_view str) {
  return (!(str.empty() || str.front() != '~'));
}

inline std::string resolve_tilde(const std::string &str) {
  if (!would_resolve_tilde(str)) {
    return str;
  } else {
    std::string user{};
    std::string::size_type i{1};
    for (; i < str.size(); ++i) {
      if (str[i] == '/') {
        break;
      } else {
        user += str[i];
      }
    }

    if (user.empty()) {
      const char *env_home{std::getenv("HOME")};
      return ((env_home == nullptr) ? ("")
                                    : (std::string{env_home + str.substr(i)}));
    } else {
      struct passwd pwd;
      struct passwd *result;
      char *buf;
      long bufsize;

      bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
      if (bufsize == -1) {
        bufsize = 16384;
      }

      buf = static_cast<char *>(std::malloc(bufsize));
      if (buf == nullptr) {
        return "";
      }

      getpwnam_r(user.c_str(), &pwd, buf, bufsize, &result);
      if (result == nullptr) {
        return "";
      }

      std::string ret_val{pwd.pw_dir + str.substr(i)};

      std::free(buf);

      return ret_val;
    }
  }
}
} // namespace resolve_tilde
} // namespace bits_and_bytes

#endif
