#include "TestHarness.h"
#include "Dictionary.h"

namespace
{
    const std::string dictPath = "../TestData/DictionaryTest/dict.txt";
}

TEST( Dictionay, Constructor )
{
    try
    {
        Dictionary dict( "asdsf" );
        CHECK( false );
    }
    catch( std::invalid_argument e )
    {
        CHECK( true );
    }

    try
    {
        Dictionary dict( dictPath );
    }
    catch( std::invalid_argument e )
    {
        CHECK(false);
    }
}

TEST( Dictionay, IsStringValid )
{
    //valid string
    Dictionary dict( dictPath );
    CHECK( dict.IsStringValid( "abc" ) );
    CHECK( dict.IsStringValid( "edd" ) );
    CHECK( dict.IsStringValid( "irfwoi" ) );
    CHECK( dict.IsStringValid( "sekr" ) );
    CHECK( dict.IsStringValid( "xzeei" ) );

    //Invalid string
    CHECK( !dict.IsStringValid( "ab" ) );
    CHECK( !dict.IsStringValid( "fwoi" ) );
    CHECK( !dict.IsStringValid( "abcc" ) );
    CHECK( !dict.IsStringValid( "edds" ) );
    CHECK( !dict.IsStringValid( "ierfwoi" ) );
    CHECK( !dict.IsStringValid( "serkr" ) );
    CHECK( !dict.IsStringValid( "xzefei" ) );
    CHECK( !dict.IsStringValid( "wwed" ) );
    CHECK( !dict.IsStringValid( "s" ) );
    CHECK( !dict.IsStringValid( "" ) );
}

TEST( Dictionay, IsSubStringValid )
{
    //valid string
    Dictionary dict( dictPath );
    CHECK( dict.IsSubStringValid( "ab" ) );
    CHECK( dict.IsSubStringValid( "abc" ) );
    CHECK( dict.IsSubStringValid( "edd" ) );
    CHECK( dict.IsSubStringValid( "fwoi" ) );
    CHECK( dict.IsSubStringValid( "sek" ) );
    CHECK( dict.IsSubStringValid( "zeei" ) );

    //Invalid string
    CHECK( !dict.IsSubStringValid( "adb" ) );
    CHECK( !dict.IsSubStringValid( "eddd" ) );
    CHECK( !dict.IsSubStringValid( "fwosi" ) );
    CHECK( !dict.IsSubStringValid( "xzefei" ) );
    CHECK( !dict.IsSubStringValid( "wwed" ) );
    CHECK( !dict.IsSubStringValid( "s" ) );
    CHECK( !dict.IsSubStringValid( "" ) );
}

TEST( Dictionary, WildChar )
{
    //valid string for IsStringValid
    Dictionary dict( dictPath );
    CHECK( dict.IsStringValid( "a.c" ) );
    CHECK( dict.IsStringValid( ".dd" ) );
    CHECK( dict.IsStringValid( "irfwo." ) );
    CHECK( dict.IsStringValid( "s..r" ) );
    CHECK( dict.IsStringValid( "x.e.i" ) );
    CHECK( dict.IsStringValid( "..." ) );
   
    //valid string for IsSubStringValid
    CHECK( dict.IsSubStringValid( "a." ) );
    CHECK( dict.IsSubStringValid( "e.d" ) );
    CHECK( dict.IsSubStringValid( "f..i" ) );
    CHECK( dict.IsSubStringValid( ".ek" ) );
    CHECK( dict.IsSubStringValid( "z.e." ) );
    CHECK( dict.IsSubStringValid( "..." ) );

    //Invalid string for IsSubStringValid
    CHECK( !dict.IsStringValid( "ass." ) );
    CHECK( !dict.IsStringValid( "." ) );

    //Invalid string for IsSubStringValid
    CHECK( !dict.IsSubStringValid( "ad." ) );
    CHECK( !dict.IsSubStringValid( "." ) );
}