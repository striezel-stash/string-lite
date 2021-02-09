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

#define string_CPP11_110  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1700)
#define string_CPP11_120  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1800)
#define string_CPP11_140  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1900)

#define string_CPP17_000  (string_CPP17_OR_GREATER)
#define string_CPP17_140  (string_CPP17_OR_GREATER || string_COMPILER_MSVC_VER >= 1900)

// Presence of C++11 language features:

#define string_HAVE_CONSTEXPR_11            string_CPP11_140
#define string_HAVE_NOEXCEPT                string_CPP11_140
#define string_HAVE_NULLPTR                 string_CPP11_100
#define string_HAVE_DEFAULT_FN_TPL_ARGS     string_CPP11_120
#define string_HAVE_EXPLICIT_CONVERSION     string_CPP11_120

// Presence of C++17 language features:

#define string_HAVE_NODISCARD               string_CPP17_000

// Presence of C++ library features:

#define string_HAVE_TYPE_TRAITS             string_CPP11_110

// Usage of C++ language features:

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

#if string_HAVE_NULLPTR
# define string_nullptr nullptr
#else
# define string_nullptr NULL
#endif

#if string_HAVE_EXPLICIT_CONVERSION
# define string_explicit_cv explicit
#else
# define string_explicit_cv /*explicit*/
#endif

#define string_HAS_ENABLE_IF_  (string_HAVE_TYPE_TRAITS && string_HAVE_DEFAULT_FN_TPL_ARGS)

#if string_HAS_ENABLE_IF_
#  define string_ENABLE_IF_HAS_MEMBER_(member) , class = decltype( std::declval<StringT>().member )
#else
# define  string_ENABLE_IF_HAS_MEMBER_(member)
#endif

// Additional includes:

#include <algorithm>
#include <cassert>
#include <locale>
#include <string>
#include <cstring>

#if string_HAVE_TYPE_TRAITS
# include <type_traits>
#elif string_HAVE_TR1_TYPE_TRAITS
# include <tr1/type_traits>
#endif

namespace nonstd {
namespace string {
namespace detail {

template< typename CharT >
string_nodiscard inline CharT * to_begin( CharT * text )
{
    return text;
}

template< typename CharT >
string_nodiscard inline CharT * to_end( CharT * text )
{
    return std::strchr( text, '\0' );
}

template< typename StringT >
string_nodiscard inline typename StringT::iterator to_begin( StringT & text )
{
    return text.begin();
}

template< typename StringT >
string_nodiscard inline typename StringT::iterator to_end( StringT & text )
{
    return text.end();
}

template< typename CharT >
string_nodiscard inline CharT as_lowercase( CharT chr )
{
    return std::tolower( chr, std::locale() );
}

template< typename CharT >
string_nodiscard inline CharT as_uppercase( CharT chr )
{
    return std::toupper( chr, std::locale() );
}

// Note: serve both CharT* and StringT&:

template< typename StringT, typename Fn >
void to_case( StringT & text, Fn fn ) string_noexcept
{
    std::transform(
        detail::to_begin( text ), detail::to_end( text )
        , detail::to_begin( text )
        , fn
    );
}

} // namespace detail

template< typename CharT >
string_nodiscard CharT nullchr() string_noexcept
{
    return 0;
}

// Observers:

template< typename CharT >
string_nodiscard bool is_empty( CharT const * cp ) string_noexcept
{
    assert( cp != string_nullptr );
    return *cp == nullchr<CharT>();
}

template< typename StringT  string_ENABLE_IF_HAS_MEMBER_(empty()) >
string_nodiscard bool is_empty( StringT const & text ) string_noexcept
{
    return text.empty();
}

// Modifiers:

template< typename CharT >
void clear( CharT * cp ) string_noexcept
{
    *cp = nullchr<CharT>();
}

template< typename StringT  string_ENABLE_IF_HAS_MEMBER_(clear()) >
void clear( StringT & text ) string_noexcept
{
    text.clear();
}

template< typename CharT >
void to_lowercase( CharT * cp ) string_noexcept
{
    detail::to_case( cp, detail::as_lowercase<CharT> );
}

template< typename CharT >
void to_uppercase( CharT * cp ) string_noexcept
{
    detail::to_case( cp, detail::as_uppercase<CharT> );
}

template< typename StringT  string_ENABLE_IF_HAS_MEMBER_(begin()) >
void to_lowercase( StringT & text ) string_noexcept
{
    detail::to_case( text, detail::as_lowercase<typename StringT::value_type> );
}

template< typename StringT  string_ENABLE_IF_HAS_MEMBER_(begin()) >
void to_uppercase( StringT & text ) string_noexcept
{
    detail::to_case( text, detail::as_uppercase<typename StringT::value_type> );
}

template< typename StringT  string_ENABLE_IF_HAS_MEMBER_(begin()) >
string_nodiscard StringT as_lowercase( StringT const & text ) string_noexcept
{
    StringT result( text );
    to_lowercase( result );
    return result;
}

template< typename StringT  string_ENABLE_IF_HAS_MEMBER_(begin()) >
string_nodiscard StringT as_uppercase( StringT const & text ) string_noexcept
{
    StringT result( text );
    to_uppercase( result );
    return result;
}

#if string_HAS_ENABLE_IF_
// template< typename StringT  string_ENABLE_IF_HAS_MEMBER_(toUpper()) >
// void to_upper( StringT & text ) string_noexcept
// {
//     text = text.toUpper();
// }
#endif

} // namespace string
} // namespace nonstd

namespace nonstd {

// using string::clear;

} // namespace nonstd

#endif // NONSTD_STRING_LITE_HPP
