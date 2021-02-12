# string lite: string facilities for C++98 and later

[![Language](https://img.shields.io/badge/C%2B%2B-98/11/14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://travis-ci.org/martinmoene/string-lite.svg?branch=master)](https://travis-ci.org/martinmoene/string-lite) [![Build status](https://ci.appveyor.com/api/projects/status/1ha3wnxtam547m8p?svg=true)](https://ci.appveyor.com/project/martinmoene/string-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Fstring-lite.svg)](https://github.com/martinmoene/string-lite/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://github.com/martinmoene/string-lite/blob/master/include/nonstd/string.hpp) [![Conan](https://img.shields.io/badge/on-conan-blue.svg)](https://conan.io/center/string-lite) [![Try it on wandbox](https://img.shields.io/badge/on-wandbox-blue.svg)](https://wandbox.org/) [![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](https://godbolt.org/)

## License

*string lite* is distributed under the [Boost Software License](https://github.com/martinmoene/bit-lite/blob/master/LICENSE.txt).

Note: this repository contains a copy of several files from the [CsString library by Ansel Sermersheim and Barbara Geller](https://github.com/copperspice/cs_string) for testing purposes. The CsString library is released under the BSD 2-clause license. 

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
| &nbsp;             | bool **contains**(StringT const & s, SubT const & substr) | true if string contains substring (or -view) |
| &nbsp;             | bool **contains**(StringT const & s, std::regex const & substr) | true if string contains regular expressionst |
| &nbsp;             | bool **contains_re**(StringT const & s, ReT const & re) | true if string contains regular expression (or -view) |
| &nbsp;             | IterT **find**(StringT & s, SubT const & substr)          | provide iterator to substring |
| &nbsp;             | IterT **find**(StringT const & s, SubT const & substr)    | provide const iterator to substring |
| &nbsp;             | &nbsp;                                      |&nbsp;|
| Modifiers          | void **clear**(CharT * s)                   | make C-string empty |
| &nbsp;             | void **clear**(StringT & s)                 | make string empty |
| &nbsp;             | void **to_lowercase**(CharT * p)            | convert C-string to lowercase |
| &nbsp;             | void **to_uppercase**(CharT * p)            | convert C-string to uppercase |
| &nbsp;             | void **to_lowercase**(StringT & s)          | convert string to lowercase  |
| &nbsp;             | void **to_uppercase**(StringT & s)          | convert string to uppercase  |
| &nbsp;             | StringT **as_lowercase**(StringT const & s) | provide string converted to lowercase |
| &nbsp;             | StringT **as_uppercase**(StringT const & s) | provide string converted to uppercase |
