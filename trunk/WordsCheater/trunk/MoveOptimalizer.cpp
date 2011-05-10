#include "MoveOptimalizer.h"

#include <algorithm>
#include <iostream>
#include <time.h>

namespace
{
    int fac( int i)
    {
        if( i > 1 )
            return i * fac(i);

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

void MoveOptimalizer::OptimizeMove( std::vector<char>& tileToPlace )
{
    if( tileToPlace.size( ) != Board::MAX_TILES_TO_PLACE )
        throw std::invalid_argument( __FUNCTION__ "tileToPlace has not 7 tile" );

    m_iniBoard.ResetFromFile( m_inputBoardPath );
    m_ranker.Reset( );

    std::sort( &tileToPlace[0], &tileToPlace[0] + Board::MAX_TILES_TO_PLACE );

    clock_t start, finish;
    start = clock();

    int count = 1;
    const int totalRunNum = fac( Board::MAX_TILES_TO_PLACE );

    do
    {
        std::cout << "run# " << count << " ...";
        clock_t eachStart, eachFinish;
        eachStart = clock();
        m_visitor.Initialize( m_iniBoard, &tileToPlace[0] );
        m_visitor.RankExhaustively( );
        eachFinish = clock();
        std::cout << "done. Taken: " << double(eachFinish - eachStart)/CLOCKS_PER_SEC  << "s. "
                  << "remaining: " << ( double( eachFinish - start ) / count ) * ( totalRunNum - count )  << "s. " << std::endl;
        ++count;
    } while( std::next_permutation( &tileToPlace[0], &tileToPlace[0] + Board::MAX_TILES_TO_PLACE ) );
    finish = clock();

    std::cout << "Finished. Total Time Taken: " << double(finish - start)/CLOCKS_PER_SEC  << "s" <<std::endl;

    m_ranker.GetResults( m_resultBegin, m_resultEnd );
}

Result_it& MoveOptimalizer::result_begin( )
{
    return m_resultBegin;
}

Result_it& MoveOptimalizer::result_end( )
{
    return m_resultEnd;
}