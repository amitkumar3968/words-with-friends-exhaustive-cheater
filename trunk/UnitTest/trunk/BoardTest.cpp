#include "TestHarness.h"
#include "Board.h"

#include <vector>

namespace
{
    const std::string TEST_DATA = "../TestData/BoardTest/";

    bool CheckGetLine( Board::Iterator& itr,
                       Board::Iterator& end,
                       const char expString[] )
    {
        bool rtn = false;
        int i = 0;
        for( ; itr != end; ++itr )
        {
            rtn = true; // ensure it run inside the loop
            if( itr->type != Board::ORIGINAL ||
                itr->ch != expString[i++] )
                return false;
        }
        return rtn;
    }

    bool CheckPlacedTiles( const PlacedTileInfo* actual, int actualSize,
                           const PlacedTileInfo* expect, int expectSize )
    {
        if( expectSize == 0 ||
            actualSize != expectSize )
            return false;

        for(int i=0;i<expectSize;++i)
        {
            if( actual[i] != expect[i])
                return false;
        }
        return true;
    }
}


TEST( Board, Iterator_vertical )
{
    Board subject;
    subject.ResetFromFile( TEST_DATA + "boardForIterator.txt" );

    Board::Iterator end1;
    Board::Iterator end2;

    CHECK( subject.GetEnds( 6, 7, true, end1, end2 ) );

    // operator *
    CHECK( (*end1).type == Board::ORIGINAL );
    CHECK( (*end1).ch == 'a' );

    CHECK( (*end2).type == Board::ORIGINAL );
    CHECK( (*end2).ch == 'p' );

    // operator ->
    CHECK( end1->type == Board::ORIGINAL );
    CHECK( end1->ch == 'a' );

    CHECK( end2->type == Board::ORIGINAL );
    CHECK( end2->ch == 'p' );

    // operator ++
    CHECK( (++end1)->type == Board::ORIGINAL );
    CHECK( end1->ch == 'b' );

    // operator --
    CHECK( (--end2)->type == Board::ORIGINAL );
    CHECK( end1->ch == 'o' );

    // operator ==
    for(int i=0; i<8; ++i)
        --end2;

    CHECK( end1 == end2 );


    // operator !=
    ++end1;
    CHECK( end1 != end2 );

    // empty grid
    --end2;
    --end2;

    CHECK( end2->type == Board::EMPTY )

    // BOUNDARY

    for(int i=0; i<9; ++i)
        ++end1;

    CHECK( end1->type == Board::ORIGINAL );
    CHECK( end1->ch == 'p' );

    ++end1;
    CHECK( end1 == subject.BOUNDARY );
    ++end1;
    CHECK( end1 == subject.BOUNDARY );
    
}


TEST( Board, Iterator_horizontal )
{
    Board subject;
    subject.ResetFromFile( TEST_DATA + "boardForIterator.txt" );

    Board::Iterator end1;
    Board::Iterator end2;

    CHECK( subject.GetEnds( 6, 7, false, end1, end2 ) );

    // operator *
    CHECK( (*end1).type == Board::ORIGINAL );
    CHECK( (*end1).ch == 'q' );

    CHECK( (*end2).type == Board::ORIGINAL );
    CHECK( (*end2).ch == 's' );

    // operator ->
    CHECK( end1->type == Board::ORIGINAL );
    CHECK( end1->ch == 'q' );

    CHECK( end2->type == Board::ORIGINAL );
    CHECK( end2->ch == 's' );

    // operator ++
    CHECK( (++end1)->type == Board::ORIGINAL );
    CHECK( end1->ch == 'w' );

    // operator --
    CHECK( (--end2)->type == Board::ORIGINAL );
    CHECK( end1->ch == 'a' );

    // operator ==
    for(int i=0; i<8; ++i)
        --end2;

    CHECK( end1 == end2 );


    // operator !=
    ++end1;
    CHECK( end1 != end2 );

    // empty grid
    --end2;
    --end2;

    CHECK( end2->type == Board::EMPTY )

    // BOUNDARY

    for(int i=0; i<9; ++i)
        ++end1;

    CHECK( end1->type == Board::ORIGINAL );
    CHECK( end1->ch == 'p' );

    ++end1;
    CHECK( end1 == subject.BOUNDARY );
    ++end1;
    CHECK( end1 == subject.BOUNDARY );
    
}


TEST( Board, GetLine )
{
    Board subject;
    subject.ResetFromFile( TEST_DATA + "normalBoard.txt" );

    Board::Iterator itr;
    Board::Iterator end;

    CHECK( subject.GetLine( 6, 7, true, itr, end ) );
    CHECK( CheckGetLine( itr, end, "abcdeflmnop" ) );

    CHECK( subject.GetLine( 6, 7, false, itr, end ) );
    CHECK( CheckGetLine( itr, end, "discard" ) );

    CHECK( subject.GetLine( 8, 14, false, itr, end ) );
    CHECK( CheckGetLine( itr, end, "eerrttyy" ) );

    CHECK( subject.GetLine( 8, 14, true, itr, end ) );
    CHECK( CheckGetLine( itr, end, "y" ) );

    CHECK( subject.GetLine( 6, 5, true, itr, end ) );
    CHECK( CheckGetLine( itr, end, "iii" ) );

    CHECK( !subject.GetLine( 3, 3, true, itr, end ) );

    CHECK( !subject.GetLine( 3, 3, false, itr, end ) );

    CHECK( !subject.GetLine( 15, 15, true, itr, end ) );

}


TEST( Board, GetEnds )
{
    Board subject;
    subject.ResetFromFile( TEST_DATA + "normalBoard.txt" );

    Board::Iterator front;
    Board::Iterator back;

    CHECK( subject.GetEnds( 6, 7, true, front, back ) );

    CHECK( front->type == Board::ORIGINAL );
    CHECK( front->ch == 'a' );

    CHECK( back->type == Board::ORIGINAL );
    CHECK( back->ch == 'p' );

    CHECK( subject.GetEnds( 6, 7, false, front, back ) );

    CHECK( front->type == Board::ORIGINAL );
    CHECK( front->ch == 'd' );

    CHECK( back->type == Board::ORIGINAL );
    CHECK( back->ch == 'd' );

    CHECK( subject.GetEnds( 8, 14, false, front, back ) );
    CHECK( front->type == Board::ORIGINAL );
    CHECK( front->ch == 'e' );

    CHECK( back->type == Board::ORIGINAL );
    CHECK( back->ch == 'y' );

    CHECK( subject.GetEnds( 8, 14, true, front, back ) );

    CHECK( front->type == Board::ORIGINAL );
    CHECK( front->ch == 'y' );

    CHECK( back->type == Board::ORIGINAL );
    CHECK( back->ch == 'y' );

    CHECK( front == back );

    CHECK( subject.GetEnds( 6, 5, true, front, back ) );

    CHECK( front->type == Board::ORIGINAL );
    CHECK( front->ch == 'i' );

    CHECK( back->type == Board::ORIGINAL );
    CHECK( back->ch == 'i' );

    CHECK( front != back );

    CHECK( !subject.GetEnds( 3, 3, true, front, back ) );

    CHECK( !subject.GetEnds( 3, 3, false, front, back ) );

    CHECK( !subject.GetEnds( 15, 15, false, front, back ) );

}



TEST( Board, Place_vertical )
{
    Board subject;
    subject.ResetFromFile( TEST_DATA + "normalBoard.txt" );

    CHECK( subject.Place( 4, 10, 'n' ) );
    CHECK( subject.Place( 5, 10, 'o' ) );
    CHECK( subject.Place( 6, 10, 't' ) );

    CHECK( subject.Place( 8, 10, 'i' ) );

    CHECK( subject.Place( 10, 10, 't' ) );
    CHECK( subject.Place( 11, 10, 'y' ) );

    Board::Iterator itr;
    Board::Iterator end;

    CHECK( subject.GetLine( 4, 10, true, itr, end ) );
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'n' );

    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'o' );
    
    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 't' );

    ++itr;
    CHECK( itr->type == Board::ORIGINAL );
    CHECK( itr->ch == 'd' );
    
    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'i' );

    ++itr;
    CHECK( itr->type == Board::ORIGINAL );
    CHECK( itr->ch == 'r' );
    
    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 't' );

    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'y' );

    ++itr;
    CHECK( itr == end );
}


TEST( Board, Place_horizontal )
{
    Board subject;
    subject.ResetFromFile( TEST_DATA + "normalBoard.txt" );

    //place to invalid position
    CHECK( !subject.Place( 15, 15, 'f' ) );

    //place to ORIGINAL position
    CHECK( !subject.Place( 5, 12, 'x' ) );

    CHECK( subject.Place( 0, 12, 'f' ) );
    CHECK( subject.Place( 1, 12, 'e' ) );
    CHECK( subject.Place( 2, 12, 'l' ) );
    CHECK( subject.Place( 3, 12, 'i' ) );
    CHECK( subject.Place( 4, 12, 'x' ) );
    CHECK( subject.Place( 6, 12, 'i' ) );
    CHECK( subject.Place( 8, 12, 'g' ) );

    //place to placed position
    CHECK( !subject.Place(  8, 12, 'x' ) );

    CHECK( subject.GetPlacedNum() == 7 );

    std::vector<PlacedTileInfo> expectPlaceTiles;
    expectPlaceTiles.push_back( PlacedTileInfo( 0, 12, 'f' ) );
    expectPlaceTiles.push_back( PlacedTileInfo( 1, 12, 'e' ) );
    expectPlaceTiles.push_back( PlacedTileInfo( 2, 12, 'l' ) );
    expectPlaceTiles.push_back( PlacedTileInfo( 3, 12, 'i' ) );
    expectPlaceTiles.push_back( PlacedTileInfo( 4, 12, 'x' ) );
    expectPlaceTiles.push_back( PlacedTileInfo( 6, 12, 'i' ) );
    expectPlaceTiles.push_back( PlacedTileInfo( 8, 12, 'g' ) );
    
    CHECK( CheckPlacedTiles( subject.GetPlacedTiles(), subject.GetPlacedNum(),
                             &expectPlaceTiles[0], expectPlaceTiles.size() ) );

    Board::Iterator itr;
    Board::Iterator end;

    CHECK( subject.GetLine( 8, 12, false, itr, end ) );
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'f' );

    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'e' );
    
    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'l' );

    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'i' );
    
    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'x' );

    ++itr;
    CHECK( itr->type == Board::ORIGINAL );
    CHECK( itr->ch == 'l' );
    
    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'i' );

    ++itr;
    CHECK( itr->type == Board::ORIGINAL );
    CHECK( itr->ch == 'n' );

    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'g' );

    ++itr;
    CHECK( itr == end );

    //placed too many
    CHECK( !subject.Place( 0, 12, 'f' ) );
}


TEST( Board, Undo )
{
    Board subject;
    subject.ResetFromFile( TEST_DATA + "normalBoard.txt" );

    CHECK( !subject.Undo() );

    CHECK( subject.Place( 0, 12, 'f' ) );
    CHECK( subject.Place( 1, 12, 'e' ) );
    CHECK( subject.Place( 2, 12, 'l' ) );
    CHECK( subject.Place( 3, 12, 'i' ) );

    std::vector<PlacedTileInfo> expectPlaceTiles;
    expectPlaceTiles.push_back( PlacedTileInfo( 0, 12, 'f' ) );
    expectPlaceTiles.push_back( PlacedTileInfo( 1, 12, 'e' ) );
    expectPlaceTiles.push_back( PlacedTileInfo( 2, 12, 'l' ) );
    expectPlaceTiles.push_back( PlacedTileInfo( 3, 12, 'i' ) );
    
    CHECK( CheckPlacedTiles( subject.GetPlacedTiles(), subject.GetPlacedNum(),
                             &expectPlaceTiles[0], expectPlaceTiles.size() ) );

    CHECK( subject.Undo() );

    expectPlaceTiles.pop_back();
    CHECK( CheckPlacedTiles( subject.GetPlacedTiles(), subject.GetPlacedNum(),
                             &expectPlaceTiles[0], expectPlaceTiles.size() ) );

    CHECK( subject.Place( 4, 12, 'x' ) );
    CHECK( subject.Place( 6, 12, 'i' ) );
    CHECK( subject.Place( 8, 12, 'g' ) );

    expectPlaceTiles.push_back( PlacedTileInfo( 4, 12, 'x' ) );
    expectPlaceTiles.push_back( PlacedTileInfo( 6, 12, 'i' ) );
    expectPlaceTiles.push_back( PlacedTileInfo( 8, 12, 'g' ) );

    CHECK( CheckPlacedTiles( subject.GetPlacedTiles(), subject.GetPlacedNum(),
                             &expectPlaceTiles[0], expectPlaceTiles.size() ) );

    Board::Iterator itr;
    Board::Iterator end;

    CHECK( subject.GetLine( 8, 12, false, itr, end ) );
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'x' );

    ++itr;
    CHECK( itr->type == Board::ORIGINAL );
    CHECK( itr->ch == 'l' );
    
    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'i' );

    ++itr;
    CHECK( itr->type == Board::ORIGINAL );
    CHECK( itr->ch == 'n' );

    ++itr;
    CHECK( itr->type == Board::PLACED );
    CHECK( itr->ch == 'g' );

    ++itr;
    CHECK( itr == end );
    for(int i=0;i<6;++i)
        CHECK( subject.Undo() );

    CHECK( subject.GetPlacedNum() == 0 );
    CHECK( !subject.Undo() );
}


