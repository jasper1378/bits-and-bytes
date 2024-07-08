# Prelude.
AC_PREREQ([2.72])
AC_INIT([bits-and-bytes], [0.0])
AC_CONFIG_SRCDIR([include/bits-and-bytes/enum_flag_operators.hpp])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])
AC_LANG([C++])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADER_STDBOOL
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNC([pow])
AC_CHECK_FUNC([sqrt])

# Output files.
AC_CONFIG_FILES([Makefile include/bits-and-bytes/Makefile])
AC_OUTPUT
