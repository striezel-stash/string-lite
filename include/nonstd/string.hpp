//
// Copyright (c) 2021-2021 Martin Moene
//
// https://github.com/martinmoene/string-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef NONSTD_STRING_LITE_HPP
#define NONSTD_STRING_LITE_HPP

#define string_lite_MAJOR  0
#define string_lite_MINOR  0
#define string_lite_PATCH  0

#define string_lite_VERSION  string_STRINGIFY(string_lite_MAJOR) "." string_STRINGIFY(string_lite_MINOR) "." string_STRINGIFY(string_lite_PATCH)

#define string_STRINGIFY(  x )  string_STRINGIFY_( x )
#define string_STRINGIFY_( x )  #x

// tweak header support:

#ifdef __has_include
# if __has_include(<nonstd/string.tweak.hpp>)
#  include <nonstd/string.tweak.hpp>
# endif
#define string_HAVE_TWEAK_HEADER  1
#else
#define string_HAVE_TWEAK_HEADER  0
//# pragma message("string.hpp: Note: Tweak header not supported.")
#endif

// C++ language version detection (C++20 is speculative):
// Note: VC14.0/1900 (VS2015) lacks too much from C++14.

#ifndef   string_CPLUSPLUS
# if defined(_MSVC_LANG ) && !defined(__clang__)
#  define string_CPLUSPLUS  (_MSC_VER == 1900 ? 201103L : _MSVC_LANG )
# else
#  define string_CPLUSPLUS  __cplusplus
# endif
#endif

#define string_CPP98_OR_GREATER  ( string_CPLUSPLUS >= 199711L )
#define string_CPP11_OR_GREATER  ( string_CPLUSPLUS >= 201103L )
#define string_CPP14_OR_GREATER  ( string_CPLUSPLUS >= 201402L )
#define string_CPP17_OR_GREATER  ( string_CPLUSPLUS >= 201703L )
#define string_CPP20_OR_GREATER  ( string_CPLUSPLUS >= 202000L )

// MSVC version:

#if defined(_MSC_VER ) && !defined(__clang__)
# define string_COMPILER_MSVC_VER  (_MSC_VER )
#else
# define string_COMPILER_MSVC_VER  0
#endif

// Presence of language and library features:

#define string_CPP11_120  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1800)
#define string_CPP11_140  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1900)

#define string_CPP17_000  (string_CPP17_OR_GREATER)

// Presence of C++11 language features:

#define string_HAVE_CONSTEXPR_11           string_CPP11_140
#define string_HAVE_NOEXCEPT               string_CPP11_140
#define string_HAVE_DEFAULT_FN_TPL_ARGS    string_CPP11_120
#define string_HAVE_EXPLICIT_CONVERSION    string_CPP11_120

// Presence of C++17 language features:

#define string_HAVE_NODISCARD              string_CPP17_000

// Presence of C++ language features:

#if string_HAVE_CONSTEXPR_11
# define string_constexpr constexpr
#else
# define string_constexpr /*constexpr*/
#endif

#if string_HAVE_NOEXCEPT
# define string_noexcept noexcept
#else
# define string_noexcept /*noexcept*/
#endif

#if string_HAVE_NODISCARD
# define string_nodiscard [[nodiscard]]
#else
# define string_nodiscard /*[[nodiscard]]*/
#endif

#if string_HAVE_EXPLICIT_CONVERSION
# define string_explicit_cv explicit
#else
# define string_explicit_cv /*explicit*/
#endif

// Additional includes:

#include <string>

namespace nonstd {

template< typename CharT >
CharT nullchr() string_noexcept
{
    return 0;
}

template< typename CharT >
void clear( CharT * s ) string_noexcept
{
    *s = nullchr<CharT>();
}

template< typename CharT, typename Traits = std::char_traits<CharT>, typename Allocator = std::allocator<CharT> >
void clear( std::basic_string<CharT, Traits, Allocator> & s ) string_noexcept
{
    s.clear();
}

} // namespace nonstd

#endif // NONSTD_STRING_LITE_HPP
