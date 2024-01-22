# generic-makefile

## About
This repository contains a couple of simple, generic, C/C++-focused Makefiles that I use in many of my projects.

## Installation
To use, simply copy the desired Makefile into your project's root directory. Please note that these Makefiles have only been tested with GNU Make.

## Usage
The repository contains C++ and C Makefiles for libraries (will create both static and shared libraries) and for regular programs (will create a single binary). Please note that GNU Make is unable to deal with spaces in file paths.

### Targets
All Makefiles support the following targets.

- default
  - Equivalent to `release`
- `release`
  - Compile project using release settings
- `debug`
  - Compile project using debug settings
- `install`
  - Copy executable/library and header files to install location
- `uninstall`
  - Remove installed executable/library and header files
- `clean`
  - Remove build files

### Project structure
The default Makefile settings assume that your project has the following directory structure.
```
.
├── include
├── Makefile
├── source
└── submodules
    └── my_library
        ├── include
        ├── include_install
        ├── Makefile
        └── source
```

### Git submodules
All Makefiles support the use of Git submodules in your project. For now, submodules must be added, updated, and compiled manually (this will hopefully be automated soon). Once compiled, static libraries found in submodules will be automatically included in the main project.

### Settings
The following fields should be edited in order for the Makefile to work properly with your project.

- `BIN_NAME` (program Makefile)
  - The name of the compiled executable
  - Default: none
- `LIB_NAME` (library Makefile)
  - The name of the compiled library
  - Default: none
- `VERSION_MAJOR`
  - The major version number
  - Default: `0`
- `VERSION_MINOR`
  - The minor version number
  - Default: `0`
- `CXX` (C++ Makefile)
  - The C++ compiler to use
  - Default: `g++`
- `CC` (C Makefile)
  - The C compiler to use
  - Default: `gcc`
- `COMPILE_FLAGS` (C++ Makefile)
  - Flags that are passed to the compiler
  - Default: `-std=c++20 -Wall -Wextra -g`
- `COMPILE_FLAGS` (C Makefile)
  - Flags that are passed to the compiler
  - Default: `-std=c17 -Wall -Wextra -g`
- `RELEASE_COMPILE_FLAGS`
  - Flags that are passed to the compiler; only when making the `release` target
  - Default: `-O2 -DNDEBUG`
- `DEBUG_COMPILE_FLAGS`
  - Flags that are passed to the compiler; only when making the `debug` target
  - Default: `-Og -DDEBUG`
- `LINK_FLAGS`
  - Flags that are passed to the linker
  - Default: empty
- `RELEASE_LINK_FLAGS`
  - Flags that are passed to the linker; only when making the `release` target
  - Default: empty
- `DEBUG_LINK_FLAGS`
  - Flags that are passed to the linker; only when making the `debug` target
  - Default: empty
- `LIBRARIES`
  - Libraries to link against
  - Default: empty
- `SOURCE_FILE_EXT` (C++ Makefile)
  - The file extension used by source files
  - Default: `.cpp`
- `SOURCE_FILE_EXT` (C Makefile)
  - The file extension used by source files
  - Default: `.c`
- `HEADER_FILE_EXT` (C++ Makefile)
  - The file extension used by header files
  - Default: `.hpp`
- `HEADER_FILE_EXT` (C Makefile)
  - The file extension used by header files
  - Default: `.h`
- `SOURCE_DIRS`
  - Directories containg source files
  - Default: `./source`
- `INCLUDE_DIRS`
  - Directories containing header files
  - Default: `./include`
- `INCLUDE_INSTALL_DIRS` (library Makefile)
  - Directories containing header files to be installed
  - Default: `./install_install`
- `SUBMODULE_DIR`
  - Directory containing optional Git submodules
  - Default: `./submodules`
- `INSTALL_PATH`
  - Location of installed files; `/bin`, `/lib`, and `/include` will be suffixed automatically
  - Default: `/usr/local`

## License
See [LICENSE.MD](LICENSE.MD) for details.
