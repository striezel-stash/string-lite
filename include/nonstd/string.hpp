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

// half-open range [lo..hi):
#define string_BETWEEN( v, lo, hi ) ( (lo) <= (v) && (v) < (hi) )

// Presence of language and library features:

#define string_CPP11_100  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1600)
#define string_CPP11_110  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1700)
#define string_CPP11_120  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1800)
#define string_CPP11_140  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1900)

#define string_CPP11_000  (string_CPP11_OR_GREATER)

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

// Method enabling (return type):

#if string_HAVE_TYPE_TRAITS
# define string_ENABLE_IF_R_(VA, R)  typename std::enable_if< (VA), R >::type
#else
# define string_ENABLE_IF_R_(VA, R)  R
#endif

// Method enabling (function template argument):

#if string_HAS_ENABLE_IF_

// VS 2013 seems to have trouble with SFINAE for default non-type arguments:
# if !string_BETWEEN( string_COMPILER_MSVC_VER, 1, 1900 )
#  define string_ENABLE_IF_(VA) , typename std::enable_if< (VA), int >::type = 0
# else
#  define string_ENABLE_IF_(VA) , typename = typename std::enable_if< (VA), ::nonstd::string::detail::enabler >::type
# endif

# define string_ENABLE_IF_HAS_METHOD_(  type, method)  string_ENABLE_IF_(  string_HAS_METHOD_( type, method) )
# define string_DISABLE_IF_HAS_METHOD_( type, method)  string_ENABLE_IF_( !string_HAS_METHOD_( type, method) )

#else
# define  string_ENABLE_IF_(VA)
# define  string_ENABLE_IF_HAS_METHOD_( type, member)
# define  string_DISABLE_IF_HAS_METHOD_(type, member)
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

// Method detection:

#if string_CPP11_OR_GREATER

# define string_HAS_METHOD_( T, M )  \
    has_##M<T>::value

# define string_MAKE_HAS_METHOD_( M )                   \
    template< typename T >                              \
    using M##_t = decltype(std::declval<T>().M());      \
                                                        \
    template<typename T >                               \
    using has_##M = std23::is_detected<M##_t, T>;

#else // string_CPP11_OR_GREATER

# define string_MAKE_HAS_METHOD_( M )                   \
    template< typename T >                              \
    struct has_##M                                      \
    {                                                   \
        typedef char yes[1];                            \
        typedef char no[2];                             \
                                                        \
        template< typename U >                          \
        static yes & test( int (*)[sizeof(std98::declval<U>().M(), 1)] );    \
                                                        \
        template< typename U >                          \
        static no & test(...);                          \
                                                        \
        static const bool value = sizeof( test<T>(NULL) ) == sizeof(yes); \
    };

#endif

// Type traits:
namespace nonstd {
namespace string {

namespace std98 {

template< typename T, T v > struct integral_constant { enum { value = v }; };
typedef integral_constant< bool, true  > true_type;
typedef integral_constant< bool, false > false_type;

template< typename T, typename U >
struct is_same { enum dummy { value = false }; };

template< typename T >
struct is_same<T, T> { enum dummy { value = true }; };

template< typename T >
T declval();

} // namespace std98

#if string_CPP11_OR_GREATER

namespace std11 {

template< bool B, typename T, typename F >
struct conditional { typedef T type; };

template< typename T, typename F >
struct conditional<false, T, F> { typedef F type; };

} // C++11

namespace std14 {

template< bool B, typename T, typename F >
using conditional_t = typename std11::conditional<B,T,F>::type;

} // namespace c++14

namespace std17 {

template< typename... >
using void_t = void;

} // namespace c++17

namespace std23 {
namespace detail {

template< typename Default, typename AlwaysVoid, template<class...> class Op, typename... Args >
struct detector
{
    using value_t = std::false_type;
    using type = Default;
};

template< typename Default, template<class...> class Op, typename... Args >
struct detector<Default, std17::void_t<Op<Args...>>, Op, Args...>
{
    using value_t = std::true_type;
    using type = Op<Args...>;
};

} // namespace detail

struct nonesuch
{
    ~nonesuch() = delete;
    nonesuch( nonesuch const & ) = delete;
    void operator=( nonesuch const & ) = delete;
};

// pre-C+17 requires `class Op`:
template< template<typename...> class Op, typename... Args >
using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

} // std23

#endif // string_CPP11_OR_GREATER

// string-lite API functions:
namespace detail {

// for string_ENABLE_IF_():

/*enum*/ class enabler{};

template< typename CharT >
string_nodiscard inline CharT * begin( CharT * text )
{
    return text;
}

template< typename CharT >
string_nodiscard inline CharT * end( CharT * text )
{
    return std::strchr( text, '\0' );
}

template< typename CharT >
string_nodiscard inline CharT const * begin( CharT const * text )
{
    return text;
}

template< typename CharT >
string_nodiscard inline CharT const * end( CharT const * text )
{
    return std::strchr( text, '\0' );
}

template< typename CharT >
string_nodiscard inline CharT const * cbegin( CharT const * text )
{
    return text;
}

template< typename CharT >
string_nodiscard inline CharT const * cend( CharT const * text )
{
    return std::strchr( text, '\0' );
}

template< typename StringT >
string_nodiscard inline typename StringT::iterator begin( StringT & text )
{
    return text.begin();
}

template< typename StringT >
string_nodiscard inline typename StringT::iterator end( StringT & text )
{
    return text.end();
}

#if string_CPP11_000

template< typename StringT >
string_nodiscard inline typename StringT::const_iterator begin( StringT const & text )
{
    return text.cbegin();
}

template< typename StringT >
string_nodiscard inline typename StringT::const_iterator end( StringT const & text )
{
    return text.cend();
}

template< typename StringT >
string_nodiscard inline typename StringT::const_iterator cbegin( StringT const & text )
{
    return text.cbegin();
}

template< typename StringT >
string_nodiscard inline typename StringT::const_iterator cend( StringT const & text )
{
    return text.cend();
}

#else

template< typename StringT >
string_nodiscard inline typename StringT::const_iterator cbegin( StringT const & text )
{
    typedef typename StringT::const_iterator const_iterator;
    return const_iterator( text.begin() );
}

template< typename StringT >
string_nodiscard inline typename StringT::const_iterator cend( StringT const & text )
{
    typedef typename StringT::const_iterator const_iterator;
    return const_iterator( text.end() );
}

#endif // string_CPP11_000

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
        detail::begin( text ), detail::end( text )
        , detail::begin( text )
        , fn
    );
}

template< typename StringT, typename SubT >
typename StringT::iterator find( StringT & text, SubT const & seek )
{
    return std::search(
        detail::begin(text), detail::end(text)
        , detail::cbegin(seek), detail::cend(seek)
    );
}

template< typename StringT, typename SubT >
typename StringT::const_iterator find( StringT const & text, SubT const & seek )
{
    return std::search(
        detail::cbegin(text), detail::cend(text)
        , detail::cbegin(seek), detail::cend(seek)
    );
}

} // namespace detail

string_MAKE_HAS_METHOD_( begin )
string_MAKE_HAS_METHOD_( clear )
string_MAKE_HAS_METHOD_( contains )
string_MAKE_HAS_METHOD_( empty )

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

template< typename StringT
    string_ENABLE_IF_HAS_METHOD_(StringT, empty)
>
string_nodiscard bool is_empty( StringT const & text ) string_noexcept
{
    return text.empty();
}

template< typename StringT, typename SubT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
string_constexpr typename StringT::iterator find( StringT & text, SubT const & seek )
{
    return detail::find( text, seek );
}

template< typename StringT, typename SubT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
string_constexpr typename StringT::const_iterator find( StringT const & text, SubT const & seek )
{
    return detail::find( text, seek );
}

template< typename CharT, typename SubT >
string_constexpr CharT * find( CharT * text, SubT const & seek )
{
    return detail::find( text, seek );
}

// C++20-like string::contains():

#if string_HAS_ENABLE_IF_

template< typename StringT, typename SubT
    string_ENABLE_IF_HAS_METHOD_(StringT, contains)
>
string_nodiscard string_constexpr bool contains( StringT const & text, SubT const & seek ) string_noexcept
{
    return text.contains( seek );
}

template< typename StringT, typename SubT
    string_DISABLE_IF_HAS_METHOD_(StringT, contains)
    string_ENABLE_IF_( !std::is_arithmetic<SubT>::value )
>
string_nodiscard string_constexpr bool contains( StringT const & text, SubT const & seek ) string_noexcept
{
    return detail::end( text ) != find( text, seek );
}

template< typename StringT, typename CharT
    string_DISABLE_IF_HAS_METHOD_(StringT, contains)
    string_ENABLE_IF_( std::is_arithmetic<CharT>::value )
>
string_nodiscard /*string_constexpr*/ bool contains( StringT const & text, CharT seek ) string_noexcept
{
    CharT look[] = { seek, nullchr<CharT>() };
    return detail::end( text ) != find( text, look );
}

#else // string_HAS_ENABLE_IF_

template< typename StringT, typename SubT >
string_nodiscard string_constexpr bool contains( StringT const & text, SubT const & seek ) string_noexcept
{
    return detail::cend( text ) != find( text, seek );
}

template< typename StringT >
string_nodiscard string_constexpr bool contains( StringT const & text, char const * seek ) string_noexcept
{
    return detail::cend( text ) != find( text, seek );
}

template< typename StringT >
string_nodiscard string_constexpr bool contains( StringT const & text, char seek ) string_noexcept
{
    char look[] = { seek, nullchr<char>() };
    return detail::cend( text ) != find( text, look );
}

#endif // string_HAS_ENABLE_IF_

// Modifiers:

template< typename CharT >
void clear( CharT * cp ) string_noexcept
{
    *cp = nullchr<CharT>();
}

template< typename StringT
    string_ENABLE_IF_HAS_METHOD_(StringT, clear)
>
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

template< typename StringT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
void to_lowercase( StringT & text ) string_noexcept
{
    detail::to_case( text, detail::as_lowercase<typename StringT::value_type> );
}

template< typename StringT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
void to_uppercase( StringT & text ) string_noexcept
{
    detail::to_case( text, detail::as_uppercase<typename StringT::value_type> );
}

template< typename StringT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
string_nodiscard StringT as_lowercase( StringT const & text ) string_noexcept
{
    StringT result( text );
    to_lowercase( result );
    return result;
}

template< typename StringT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
string_nodiscard StringT as_uppercase( StringT const & text ) string_noexcept
{
    StringT result( text );
    to_uppercase( result );
    return result;
}

#if string_HAS_ENABLE_IF_
// template< typename StringT
//     string_ENABLE_IF_HAS_METHOD_(toUpper())
// >
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
