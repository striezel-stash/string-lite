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
#define string_CPP23_OR_GREATER  ( string_CPLUSPLUS >= 202300L )

// MSVC version:

#if defined(_MSC_VER ) && !defined(__clang__)
# define string_COMPILER_MSVC_VER           (_MSC_VER )
# define string_COMPILER_MSVC_VERSION       (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900 ) ) )
# define string_COMPILER_MSVC_VERSION_FULL  (_MSC_VER - 100 * ( 5 + (_MSC_VER < 1900 ) ) )
#else
# define string_COMPILER_MSVC_VER           0
# define string_COMPILER_MSVC_VERSION       0
# define string_COMPILER_MSVC_VERSION_FULL  0
#endif

// clang version:

#define string_COMPILER_VERSION( major, minor, patch ) ( 10 * ( 10 * (major) + (minor) ) + (patch) )

#if defined( __apple_build_version__ )
# define string_COMPILER_APPLECLANG_VERSION string_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
# define string_COMPILER_CLANG_VERSION 0
#elif defined( __clang__ )
# define string_COMPILER_APPLECLANG_VERSION 0
# define string_COMPILER_CLANG_VERSION string_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
#else
# define string_COMPILER_APPLECLANG_VERSION 0
# define string_COMPILER_CLANG_VERSION 0
#endif

// GNUC version:

#if defined(__GNUC__) && !defined(__clang__)
# define string_COMPILER_GNUC_VERSION string_COMPILER_VERSION( __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ )
#else
# define string_COMPILER_GNUC_VERSION 0
#endif

// half-open range [lo..hi):
#define string_BETWEEN( v, lo, hi ) ( (lo) <= (v) && (v) < (hi) )

// Presence of language and library features:

#define string_CPP11_100  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1600)
#define string_CPP11_110  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1700)
#define string_CPP11_120  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1800)
#define string_CPP11_140  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1900)
#define string_CPP11_141  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1910)

#define string_CPP11_000  (string_CPP11_OR_GREATER)

#define string_CPP14_000  (string_CPP14_OR_GREATER)
#define string_CPP14_120  (string_CPP14_OR_GREATER || string_COMPILER_MSVC_VER >= 1800)

#define string_CPP17_000  (string_CPP17_OR_GREATER)
#define string_CPP17_120  (string_CPP17_OR_GREATER || string_COMPILER_MSVC_VER >= 1800)
#define string_CPP17_140  (string_CPP17_OR_GREATER || string_COMPILER_MSVC_VER >= 1900)

// Presence of C++11 language features:

#define string_HAVE_FREE_BEGIN              string_CPP14_120
#define string_HAVE_CONSTEXPR_11            string_CPP11_140
#define string_HAVE_NOEXCEPT                string_CPP11_140
#define string_HAVE_NULLPTR                 string_CPP11_100
#define string_HAVE_DEFAULT_FN_TPL_ARGS     string_CPP11_120
#define string_HAVE_EXPLICIT_CONVERSION     string_CPP11_120

// Presence of C++14 language features:

#define string_HAVE_FREE_BEGIN              string_CPP14_120

// Presence of C++17 language features:

#define string_HAVE_FREE_SIZE               string_CPP17_140
#define string_HAVE_NODISCARD               string_CPP17_000

// Presence of C++ library features:

#define string_HAVE_REGEX                  (string_CPP11_100 && !string_BETWEEN(string_COMPILER_GNUC_VERSION, 1, 490))
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

#define string_HAS_ENABLE_IF_          (string_HAVE_TYPE_TRAITS && string_HAVE_DEFAULT_FN_TPL_ARGS)
#define string_TEST_STRING_CONTAINS    (string_HAS_ENABLE_IF_ && !string_BETWEEN(string_COMPILER_MSVC_VER, 1, 1910))
#define string_TEST_STRING_STARTS_WITH  string_TEST_STRING_CONTAINS
#define string_TEST_STRING_ENDS_WITH    string_TEST_STRING_CONTAINS

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
#include <cstring>
#include <iterator>
#include <locale>
#include <string>

#if string_HAVE_REGEX
# include <regex>
#endif

#if string_HAVE_TYPE_TRAITS
# include <type_traits>
#elif string_HAVE_TR1_TYPE_TRAITS
# include <tr1/type_traits>
#endif

// Method detection:

#define string_HAS_METHOD_( T, M )  \
    nonstd::string::has_##M<T>::value

#if string_CPP11_OR_GREATER && !string_BETWEEN(string_COMPILER_GNUC_VERSION, 1, 500)

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

// for string_HAS_METHOD_:

string_MAKE_HAS_METHOD_( begin )
string_MAKE_HAS_METHOD_( clear )
string_MAKE_HAS_METHOD_( contains )
string_MAKE_HAS_METHOD_( empty )
string_MAKE_HAS_METHOD_( starts_with )
string_MAKE_HAS_METHOD_( ends_with )
string_MAKE_HAS_METHOD_( replace )

// string-lite API functions:

namespace detail {

// for string_ENABLE_IF_():

/*enum*/ class enabler{};

#if string_HAVE_FREE_BEGIN

using std::begin;
using std::cbegin;
using std::crbegin;
using std::end;
using std::cend;
using std::crend;

#else // string_HAVE_FREE_BEGIN

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

template< typename StringT >
string_nodiscard inline typename StringT::reverse_iterator rbegin( StringT const & text )
{
    return text.rbegin();
}

template< typename StringT >
string_nodiscard inline typename StringT::reverse_iterator rend( StringT const & text )
{
    return text.rend();
}

template< typename StringT >
string_nodiscard inline typename StringT::const_reverse_iterator crbegin( StringT const & text )
{
    return text.crbegin();
}

template< typename StringT >
string_nodiscard inline typename StringT::const_reverse_iterator crend( StringT const & text )
{
    return text.crend();
}

#else // string_CPP11_000

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

template< typename StringT >
string_nodiscard inline typename StringT::const_reverse_iterator crbegin( StringT const & text )
{
    typedef typename StringT::const_reverse_iterator const_reverse_iterator;
    return const_reverse_iterator( text.rbegin() );
}

template< typename StringT >
string_nodiscard inline typename StringT::const_reverse_iterator crend( StringT const & text )
{
    typedef typename StringT::const_reverse_iterator const_reverse_iterator;
    return const_reverse_iterator( text.rend() );
}

#endif // string_CPP11_000
#endif // string_HAVE_FREE_BEGIN

// non-standard begin(), end() for char*:

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

#if string_HAVE_FREE_SIZE

using std::size;

#else // string_HAVE_FREE_SIZE

template< typename Cont >
string_nodiscard inline size_t size( Cont const & c )
{
    return c.size();
}

#endif // string_HAVE_FREE_SIZE

// nonstd size(C-string)

string_nodiscard inline size_t size( char const * s )
{
    return std::strlen( s );
}

// case conversion:

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

// find_first():

template< typename StringT, typename SubT >
typename StringT::iterator find_first( StringT & text, SubT const & seek )
{
    return std::search(
        detail::begin(text), detail::end(text)
        , detail::cbegin(seek), detail::cend(seek)
    );
}

template< typename StringT, typename SubT >
typename StringT::const_iterator find_first( StringT const & text, SubT const & seek )
{
    return std::search(
        detail::cbegin(text), detail::cend(text)
        , detail::cbegin(seek), detail::cend(seek)
    );
}

// find_last():

template< typename StringIt, typename SubIt, typename PredicateT >
StringIt find_last( StringIt text_pos, StringIt text_end, SubIt seek_pos, SubIt seek_end, PredicateT compare )
{
    if ( seek_pos == seek_end )
        return text_end;

    StringIt result = text_end;

    while ( true )
    {
        StringIt new_result = std::search( text_pos, text_end, seek_pos, seek_end, compare );

        if ( new_result == text_end )
        {
            break;
        }
        else
        {
            result = new_result;
            text_pos = result;
            ++text_pos;
        }
    }
    return result;
}

template< typename StringT, typename SubT, typename PredicateT >
typename StringT::iterator find_last( StringT & text, SubT const & seek, PredicateT compare )
{
    return detail::find_last(
        detail::begin(text), detail::end(text)
        , detail::cbegin(seek), detail::cend(seek)
        , compare
    );
}

template< typename StringT, typename SubT, typename PredicateT >
typename StringT::const_iterator find_last( StringT const & text, SubT const & seek, PredicateT compare )
{
    return detail::find_last(
        detail::cbegin(text), detail::cend(text)
        , detail::cbegin(seek), detail::cend(seek)
        , compare
    );
}

// starts_with():

template< typename StringIt, typename SubIt, typename PredicateT >
bool starts_with( StringIt text_pos, StringIt text_end, SubIt seek_pos, SubIt seek_end, PredicateT compare )
{
    for( ; text_pos != text_end && seek_pos != seek_end; ++text_pos, ++seek_pos )
    {
        if( !compare( *text_pos, *seek_pos ) )
            return false;
    }

    return seek_pos == seek_end;
}

template< typename StringT, typename SubT, typename PredicateT >
bool starts_with( StringT const & text, SubT const & seek, PredicateT compare )
{
    return detail::starts_with(
        detail::cbegin(text), detail::cend(text)
        , detail::cbegin(seek), detail::cend(seek)
        , compare
    );
}

// ends_with():

template< typename StringT, typename SubT, typename PredicateT >
bool ends_with( StringT const & text, SubT const & seek, PredicateT compare )
{
    return detail::starts_with(
        detail::crbegin(text), detail::crend(text)
        , detail::crbegin(seek), detail::crend(seek)
        , compare
    );
}

// TODO replace_all() - alg:

template< typename StringIt, typename FromIt, typename ToIt, typename PredicateT >
bool replace_all
(
    StringIt text_pos, StringIt text_end
    , FromIt from_pos, FromIt from_end
    , ToIt to_pos, ToIt to_end
    , PredicateT compare
)
{
    return true; // error
}

template< typename CharT, typename FromT, typename ToT >
std::basic_string<CharT> & replace_all( std::basic_string<CharT> & text, FromT const & from, ToT const & to ) string_noexcept
{
    for ( ;; )
    {
        const size_t pos = text.find( from );

        if ( pos == std::string::npos )
            return text;

        text.replace( pos, size(from), to );
    }
}

template< typename StringT, typename FromT, typename ToT >
StringT & replace_all( StringT & text, FromT const & from, ToT const & to ) string_noexcept
{
    typedef typename StringT::value_type A;

    (void) detail::replace_all(
        detail::begin(text), detail::end(text)
        , detail::cbegin(from), detail::cend(from)
        , detail::cbegin(to), detail::cend(to)
        , std::equal_to<A>()
    );

    return text;
}

// replace_first() - alg:

template< typename CharT, typename FromT, typename ToT >
std::basic_string<CharT> & replace_first( std::basic_string<CharT> & text, FromT const & from, ToT const & to ) string_noexcept
{
    const size_t pos = text.find( from );

    if ( pos == std::string::npos )
        return text;

    return text.replace( pos, size(from), to );
}

// replace_last() - alg:

template< typename CharT, typename FromT, typename ToT >
std::basic_string<CharT> & replace_last( std::basic_string<CharT> & text, FromT const & from, ToT const & to ) string_noexcept
{
    const size_t pos = text.rfind( from );

    if ( pos == std::string::npos )
        return text;

    return text.replace( pos, size(from), to );
}

} // namespace detail

// Utilities:

template< typename CharT >
string_nodiscard CharT nullchr() string_noexcept
{
    return 0;
}

// Observers:

// is_empty():

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

// find_first():

template< typename StringT, typename SubT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
string_constexpr typename StringT::iterator find_first( StringT & text, SubT const & seek )
{
    return detail::find_first( text, seek );
}

template< typename StringT, typename SubT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
string_constexpr typename StringT::const_iterator find_first( StringT const & text, SubT const & seek )
{
    return detail::find_first( text, seek );
}

template< typename CharT, typename SubT >
string_constexpr CharT * find_first( CharT * text, SubT const & seek )
{
    return detail::find_first( text, seek );
}

// find_last():

template< typename StringT, typename SubT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
string_constexpr typename StringT::iterator find_last( StringT & text, SubT const & seek )
{
    typedef typename StringT::value_type A;

    return detail::find_last( text, seek, std::equal_to<A>() );
}

template< typename StringT, typename SubT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
string_constexpr typename StringT::const_iterator find_last( StringT const & text, SubT const & seek )
{
    typedef typename StringT::value_type A;

    return detail::find_last( text, seek, std::equal_to<A>() );
}

template< typename CharT, typename SubT >
string_constexpr CharT * find_last( CharT * text, SubT const & seek )
{
    return detail::find_last( text, seek, std::equal_to<CharT>() );
}

// contains(); C++23-like string::contains():

#if string_TEST_STRING_CONTAINS

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
    return detail::end( text ) != find_first( text, seek );
}

template< typename StringT, typename CharT
    string_DISABLE_IF_HAS_METHOD_(StringT, contains)
    string_ENABLE_IF_( std::is_arithmetic<CharT>::value )
>
string_nodiscard /*string_constexpr*/ bool contains( StringT const & text, CharT seek ) string_noexcept
{
    CharT look[] = { seek, nullchr<CharT>() };
    return detail::end( text ) != find_first( text, look );
}

#else // string_TEST_STRING_CONTAINS

template< typename StringT, typename SubT >
string_nodiscard string_constexpr bool contains( StringT const & text, SubT const & seek ) string_noexcept
{
    return detail::cend( text ) != find_first( text, seek );
}

template< typename StringT >
string_nodiscard string_constexpr bool contains( StringT const & text, char const * seek ) string_noexcept
{
    return detail::cend( text ) != find_first( text, seek );
}

template< typename StringT >
string_nodiscard /*string_constexpr*/ bool contains( StringT const & text, char seek ) string_noexcept
{
    char look[] = { seek, nullchr<char>() };
    return detail::cend( text ) != find_first( text, look );
}

#endif // string_TEST_STRING_CONTAINS

#if string_HAVE_REGEX

template< typename StringT >
string_nodiscard string_constexpr bool contains( StringT const & text, std::regex const & re ) string_noexcept
{
    return std::regex_search( text, re );
}

template< typename StringT, typename ReT >
string_nodiscard string_constexpr bool contains_re( StringT const & text, ReT const & re ) string_noexcept
{
    return contains( text, std::regex(re) );
}

#endif // string_HAVE_REGEX

// starts_with():

#if string_TEST_STRING_STARTS_WITH

template< typename StringT, typename SubT
    string_ENABLE_IF_HAS_METHOD_(StringT, starts_with)
>
string_nodiscard string_constexpr bool starts_with( StringT const & text, SubT const & seek ) string_noexcept
{
    return text.starts_with( seek );
}

template< typename StringT, typename SubT
    string_DISABLE_IF_HAS_METHOD_(StringT, starts_with)
    string_ENABLE_IF_( !std::is_arithmetic<SubT>::value )
>
string_nodiscard string_constexpr bool starts_with( StringT const & text, SubT const & seek ) string_noexcept
{
    typedef typename StringT::value_type A;

    return detail::starts_with( text, seek, std::equal_to<A>() );
}

template< typename StringT, typename CharT
    string_DISABLE_IF_HAS_METHOD_(StringT, starts_with)
    string_ENABLE_IF_( std::is_arithmetic<CharT>::value )
>
string_nodiscard /*string_constexpr*/ bool starts_with( StringT const & text, CharT seek ) string_noexcept
{
    CharT look[] = { seek, nullchr<CharT>() };

    // return detail::starts_with( text, look, std::equal_to<CharT>() );
    return detail::starts_with( text, StringT(look), std::equal_to<CharT>() );
}

#else // string_TEST_STRING_STARTS_WITH

template< typename StringT, typename SubT >
string_nodiscard string_constexpr bool starts_with( StringT const & text, SubT const & seek ) string_noexcept
{
    typedef typename StringT::value_type A;

    return detail::starts_with( text, seek, std::equal_to<A>() );
}

template< typename StringT >
string_nodiscard string_constexpr bool starts_with( StringT const & text, char const * seek ) string_noexcept
{
    typedef typename StringT::value_type A;

    return detail::starts_with( text, seek, std::equal_to<A>() );
}

template< typename StringT >
string_nodiscard /*string_constexpr*/ bool starts_with( StringT const & text, char seek ) string_noexcept
{
    char look[] = { seek, nullchr<char>() };

    return detail::starts_with( text, StringT(look), std::equal_to<char>() );
}

#endif // string_TEST_STRING_STARTS_WITH

// ends_with():

#if string_TEST_STRING_ENDS_WITH

template< typename StringT, typename SubT
    string_ENABLE_IF_HAS_METHOD_(StringT, ends_with)
>
string_nodiscard string_constexpr bool ends_with( StringT const & text, SubT const & seek ) string_noexcept
{
    return text.ends_with( seek );
}

template< typename StringT, typename SubT
    string_DISABLE_IF_HAS_METHOD_(StringT, ends_with)
    string_ENABLE_IF_( !std::is_arithmetic<SubT>::value )
>
string_nodiscard string_constexpr bool ends_with( StringT const & text, SubT const & seek ) string_noexcept
{
    typedef typename StringT::value_type A;

    return detail::ends_with( text, StringT(seek), std::equal_to<A>() );
}

template< typename StringT, typename CharT
    string_DISABLE_IF_HAS_METHOD_(StringT, ends_with)
    string_ENABLE_IF_( std::is_arithmetic<CharT>::value )
>
string_nodiscard /*string_constexpr*/ bool ends_with( StringT const & text, CharT seek ) string_noexcept
{
    CharT look[] = { seek, nullchr<CharT>() };

    return detail::ends_with( text, StringT(look), std::equal_to<CharT>() );
}

#else // string_TEST_STRING_ENDS_WITH

template< typename StringT, typename SubT >
string_nodiscard string_constexpr bool ends_with( StringT const & text, SubT const & seek ) string_noexcept
{
    typedef typename StringT::value_type A;

    return detail::ends_with( text, seek, std::equal_to<A>() );
}

template< typename StringT >
string_nodiscard string_constexpr bool ends_with( StringT const & text, char const * seek ) string_noexcept
{
    typedef typename StringT::value_type A;

    return detail::ends_with( text, StringT(seek), std::equal_to<A>() );
}

template< typename StringT >
string_nodiscard /*string_constexpr*/ bool ends_with( StringT const & text, char seek ) string_noexcept
{
    char look[] = { seek, nullchr<char>() };

    return detail::ends_with( text, StringT(look), std::equal_to<char>() );
}

#endif // string_TEST_STRING_ENDS_WITH

// Modifiers:

// replace_all():

template< typename CharT, typename FromT, typename ToT
    // string_ENABLE_IF_HAS_METHOD_(StringT, replace)
>
string_nodiscard string_constexpr std::basic_string<CharT> &
replace_all( std::basic_string<CharT> & text, FromT const & from, ToT const & to ) string_noexcept
{
    return detail::replace_all( text, from, to );
}

template< typename StringT, typename FromT, typename ToT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
string_nodiscard string_constexpr StringT &
replace_all( StringT & text, FromT const & from, ToT const & to ) string_noexcept
{
    return detail::replace_all( text, from, to );
}

// replaced_all():

template< typename CharT, typename FromT, typename ToT >
string_nodiscard /*string_constexpr*/ std::basic_string<CharT>
replaced_all( CharT const * text, FromT const & from, ToT const & to ) string_noexcept
{
    std::basic_string<CharT> result( text );

    return replace_all( result, from, to );
}

template< typename StringT, typename FromT, typename ToT >
string_nodiscard /*string_constexpr*/ StringT
replaced_all( StringT const & text, FromT const & from, ToT const & to ) string_noexcept
{
    StringT result( text );

    return replace_all( result, from, to );
}

// replace_first():

template< typename CharT, typename FromT, typename ToT
    // string_ENABLE_IF_HAS_METHOD_(StringT, replace)
>
string_nodiscard string_constexpr std::basic_string<CharT> &
replace_first( std::basic_string<CharT> & text, FromT const & from, ToT const & to ) string_noexcept
{
    return detail::replace_first( text, from, to );
}

template< typename StringT, typename FromT, typename ToT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
string_nodiscard string_constexpr StringT &
replace_first( StringT & text, FromT const & from, ToT const & to ) string_noexcept
{
    return detail::replace_first( text, from, to );
}

// replaced_first():

template< typename CharT, typename FromT, typename ToT >
string_nodiscard /*string_constexpr*/ std::basic_string<CharT>
replaced_first( CharT const * text, FromT const & from, ToT const & to ) string_noexcept
{
    std::basic_string<CharT> result( text );

    return replace_first( result, from, to );
}

template< typename StringT, typename FromT, typename ToT >
string_nodiscard /*string_constexpr*/ StringT
replaced_first( StringT const & text, FromT const & from, ToT const & to ) string_noexcept
{
    StringT result( text );

    return replace_first( result, from, to );
}

// replace_last():

template< typename CharT, typename FromT, typename ToT
    // string_ENABLE_IF_HAS_METHOD_(StringT, replace)
>
string_nodiscard string_constexpr std::basic_string<CharT> &
replace_last( std::basic_string<CharT> & text, FromT const & from, ToT const & to ) string_noexcept
{
    return detail::replace_last( text, from, to );
}

template< typename StringT, typename FromT, typename ToT
    string_ENABLE_IF_HAS_METHOD_(StringT, begin)
>
string_nodiscard string_constexpr StringT &
replaced_last( StringT & text, FromT const & from, ToT const & to ) string_noexcept
{
    return detail::replace_last( text, from, to );
}

// replaced_last():

template< typename CharT, typename FromT, typename ToT >
string_nodiscard /*string_constexpr*/ std::basic_string<CharT>
replaced_last( CharT const * text, FromT const & from, ToT const & to ) string_noexcept
{
    std::basic_string<CharT> result( text );

    return replaced_last( result, from, to );
}

template< typename StringT, typename FromT, typename ToT >
string_nodiscard /*string_constexpr*/ StringT
replaced_last( StringT const & text, FromT const & from, ToT const & to ) string_noexcept
{
    StringT result( text );

    return replaced_last( result, from, to );
}

// clear():

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

// to_lowercase(), to_uppercase():

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

} // namespace string
} // namespace nonstd

namespace nonstd {

// using string::clear;

} // namespace nonstd

#endif // NONSTD_STRING_LITE_HPP
