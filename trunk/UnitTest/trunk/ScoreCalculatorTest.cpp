#include "TestHarness.h"

#include "ScoreCalculator.h"
#include "Board.h"
#include "Dictionary.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    const std::string TEST_DATA = "../TestData/ScoreCalculatorTest/";

    bool LoadTestCase( std::ifstream& file, Board& board, bool& expRtn, int& expScore )
    {
        expScore = 0;
        std::vector<PlacedTileInfo> placedTiles;
        if( board.ParseFileBoard( file, placedTiles ) )
        {
            for( std::vector<PlacedTileInfo>::iterator itr = placedTiles.begin();
                 itr != placedTiles.end();
                 ++itr )
            {
                board.Place( itr->m_row, itr->m_col, itr->m_placedChar );
            }
            std::string str;
            if( getline( file, str, '\n' ) )
            {
                if( str == "true")
                    expRtn = true;
                else if( str == "false" )
                    expRtn = false;
            }
            file >> expScore;
            return true;
        }
        return false;
    }
}

TEST( ScoreCalculator, TestDriven )
{
    std::ifstream file ( TEST_DATA + "all.txt", std::ios_base::in );
    if( !file )
        return;

    Board board;
    Dictionary dict(  TEST_DATA + "enable1.txt" );
    ScoreCalculator subject( &board, &dict );

    int numTestCase = 0;

    while( 1 )
    {
        board.Reset();
        int score = 0;
        bool expRtn = false;
        int expScore = 0;

        if( LoadTestCase( file, board, expRtn, expScore ) )
        {
            ++numTestCase;
            //board.printToStream( std::cout, 0,0 );
            //std::cout<<expRtn<<std::endl;
            //std::cout<<expScore<<std::endl;

            CHECK( expRtn == subject.Calculate( score ) );
            if( expRtn )
                CHECK( score == expScore );
            
        }
        else
            break;
    }

    std::cout << numTestCase << " Test Cases Passed.";
}