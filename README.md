# string lite: string facilities for C++98 and later

[![Language](https://img.shields.io/badge/C%2B%2B-98/11/14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://travis-ci.org/martinmoene/string-lite.svg?branch=master)](https://travis-ci.org/martinmoene/string-lite) [![Build status](https://ci.appveyor.com/api/projects/status/1ha3wnxtam547m8p?svg=true)](https://ci.appveyor.com/project/martinmoene/string-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Fstring-lite.svg)](https://github.com/martinmoene/string-lite/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://github.com/martinmoene/string-lite/blob/master/include/nonstd/string.hpp) [![Conan](https://img.shields.io/badge/on-conan-blue.svg)](https://conan.io/center/string-lite) [![Try it on wandbox](https://img.shields.io/badge/on-wandbox-blue.svg)](https://wandbox.org/) [![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](https://godbolt.org/)

**Contents**  

- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [License](#license)
- [Dependencies](#dependencies)
- [Installation and use](#installation-and-use)
- [Synopsis](#synopsis)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)

## Example usage

```cpp
#include "nonstd/string.hpp"

TODO
```

### Compile and run

```bash
prompt >g++ -std=c++11 -Wall -I../include -o 01-basic.exe 01-basic.cpp && 01-basic.exe
... TODO 
```

## In a nutshell

**string lite** is a single-file header-only library to provide various string algorithms.

*string lite* is inspired on...

**Features and properties of string lite** are ease of installation (single header), freedom of dependencies other than the standard library.

## License

*string lite* is distributed under the [Boost Software License](https://github.com/martinmoene/bit-lite/blob/master/LICENSE.txt).

Note: this repository contains a copy of several files from the [CsString library by Ansel Sermersheim and Barbara Geller](https://github.com/copperspice/cs_string) for testing purposes. The CsString library is released under the BSD 2-clause license. 

## Dependencies

*string lite* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).

## Installation and use

*string lite* is a single-file header-only library. Put `string.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.

## Synopsis

**Contents**  
[Documentation of `nonstd::string`](#documentation-of-nonstdstring)  
[Configuration](#configuration)  

### Documentation of `nonstd::string`


### API

| Kind               | Type or function                            | Notes |
|--------------------|---------------------------------------------|-------|
| **Type**           | **xxx**                                     | ... |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| **Free function**  | CharT **nullchr**()                         | null character of template type |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| Observers          | bool **is_empty**(CharT * s)                | true if C-string is empty |
| &nbsp;             | bool **is_empty**(StringT const & s)        | true if string is empty |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | bool **contains**(StringT const & s, CharT chr) | true if string contains chr |
| &nbsp;             | bool **contains**(StringT const & s, SubT const & substr) | true if string contains substring |
| &nbsp;             | bool **contains**(StringT const & s, std::regex const & substr) | true if string contains regular expression |
| &nbsp;             | bool **contains_re**(StringT const & s, ReT const & re) | true if string contains regular expression |
| &nbsp;             | bool **starts_with**(StringT const & s, CharT chr) | true if string starts with chr |
| &nbsp;             | bool **starts_with**(StringT const & s, SubT const & substr) | true if string starts with substring |
| &nbsp;             | bool **ends_with**(StringT const & s, CharT chr) | true if string ends with chr |
| &nbsp;             | bool **ends_with**(StringT const & s, SubT const & substr) | true if string ends with substring |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| Searching          | IterT **find_first**(StringT & s, SubT const & substr)       | provide iterator to substring |
| &nbsp;             | IterT **find_first**(StringT const & s, SubT const & substr) | provide const iterator to substring |
| &nbsp;             | IterT **find_last**(StringT & s, SubT const & substr)        | provide iterator to substring |
| &nbsp;             | IterT **find_last**(StringT const & s, SubT const & substr)  | provide const iterator to substring |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| Modifiers          | CharT * **clear**(CharT * s)                | make C-string empty |
| &nbsp;             | StringT & **clear**(StringT & s)            | make string empty |
| &nbsp;             | CharT * **to_lowercase**(CharT * p)         | convert C-string to lowercase |
| &nbsp;             | CharT * **to_uppercase**(CharT * p)         | convert C-string to uppercase |
| &nbsp;             | StringT & **to_lowercase**(StringT & s)     | convert string to lowercase  |
| &nbsp;             | StringT & **to_uppercase**(StringT & s)     | convert string to uppercase  |
| &nbsp;             | StringT **as_lowercase**(StringT const & s) | provide string converted to lowercase |
| &nbsp;             | StringT **as_uppercase**(StringT const & s) | provide string converted to uppercase |
| &nbsp;             | StringT & **replace_all**(StringT & s, FromT const & from, ToT const to) |xxx |
| &nbsp;             | StringT **replaced_all**(StringT const & s, FromT const & from, ToT const to) |xxx |
| &nbsp;             | StringT & **replace_first**(StringT & s, FromT const & from, ToT const to) |xxx |
| &nbsp;             | StringT **replaced_first**(StringT const & s, FromT const & from, ToT const to) |xxx |
| &nbsp;             | StringT & **replace_last**(StringT & s, FromT const & from, ToT const to) |xxx |
| &nbsp;             | StringT **replaced_last**(StringT const & s, FromT const & from, ToT const to) |xxx |
| &nbsp;             | &nbsp;                                                      |&nbsp;|
| Combining          | CharT * **append**(CharT * s, TailT const & tail)           |&nbsp;|
| &nbsp;             | StringT & **append**(StringT & s, TailT const & tail)       |&nbsp;|
| &nbsp;             | StringT **appended**(StringT const & s, TailT const & tail) |&nbsp;|
| &nbsp;             | StringT **join**(Coll const & coll, SepT const & sep)       |&nbsp;|
| &nbsp;             | split()                                                     |&nbsp;|

Note: with `StringT const &` the string type can also be `string_view`.

### Configuration

#### Tweak header

If the compiler supports [`__has_include()`](https://en.cppreference.com/w/cpp/preprocessor/include), *string lite* supports the [tweak header](https://vector-of-bool.github.io/2020/10/04/lib-configuration.html) mechanism. Provide your *tweak header* as `nonstd/string.tweak.hpp` in a folder in the include-search-path. In the tweak header, provide definitions as documented below, like `#define string_CPLUSPLUS 201103L`.

#### Standard selection macro

\-D<b>string\_CPLUSPLUS</b>=199711L  
Define this macro to override the auto-detection of the supported C++ standard, if your compiler does not set the `__cplusplus` macro correctly.

#### Disable exceptions
-D<b>optional_CONFIG_NO_EXCEPTIONS</b>=0
Define this to 1 if you want to compile without exceptions. If not defined, the header tries and detect if exceptions have been disabled (e.g. via `-fno-exceptions`). Default is undefined.

## Notes and references

TODO
