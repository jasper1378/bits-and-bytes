# bits-and-bytes

## About

Bits and Bytes is a collection of random and (hopefully) useful C and C++ code snippets.

## Installation

All code snippets are packaged as single header files. Just copy the headers you wish to use into your project directory. Note that some headers depend on each other; a quick peek at the source code reveals for which ones that occurs. Projects using any C++ code snippets should probably be built with `-std=c++20`.

If you want to get fancy, add bits-and-bytes as a Git submodule to your project.
```
$ git submodule add https://github.com/jasper1378/bits-and-bytes
```

Bits-and-bytes is built using the Autotools; if your project is as well, you can add this as a subproject.
```
# configure.ac
...
AC_CONFIG_SUBDIRS([bits-and-bytes])
...

# Makefile.am
...
SUBDIRS += bits-and-bytes
AM_CPPFLAGS = -I$(top_srcdir)/bits-and-bytes/include
```

## Usage

Left as an exercise for the reader... All code snippets should be simple enough for you to figure out on your own.

## License

See [LICENSE.MD](LICENSE.MD) for details.
