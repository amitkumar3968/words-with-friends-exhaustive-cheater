#include "TestHarness.h"
#include "ExhaustiveVisitor.h"
#include "ScoreRank.h"

#include <iostream>
#include <time.h>

namespace
{
    const std::string TEST_DATA = "../TestData/ExhaustiveVisitorTest/";
}

TEST( ExhaustiveVisitor, Normal )
{
    ScoreRank scoreRank;
    ExhaustiveVisitor subject( &scoreRank,  TEST_DATA + "../RealDictionary/enable1.txt" );

    Board board;
    board.ResetFromFile( TEST_DATA + "normal.txt" );

    char* tiles = "peeabsc";

    subject.Initialize( board, tiles );

    clock_t start, finish;
    start = clock();
    subject.RankExhaustively( );
    finish = clock();

    std::cout << double(finish - start)/CLOCKS_PER_SEC  << "ms taken for running 1 combination with exhaustive Visitor." << std::endl;

    std::vector<ScoreRank::RankEntity>::const_iterator begin;
    std::vector<ScoreRank::RankEntity>::const_iterator end;
    scoreRank.GetResults( begin, end );

    std::cout<< "results:" << std::endl;;
    
    for( std::vector<ScoreRank::RankEntity>::const_iterator itr = begin;
         itr != end;
         ++itr )
    {
        std::cout<< "score: " << itr->m_score << std::endl;
        board.printToStream( std::cout, itr->m_placedTiles, itr->m_numPlacedTiles );
    }
}