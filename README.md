# string lite: string facilities for C++98 and later (In Progress)

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

**string lite** is a single-file header-only library to provide various string algorithms. Firstly meant to get you up and running easily, not necessarily to provide everything that might be useful and in the most efficient manner.

Creating *string lite* I've had a look at the [C++ standard](https://eel.is/c++draft/#strings), [Boost](https://www.boost.org/doc/libs/1_60_0/doc/html/string_algo.html), [Facebook Folly](https://github.com/facebook/folly/blob/master/folly/String.h), the [Python standard library](https://docs.python.org/3/library/string.html) and several algorithms I created over time.

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

| Kind               | Type or function                            | Notes |
|--------------------|---------------------------------------------|-------|
| **Type**           | **literal_delimiter**                       | a single string |
| &nbsp;             | **any_of_delimiter**                        | any of given characters |
| &nbsp;             | **fixed_delimiter**                         | fixed length |
| &nbsp;             | **limit_delimiter**                         | not implemented |
| &nbsp;             | **regex_delimiter**                         | regular expression |
| &nbsp;             | **char_delimiter**                          | character position |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| Utilities          | CharT **nullchr**()                         | null character of template type |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | size_t **size**(CharT \* s)                 | length of C-string |
| &nbsp;             | size_t **size**(CollT & c)                  | size of collection, C++string |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | CharT \* **begin**(CharT \* c)              | iterator to C-string |
| &nbsp;             | CharT \* **end**(CharT \* c)                | iterator past C-string |
| &nbsp;             | CharT const \* **cbegin**(CharT \* c)       | const iterator to C-string |
| &nbsp;             | CharT const \* **cend**(CharT \* c)         | const iterator past C-string |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | CollT::iterator **begin**(CollT & c)        | iterator to collection, C++string |
| &nbsp;             | CollT::iterator **end**(CollT & c)          | iterator past collection, C++string |
| &nbsp;             | CollT::const_iterator **cbegin**(CollT & c) | const iterator to collection, C++string |
| &nbsp;             | CollT::const_iterator **cend**(CollT & c)   | const iterator past collection, C++string |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| Observers          | bool **is_empty**(CharT \* s)               | true if C-string is empty |
| &nbsp;             | bool **is_empty**(StringT const & s)        | true if string is empty |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | bool **contains**(StringT const & s, CharT chr) | true if string contains chr |
| &nbsp;             | bool **contains**(StringT const & s, SubT const & substr) | true if string contains substring |
| &nbsp;             | bool **contains**(StringT const & s, std::regex const & substr) | true if string contains regular expression |
| &nbsp;             | bool **contains_re**(StringT const & s, ReT const & re) | true if string contains regular expression |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | bool **starts_with**(StringT const & s, CharT chr) | true if string starts with chr |
| &nbsp;             | bool **starts_with**(StringT const & s, SubT const & substr) | true if string starts with substring |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | bool **ends_with**(StringT const & s, CharT chr) | true if string ends with chr |
| &nbsp;             | bool **ends_with**(StringT const & s, SubT const & substr) | true if string ends with substring |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| Searching          | IterT **find_first**(StringT & s, SubT const & substr)       | provide iterator to substring |
| &nbsp;             | IterT **find_first**(StringT const & s, SubT const & substr) | provide const iterator to substring |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | IterT **find_last**(StringT & s, SubT const & substr)        | provide iterator to substring |
| &nbsp;             | IterT **find_last**(StringT const & s, SubT const & substr)  | provide const iterator to substring |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| Modifiers          | CharT \* **clear**(CharT \* s)              | make C-string empty |
| &nbsp;             | StringT & **clear**(StringT & s)            | make string empty |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | CharT \* **to_lowercase**(CharT \* p)       | convert C-string to lowercase |
| &nbsp;             | CharT \* **to_uppercase**(CharT \* p)       | convert C-string to uppercase |
| &nbsp;             | StringT & **to_lowercase**(StringT & s)     | convert string to lowercase  |
| &nbsp;             | StringT & **to_uppercase**(StringT & s)     | convert string to uppercase  |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | StringT **as_lowercase**(StringT const & s) | provide string converted to lowercase |
| &nbsp;             | StringT **as_uppercase**(StringT const & s) | provide string converted to uppercase |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | StringT & **replace_all**(StringT & s, FromT const & from, ToT const to) |xxx |
| &nbsp;             | StringT **replaced_all**(StringT const & s, FromT const & from, ToT const to) |xxx |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | StringT & **replace_first**(StringT & s, FromT const & from, ToT const to) |xxx |
| &nbsp;             | StringT **replaced_first**(StringT const & s, FromT const & from, ToT const to) |xxx |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | StringT & **replace_last**(StringT & s, FromT const & from, ToT const to) |xxx |
| &nbsp;             | StringT **replaced_last**(StringT const & s, FromT const & from, ToT const to) |xxx |
| &nbsp;             | &nbsp;                                                      |&nbsp;|
| Combining          | CharT \* **append**(CharT \* s, TailT const & tail)         |&nbsp;|
| &nbsp;             | StringT & **append**(StringT & s, TailT const & tail)       |&nbsp;|
| &nbsp;             | StringT **appended**(StringT const & s, TailT const & tail) |&nbsp;|
| &nbsp;             | &nbsp;                                      |&nbsp;|
| &nbsp;             | StringT **join**(Coll const & coll, SepT const & sep)       |&nbsp;|
| &nbsp;             | std::vector&lt;string_view&gt; **split**(string_view text, Delimiter d)    |&nbsp;|
| &nbsp;             | std::vector&lt;string_view&gt; **split**(string_view text, char const * d) |&nbsp;|

Note: with `StringT const &` the string type can also be `string_view`.

### Configuration

#### Tweak header

If the compiler supports [`__has_include()`](https://en.cppreference.com/w/cpp/preprocessor/include), *string lite* supports the [tweak header](https://vector-of-bool.github.io/2020/10/04/lib-configuration.html) mechanism. Provide your *tweak header* as `nonstd/string.tweak.hpp` in a folder in the include-search-path. In the tweak header, provide definitions as documented below, like `#define string_CPLUSPLUS 201103L`.

#### Standard selection macro

\-D<b>string\_CPLUSPLUS</b>=199711L  
Define this macro to override the auto-detection of the supported C++ standard, if your compiler does not set the `__cplusplus` macro correctly.

#### Disable exceptions
-D<b>string_CONFIG_NO_EXCEPTIONS</b>=0
Define this to 1 if you want to compile without exceptions. If not defined, the header tries and detect if exceptions have been disabled (e.g. via `-fno-exceptions`). Default is undefined.

## Notes and references

TODO

- [n3593 - std::split(): An algorithm for splitting strings](http://wg21.link/n3593). / https://isocpp.org/files/papers/n3593.html
- [Martin Broadhurst. How to split a string in C++. 2016](http://www.martinbroadhurst.com/how-to-split-a-string-in-c.html).

Appendix
--------

<a id="a1"></a>
### A.1 Compile-time information

In the test runner, the version of *string-lite* is available via tag `[.version]`. The following tags are available for information on the compiler and on the C++ standard library used: `[.compiler]`, `[.stdc++]`, `[.stdlanguage]` and `[.stdlibrary]`.

<a id="a2"></a>
### A.2 *string-lite* test specification

<details>
<summary>click to expand</summary>
<p>

```
string: Setting Windows console to print utf8 characters[unicode][windows]
is_empty: true if string is empty - char *
is_empty: true if string is empty - string
contains: true if string contains sub string - string-char
contains: true if string contains sub string - string-char*
contains: true if string contains sub string - string-string
contains: true if string contains sub string - string-string_view
contains: true if string contains sub string - string_view-string_view
contains: true if string contains regular expression - string-std::regexp
contains_re: true if string contains regular expression - string-char*
contains_re: true if string contains regular expression - string-string
starts_with: true if string starts with sub string - string-char
starts_with: true if string starts with sub string - string-char*
starts_with: true if string starts with sub string - string-string
starts_with: true if string starts with sub string - string-string_view
starts_with: true if string starts with sub string - string_view-string_view
ends_with: true if string ends with sub string - string-char
ends_with: true if string ends with sub string - string-char*
ends_with: true if string ends with sub string - string-string
ends_with: true if string ends with sub string - string-string_view
ends_with: true if string ends with sub string - string_view-string_view
find_first: iterator to sub string in string - string-char*
find_first: iterator to sub string in string - string-string
find_first: iterator to sub string in string - string-string_view
find_first: iterator to sub string in string_view - string_view-string_view
find_last: iterator to sub string in string - string-char*
find_last: iterator to sub string in string - string-string
find_last: iterator to sub string in string - string-string_view
find_last: iterator to sub string in string_view - string_view-string_view
clear: Makes string empty - char *
clear: Makes string empty - string
replace_all: Change all occurrences of sub string - string-char*
replace_all: Change all occurrences of sub string - string-string
replace_all: Change all occurrences of sub string - string-string_view
replaced_all: Return new string with all occurrences of sub string changed - char*-char*
replaced_all: Return new string with all occurrences of sub string changed - string-string
replaced_all: Return new string with all occurrences of sub string changed - string-string_view
replaced_all: Return new string with all occurrences of sub string changed - string_view-string_view [TODO]
replace_first: Change the first occurrence of sub string - char*-char*[TODO]
replace_first: Change the first occurrence of sub string - string-char*
replace_first: Change the first occurrence of sub string - string-string
replace_first: Change the first occurrence of sub string - string-string_view
replace_first: Change the first occurrence of sub string - string_view-string_view
replaced_first: Return new string with first occurrence of sub string changed - char*-char*
replaced_first: Return new string with first occurrence of sub string changed - string-string
replaced_first: Return new string with first occurrence of sub string changed - string-string_view
replaced_first: Return new string with first occurrence of sub string changed - string_view-string_view [TODO]
replace_last: Change the first occurrence of sub string - char*-char*[TODO]
replace_last: Change the last occurrence of sub string - string-char*
replace_last: Change the last occurrence of sub string - string-string
replace_last: Change the last occurrence of sub string - string-string_view
replace_last: Change the last occurrence of sub string - string_view-string_view
replaced_last: Return new string with last occurrence of sub string changed - char*-char*
replaced_last: Return new string with last occurrence of sub string changed - string-string
replaced_last: Return new string with last occurrence of sub string changed - string-string_view
replaced_last: Return new string with last occurrence of sub string changed - string_view-string_view [TODO]
to_lowercase: Makes string lowercase - char *
to_uppercase: Makes string uppercase - char *
to_lowercase: Makes string lowercase - string
to_uppercase: Makes string uppercase - string
as_lowercase: Return new string in lowercase - string
as_uppercase: Return new string in uppercase - string
append: Append a string to a string in-place - char*-char* - Note: be careful!
append: Append a string to a string in-place - string-char*
append: Append a string to a string in-place - string-string
append: Append a string to a string in-place - string-string_view
appended: Return new string with second string appended to first string - string-char*
appended: Return new string with second string appended to first string - string-string
appended: Return new string with second string appended to first string - string-string_view
join: [TODO]
split: literal_delimiter
split: any_of_delimiter
split: fixed_delimiter
split: regex_delimiter
split: char_delimiter
split: empty delimiters
clear: Makes string empty - string [unicode]
tweak header: Reads tweak header if supported [tweak]
```
