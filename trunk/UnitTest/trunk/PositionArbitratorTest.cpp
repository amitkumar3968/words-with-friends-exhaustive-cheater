#include "TestHarness.h"
#include "PositionArbitrator.h"

#include "Board.h"

#include <vector>

namespace
{
    const std::string TEST_DATA = "../TestData/PositionArbitratorTest/";
}

TEST( PositionArbitrator, notPlaced )
{
    Board board;
    board.ResetFromFile( TEST_DATA + "normal.txt" );
    PositionArbitrator subject( &board );
    subject.Reset();

    // prepare expected result for not placed yet
    std::vector<Position> expResult;
    expResult.push_back( Position( 3, 7 ) );
    expResult.push_back( Position( 4, 5 ) );
    expResult.push_back( Position( 4, 6 ) );
    expResult.push_back( Position( 4, 8 ) );
    expResult.push_back( Position( 5, 4 ) );
    expResult.push_back( Position( 5, 6 ) );
    expResult.push_back( Position( 5, 8 ) );
    expResult.push_back( Position( 5, 9 ) );
    expResult.push_back( Position( 5, 10 ) );
    expResult.push_back( Position( 6, 3 ) );
    expResult.push_back( Position( 6, 11 ) );
    expResult.push_back( Position( 7, 4 ) );
    expResult.push_back( Position( 7, 6 ) );
    expResult.push_back( Position( 7, 8 ) );
    expResult.push_back( Position( 7, 9 ) );
    expResult.push_back( Position( 7, 10 ) );
    expResult.push_back( Position( 7, 11 ) );
    expResult.push_back( Position( 7, 12 ) );
    expResult.push_back( Position( 7, 13 ) );
    expResult.push_back( Position( 7, 14 ) );
    expResult.push_back( Position( 8, 5 ) );
    expResult.push_back( Position( 9, 4 ) );
    expResult.push_back( Position( 9, 6 ) );
    expResult.push_back( Position( 9, 8 ) );
    expResult.push_back( Position( 9, 9 ) );
    expResult.push_back( Position( 9, 10 ) );
    expResult.push_back( Position( 9, 11 ) );
    expResult.push_back( Position( 9, 12 ) );
    expResult.push_back( Position( 9, 13 ) );
    expResult.push_back( Position( 9, 14 ) );
    expResult.push_back( Position( 10, 3 ) );
    expResult.push_back( Position( 10, 9 ) );
    expResult.push_back( Position( 11, 4 ) );
    expResult.push_back( Position( 11, 6 ) );
    expResult.push_back( Position( 11, 8 ) );
    expResult.push_back( Position( 12, 4 ) );
    expResult.push_back( Position( 12, 6 ) );
    expResult.push_back( Position( 12, 8 ) );
    expResult.push_back( Position( 13, 4 ) );
    expResult.push_back( Position( 13, 6 ) );
    expResult.push_back( Position( 13, 8 ) );
    expResult.push_back( Position( 14, 5 ) );
    expResult.push_back( Position( 14, 6 ) );
    expResult.push_back( Position( 14, 8 ) );

    std::vector<Position> result = subject.GetPositionsToPlace( );

    CHECK( result.size() == expResult.size() );
    for(unsigned int i=0; i<result.size(); ++i )
    {
        CHECK( result[i] == expResult[i] );
    }


}

TEST( PositionArbitrator, FirstPlaced )
{
    Board board;
    board.ResetFromFile( TEST_DATA + "normal.txt" );
    PositionArbitrator subject( &board );
    subject.Reset();

    std::vector<Position> expResult;
    expResult.push_back( Position( 4, 5 ) );
    expResult.push_back( Position( 14, 5 ) );
    expResult.push_back( Position( 8, 4 ) );

    board.Place( 8, 5, 'i' );
    std::vector<Position> result = subject.GetPositionsToPlace( );
    CHECK( result.size() == expResult.size() );
    for(unsigned int i=0; i<result.size(); ++i )
    {
        CHECK( result[i] == expResult[i] );
    }
}

TEST( PositionArbitrator, SecondPlaced )
{
    Board board;
    board.ResetFromFile( TEST_DATA + "normal.txt" );
    PositionArbitrator subject( &board );
    subject.Reset();

    std::vector<Position> expResult;
    expResult.push_back( Position( 4, 5 ) );

    board.Place( 8, 5, 'i' );
    board.Place( 14, 5 , 'g' );
    std::vector<Position> result = subject.GetPositionsToPlace( );
    CHECK( result.size() == expResult.size() );
    for(unsigned int i=0; i<result.size(); ++i )
    {
        CHECK( result[i] == expResult[i] );
    }
}

TEST( PositionArbitrator, MoreThanSecondPlaced )
{
    Board board;
    board.ResetFromFile( TEST_DATA + "normal.txt" );
    PositionArbitrator subject( &board );
    subject.Reset();

    std::vector<Position> expResult;
    expResult.push_back( Position( 3, 5 ) );

    board.Place( 8, 5, 'i' );
    board.Place( 14, 5 , 'g' );
    board.Place( 4, 5 , 'g' );

    std::vector<Position> result = subject.GetPositionsToPlace( );
    CHECK( result.size() == expResult.size() );
    for(unsigned int i=0; i<result.size(); ++i )
    {
        CHECK( result[i] == expResult[i] );
    }

    expResult.clear();
    expResult.push_back( Position( 2, 5 ) );

    board.Place( 3, 5, 'i' );

    std::vector<Position> result2 = subject.GetPositionsToPlace( );
    CHECK( result2.size() == expResult.size() );
    for(unsigned int i=0; i<result2.size(); ++i )
    {
        CHECK( result2[i] == expResult[i] );
    }
}

TEST( PositionArbitrator, SevenPlaced )
{
    Board board;
    board.ResetFromFile( TEST_DATA + "normal.txt" );
    PositionArbitrator subject( &board );
    subject.Reset();

    board.Place( 8, 5, 'i' );
    board.Place( 14, 5, 'g' );
    board.Place( 4, 5 , 'g' );
    board.Place( 3, 5, 'i' );
    board.Place( 2, 5, 'a' );
    board.Place( 1, 5, 'c' );
    board.Place( 0, 5, 'i' );

    try
    {
        std::vector<Position> result = subject.GetPositionsToPlace( );
        CHECK( false );
    }
    catch( std::runtime_error )
        CHECK( true );
}

TEST( PositionArbitrator, Horizontal )
{
    Board board;
    board.ResetFromFile( TEST_DATA + "normal.txt" );
    PositionArbitrator subject( &board );
    subject.Reset();

    std::vector<Position> expResult;
    expResult.push_back( Position( 4, 8 ) );
    expResult.push_back( Position( 7, 8 ) );
    expResult.push_back( Position( 5, 6 ) );
    expResult.push_back( Position( 5, 9 ) );

    board.Place( 5, 8, 'i' );
    std::vector<Position> result = subject.GetPositionsToPlace( );
    CHECK( result.size() == expResult.size() );
    for(unsigned int i=0; i<result.size(); ++i )
    {
        CHECK( result[i] == expResult[i] );
    }

    expResult.clear();
    expResult.push_back( Position( 5, 4 ) );
    expResult.push_back( Position( 5, 9 ) );

    board.Place( 5, 6, 'd' );
    std::vector<Position> result2 = subject.GetPositionsToPlace( );
    CHECK( result2.size() == expResult.size() );
    for(unsigned int i=0; i<result2.size(); ++i )
    {
        CHECK( result2[i] == expResult[i] );
    }
}