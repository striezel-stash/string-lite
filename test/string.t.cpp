// Copyright 2021-2021 Martin Moene
//
// https://github.com/martinmoene/string-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "string-main.t.hpp"

namespace {

using namespace nonstd;

CASE( "clear: Makes string empty - char *" )
{
    char s[5] = "abc";

    clear( s );

    EXPECT( *s == '\0' );
}

CASE( "clear: Makes string empty - string" )
{
    std::string s("abc");

    clear( s );

    EXPECT( s  == "" );
    EXPECT( s.length() == 0u );
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
