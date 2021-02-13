// Copyright 2021-2021 Martin Moene
//
// https://github.com/martinmoene/string-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "string-main.t.hpp"

#ifdef _WIN32
# define string_strdup  _strdup
#else
# define string_strdup   strdup
#endif

namespace {

using namespace nonstd::string;

struct scoped_str
{
    char * p;

    scoped_str( char const * s ) : p ( string_strdup(s) ) {}

    ~scoped_str() { delete p; }

    operator char const *() { return p; }

    char * get() { return p; }
};

inline char const * lstr() { return "a b c d e f g h i j k l m n o p q r s t u v w x y z"; }
inline char const * ustr() { return "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"; }

// Tests:

CASE( "string: Setting Windows console to print utf8 characters" "[unicode][windows]" )
{
#if defined(_WIN32) && _WIN32
    // enable display of utf8, https://stackoverflow.com/a/19071749/437272
    EXPECT( SetConsoleOutputCP(65001) != 0 );
#else
    EXPECT( !!"string: skipping (non-Windows)" );
#endif
}

// Observers:

CASE( "is_empty: true if string is empty - char *" )
{
    EXPECT(     is_empty("") );
    EXPECT_NOT( is_empty("a") );
}

CASE( "is_empty: true if string is empty - string" )
{
    EXPECT(     is_empty(std::string()) );
    EXPECT_NOT( is_empty(std::string("x")) );
}

CASE( "contains: true if string contains sub string - string-char" )
{
    EXPECT(     contains(std::string("abc123xyz"), '1') );
    EXPECT_NOT( contains(std::string("abc123xyz"), '7') );
}

CASE( "contains: true if string contains sub string - string-char*" )
{
    EXPECT(     contains(std::string("abc123xyz"), "123") );
    EXPECT_NOT( contains(std::string("abc123xyz"), "789") );
}

CASE( "contains: true if string contains sub string - string-string" )
{
    EXPECT(     contains(std::string("abc123xyz"), std::string("123")) );
    EXPECT_NOT( contains(std::string("abc123xyz"), std::string("789")) );
}

CASE( "contains: true if string contains sub string - string-string_view" )
{
#if string_HAVE_STD_STRING_VIEW
    EXPECT(     contains(std::string("abc123xyz"), std::string_view("123")) );
    EXPECT_NOT( contains(std::string("abc123xyz"), std::string_view("789")) );
#else
    EXPECT( !!"std::string_view is not available (pre C++17)." );
#endif
}

CASE( "contains: true if string contains sub string - string_view-string_view" )
{
#if string_HAVE_STD_STRING_VIEW
    EXPECT(     contains(std::string_view("abc123xyz"), std::string_view("123")) );
    EXPECT_NOT( contains(std::string_view("abc123xyz"), std::string_view("789")) );
#else
    EXPECT( !!"std::string_view is not available (pre C++17)." );
#endif
}

CASE( "contains: true if string contains regular expression - string-std::regexp" )
{
#if string_HAVE_REGEX
    EXPECT(     contains(std::string("abc123xyz"), std::regex("[0-9]+")) );
    EXPECT_NOT( contains(std::string("abc123xyz"), std::regex("[4-9]+")) );
#else
    EXPECT( !!"contains_re is not available (pre C++11)." );
#endif
}

CASE( "contains_re: true if string contains regular expression - string-char*" )
{
#if string_HAVE_REGEX
    EXPECT(     contains_re(std::string("abc123xyz"), "[0-9]+") );
    EXPECT_NOT( contains_re(std::string("abc123xyz"), "[4-9]+") );
#else
    EXPECT( !!"contains_re is not available (pre C++11)." );
#endif
}

CASE( "contains_re: true if string contains regular expression - string-string" )
{
#if string_HAVE_REGEX
    EXPECT(     contains_re(std::string("abc123xyz"), std::string("[0-9]+")) );
    EXPECT_NOT( contains_re(std::string("abc123xyz"), std::string("[4-9]+")) );
#else
    EXPECT( !!"contains_re is not available (pre C++11)." );
#endif
}

CASE( "find: iterator to sub string in string - string-char*" )
{
    // text((): "abc123xyz"

    EXPECT( text_end() != find(text(), "123") );
    EXPECT( text_end() == find(text(), "789") );
}

CASE( "find: iterator to sub string in string - string-string" )
{
    // text((): "abc123xyz"

    EXPECT( text_end() != find(text(), std::string("123")) );
    EXPECT( text_end() == find(text(), std::string("789")) );
}

CASE( "find: iterator to sub string in string - string-string_view" )
{
#if string_HAVE_STD_STRING_VIEW
    // text((): "abc123xyz"

    EXPECT( text_end() != find(text(), std::string_view("123")) );
    EXPECT( text_end() == find(text(), std::string_view("789")) );
#else
    EXPECT( !!"std::string_view is not available (pre C++17)." );
#endif
}

CASE( "find: iterator to sub string in string_view - string_view-string_view" )
{
#if string_HAVE_STD_STRING_VIEW
    // text((): "abc123xyz"

    EXPECT( text_view_end() != find(text_view(), std::string_view("123")) );
    EXPECT( text_view_end() == find(text_view(), std::string_view("789")) );
#else
    EXPECT( !!"std::string_view is not available (pre C++17)." );
#endif
}

// Modifiers:

CASE( "clear: Makes string empty - char *" )
{
    scoped_str s( lstr() );

    clear( s.get() );

    EXPECT( *s == '\0' );
}

CASE( "clear: Makes string empty - string" )
{
    std::string s(lstr());

    clear( s );

    EXPECT( s  == "" );
    EXPECT( s.length() == 0u );
}

CASE( "to_lowercase: Makes string lowercase - char *" )
{
    scoped_str s( ustr() );

    to_lowercase( s.get() );

    EXPECT( std::strcmp(s, lstr()) == 0 );
}

CASE( "to_uppercase: Makes string uppercase - char *" )
{
    scoped_str s( lstr() );

    to_uppercase( s.get() );

    EXPECT( std::strcmp(s, ustr()) == 0 );
}

CASE( "to_lowercase: Makes string lowercase - string" )
{
    std::string ls( lstr() );
    std::string  s( ustr() );

    to_lowercase( s );

    EXPECT( s == ls );
}

CASE( "to_uppercase: Makes string uppercase - string" )
{
    std::string us( ustr() );
    std::string  s( lstr() );

    to_uppercase( s );

    EXPECT( s == us );
}

CASE( "as_lowercase: Returns string in lowercase - string" )
{
    std::string ls( lstr() );
    std::string us( ustr() );

    EXPECT( as_lowercase(us) == ls );
}

CASE( "as_uppercase: Returns string in uppercase - string" )
{
    std::string ls( lstr() );
    std::string us( ustr() );

    EXPECT( as_uppercase(ls) == us );
}

CASE( "clear: Makes string empty - string " "[unicode]" )
{
#if string_HAS_CSSTRING
    CsString::CsString s( "α β γ δ ε ζ η θ ι κ λ μ ν ξ ο π ρ ς σ τ υ φ χ ψ ω" );

    EXPECT( s  == s );

    clear( s );

    EXPECT( s  == "" );
    EXPECT( s.length() == 0u );
#else
    EXPECT( !!"Unicode via CsString is not available (pre C++17)." );
#endif
}

CASE( "to_upper: Makes string uppercase - string " "[unicode][.todo]" )
{
#if string_HAS_CSSTRING
    // el_EU ISO-8859-7x   Greek language locale for Europe (Euro symbol added)
    // el_GR ISO-8859-7    Greek language locale for Greece

    // std::locale::global(std::locale("el_GR"));

    CsString::CsString ls( "α β γ δ ε ζ η θ ι κ λ μ ν ξ ο π ρ σ τ υ φ χ ψ ω" );
    CsString::CsString us( "Α Β Γ Δ Ε Ζ Η Θ Ι Κ Λ Μ Ν Ξ Ο Π Ρ Σ Τ Υ Φ Χ Ψ Ω" );
    CsString::CsString  s( ls );

    // to_upper( s );

    EXPECT( s == us );
#else
    EXPECT( !!"Unicode via CsString is not available (pre C++17)." );
#endif
}

CASE( "tweak header: Reads tweak header if supported " "[tweak]" )
{
#if string_HAVE_TWEAK_HEADER
    EXPECT( string_TWEAK_VALUE == 42 );
#else
    EXPECT( !!"Tweak header is not available (string_HAVE_TWEAK_HEADER: 0)." );
#endif
}
} // anonymous namespace
