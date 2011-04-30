#include "TestHarness.h"
#include "TrieDictionary.h"

namespace
{
    const std::string DICT_FILE = "../TestData/DictionaryTest/dict.txt";
}

TEST( TrieDictionay, Constructor )
{
    try
    {
        TrieDictionary subject( "asdsf" );
        CHECK( false );
    }
    catch( std::invalid_argument e )
    {
        CHECK( true );
    }

    try
    {
        TrieDictionary subject( DICT_FILE );
    }
    catch( std::invalid_argument e )
    {
        CHECK(false);
    }
}

TEST( TrieDictionay, IsStringValid )
{
    TrieDictionary subject( DICT_FILE );

    //valid string
    CHECK( subject.IsStringValid( "abc" ) );
    CHECK( subject.IsStringValid( "edd" ) );
    CHECK( subject.IsStringValid( "irfwoi" ) );
    CHECK( subject.IsStringValid( "sekr" ) );
    CHECK( subject.IsStringValid( "xzeei" ) );

    //Invalid string
    CHECK( !subject.IsStringValid( "ab" ) );
    CHECK( !subject.IsStringValid( "fwoi" ) );
    CHECK( !subject.IsStringValid( "abcc" ) );
    CHECK( !subject.IsStringValid( "edds" ) );
    CHECK( !subject.IsStringValid( "ierfwoi" ) );
    CHECK( !subject.IsStringValid( "serkr" ) );
    CHECK( !subject.IsStringValid( "xzefei" ) );
    CHECK( !subject.IsStringValid( "wwed" ) );
    CHECK( !subject.IsStringValid( "s" ) );
    CHECK( !subject.IsStringValid( "" ) );
}
/*
TEST( TrieDictionay, IsSubStringValid )
{
    TrieDictionary subject( DICT_FILE );

    //valid string
    CHECK( subject.IsSubStringValid( "ab" ) );
    CHECK( subject.IsSubStringValid( "abc" ) );
    CHECK( subject.IsSubStringValid( "edd" ) );
    CHECK( subject.IsSubStringValid( "fwoi" ) );
    CHECK( subject.IsSubStringValid( "sek" ) );
    CHECK( subject.IsSubStringValid( "zeei" ) );

    //Invalid string
    CHECK( !subject.IsSubStringValid( "adb" ) );
    CHECK( !subject.IsSubStringValid( "eddd" ) );
    CHECK( !subject.IsSubStringValid( "fwosi" ) );
    CHECK( !subject.IsSubStringValid( "xzefei" ) );
    CHECK( !subject.IsSubStringValid( "wwed" ) );
    CHECK( !subject.IsSubStringValid( "s" ) );
    CHECK( !subject.IsSubStringValid( "" ) );
}*/

TEST( TrieDictionary, WildCharForIsStringValid )
{
    TrieDictionary subject( DICT_FILE );

    //valid string for IsStringValid
    CHECK( subject.IsStringValid( "a.c" ) );
    CHECK( subject.IsStringValid( ".dd" ) );
    CHECK( subject.IsStringValid( "irfwo." ) );
    CHECK( subject.IsStringValid( "s..r" ) );
    CHECK( subject.IsStringValid( "x.e.i" ) );
    CHECK( subject.IsStringValid( "..." ) );
   
    //Invalid string for IsStringValid
    CHECK( !subject.IsStringValid( "ass." ) );
    CHECK( !subject.IsStringValid( "." ) );
}
/*
TEST( TrieDictionary, WildCharForIsSubStringValid )
{
    TrieDictionary subject( DICT_FILE );

    //valid string for IsSubStringValid
    CHECK( subject.IsSubStringValid( "a." ) );
    CHECK( subject.IsSubStringValid( "e.d" ) );
    CHECK( subject.IsSubStringValid( "f..i" ) );
    CHECK( subject.IsSubStringValid( ".ek" ) );
    CHECK( subject.IsSubStringValid( "z.e." ) );
    CHECK( subject.IsSubStringValid( "..." ) );

    //Invalid string for IsSubStringValid
    CHECK( !subject.IsSubStringValid( "ad." ) );
    CHECK( !subject.IsSubStringValid( "." ) );
}*/