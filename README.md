# generic-makefile

## About
This repository contains a pair of simple, generic, C++-focused Makefiles that I use in many of my projects.

## Installation
To use, simply copy the desired Makefile into your project's root directory. Please note that GNU Make is recommended.

## Usage
The repository contains two Makefiles, one for libraries (will create both static and shared libraries) and one for regular programs (will create a single binary).

### Targets
Both makefiles support the following targets.

- default
  - Equivalent to `release`
- `release`
  - Compile project using release settings
- `debug`
  - Compile project using debug settings
- `install`
  - Copy executable/library/headers to install location
- `uninstall`
  - Remove install files
- `clean`
  - Remove build files

### Git submodules
Both Makefiles support the use of Git submodules in your project. For now, submodules must be added, updated, and compiled manually (this will hopefully be automated soon). Once compiled, header files and static libraries found in submodules will be automatically included in the main project.

### Settings
The following fields should be edited in order for the Makefile to work properly with your project.

- `BIN_NAME`/`LIB_NAME`
  - The name of the compiled executable/library
  - Default: none
- `CXX`
  - The C++ compiler to use
  - Default: `g++`
- `COMPILE_FLAGS`
  - Flags that are passed to the compiler
  - Default: `-std=c++20 -Wall -Wextra -g`
- `RELEASE_COMPILE_FLAGS`
  - Flags that are passed to the compiler; only when making the `release` target
  - Default: `-O2 -DNDEBUG`
- `DEBUG_COMPILE_FLAGS`
  - Flags that are passed to the compiler; only when making the `debug` target
  - Default: `-Og -DDEBUG`
- `LINK_FLAGS`
  - Flags that are passed to the linker
  - Default: empty (program Makefile), `-shared` (library Makefile)
- `RELEASE_LINK_FLAGS`
  - Flags that are passed to the linker; only when making the `release` target
  - Default: empty
- `DEBUG_LINK_FLAGS`
  - Flags that are passed to the linker; only when making the `debug` target
  - Default: empty
- `SOURCE_DIRS`
  - Directories containg source files
  - Default: `./src`
- `SUBMODULE_DIR`
  - Directory containing optional Git submodules
  - Default: `./submodules`
- `INCLUDE_DIRS`
  - Directories containing header files
  - Default: `./include $(wildcard $(SUBMODULE_DIR)/*/include)`
- `LIBRARIES`
  - TODO
  - Default: TODO
- `SUBMODULE_OBJECTS`
  - Paths of Git submodule static libraries to be compiled into the main executable
  - Default: `$(wildcard $(SUBMODULE_DIR)/*/build/*.a)`
- `INSTALL_PATH`
  - Location of installed files; `/bin`, `/lib`, `/include` will be suffixed automatically
  - Default: `/usr/local`

## License
See [LICENSE.MD](LICENSE.MD) for details.
