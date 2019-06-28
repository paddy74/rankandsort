[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Rank and Sort

A modular library for conducting ranking and sorting operations on a set of documents.

## Getting started

### Adding to your project

The recommended way to add this library to your project is by including the following in your CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 3.13)
project(myProject)

include_directories("path/to/rankandsort/include")
add_subdirectory("path/to/rankandsort/")

add_executable(myProject myProject_SOURCES)
# or `add_library(myProject myProject_SOURCES)

target_link_libraries(myProject rankandsort)
```

### Usage

This library's primary header file is `rankandsort.hpp` and can be included in your source files with the following:

```cpp
#include <rankandsort/rankandsort.hpp>
```

An example case can be found in [samples/src/example.cpp](samples/src/example.cpp).

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](tags).

## Authors

- **Patrick Cox** - [paddy74](https://github.com/paddy74)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
