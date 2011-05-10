#include "MoveOptimalizer.h"

#include <algorithm>
#include <iostream>
#include <time.h>

namespace
{
    int fac( int i)
    {
        if( i > 1 )
            return i * fac(i-1);

        return 1;
    }
}

MoveOptimalizer::MoveOptimalizer( const std::string& DictPath,
                                  const std::string& inputBoardPath )
:  m_iniBoard           ( ),
   m_ranker             ( ),
   m_visitor            ( &m_ranker, DictPath ),
   m_inputBoardPath     ( inputBoardPath )
{

}


MoveOptimalizer::~MoveOptimalizer( )
{
}

void MoveOptimalizer::OptimizeMove( std::string& tileToPlace )
{
    if( tileToPlace.size( ) != Board::MAX_TILES_TO_PLACE )
        throw std::invalid_argument( __FUNCTION__ " tileToPlace has not 7 tile" );

    m_iniBoard.ResetFromFile( m_inputBoardPath );
    m_ranker.Reset( );

    clock_t start, finish;
    start = clock();

    clock_t eachStart, eachFinish;

    int count = 1;
    const int totalRunNum = fac( Board::MAX_TILES_TO_PLACE );

    int perm[] = { 0, 1, 2, 3, 4, 5, 6 };

    do
    {
        char tilesToPlacePerm[] = { tileToPlace.at( perm[0] ),
                                    tileToPlace.at( perm[1] ),
                                    tileToPlace.at( perm[2] ),
                                    tileToPlace.at( perm[3] ),
                                    tileToPlace.at( perm[4] ),
                                    tileToPlace.at( perm[5] ),
                                    tileToPlace.at( perm[6] ) };
        if ( count%100 == 0 )
        {
            std::cout << "run# " << count << " ...";
            eachStart = clock();
        }
            m_visitor.Initialize( m_iniBoard, tilesToPlacePerm );
            m_visitor.RankExhaustively( );
        if ( count%100 == 0 )
        {
            eachFinish = clock();
            int remainingTime  = ( double( eachFinish - start ) / count ) * ( totalRunNum - count ) / CLOCKS_PER_SEC;
            std::cout << "done. Taken: " << double(eachFinish - eachStart)/CLOCKS_PER_SEC  << "s. "
                      << "remaining: " << remainingTime/60 << "m " << remainingTime%60 << "s." <<std::endl;
            std::cout << "  call_count: " << m_visitor.s_runCount 
                << " submit: " << m_ranker.s_recordedCount <<"/"<<m_ranker.s_submitCount << std::endl;
        }
        ++count;
    } while( std::next_permutation( perm, perm + Board::MAX_TILES_TO_PLACE ) );

    finish = clock();

    std::cout << "Finished. Total Time Taken: " << double(finish - start)/CLOCKS_PER_SEC  << "s" <<std::endl;
}

void MoveOptimalizer::printResultToStream( std::ostream& stream )
{
    std::vector<ScoreRank::RankEntity>::const_iterator begin, end;
    m_ranker.GetResults( begin, end );

    for( std::vector<ScoreRank::RankEntity>::const_iterator itr = begin;
         itr != end;
         ++itr )
    {
        stream << "score: " << itr->m_score << std::endl;
        m_iniBoard.printToStream( stream, itr->m_placedTiles, itr->m_numPlacedTiles );
    }
}
