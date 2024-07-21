# Prelude.
AC_PREREQ([2.72])
AC_INIT([bits-and-bytes], [0.0])
AC_CONFIG_SRCDIR([src/enum_flag_operators.hpp])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.17 foreign tar-ustar -Wall -Werror])
AC_LANG([C++])

# Checks for programs.
AC_PROG_CC
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
AC_CHECK_FUNCS([pow])
AC_CHECK_FUNCS([sqrt])

# Output files.
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile include/bits-and-bytes/Makefile])
AC_OUTPUT
