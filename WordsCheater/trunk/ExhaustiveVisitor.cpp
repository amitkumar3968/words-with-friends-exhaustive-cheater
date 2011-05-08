#include "ExhaustiveVisitor.h"

#include "ScoreRank.h"
#include "TrieDictionary.h"

#include <iostream>


ExhaustiveVisitor::ExhaustiveVisitor( ScoreRank* scoreRank, std::string dictPath )
: m_board       ( ),
  m_dict        ( dictPath ),
  m_placingPos  ( &m_board ),
  m_scoreCal    ( &m_board, &m_dict ),
  m_scoreRank   ( scoreRank )
{
    if( !scoreRank )
        throw std::invalid_argument( " scoreRank cannot be null " );
}


ExhaustiveVisitor::~ExhaustiveVisitor( )
{
}

void ExhaustiveVisitor::Initialize( const Board board, const char* tilesToPlace )
{
    m_board.Reset( board );
    std::memcpy( m_tilesToPlace, tilesToPlace, Board::MAX_TILES_TO_PLACE );
    m_placingPos.Reset( );
}

void ExhaustiveVisitor::RankExhaustively( )
{
    if( m_board.GetPlacedNum( ) < Board::MAX_TILES_TO_PLACE )
    {
        //get position to place
        std::vector<Position> posToPlace( m_placingPos.GetPositionsToPlace( ) );

        for( std::vector<Position>::const_iterator it = posToPlace.begin( );
             it != posToPlace.end( );
             ++it )
        {
            // Place a char on the board
            m_board.Place( it->m_row,
                           it->m_col,
                           m_tilesToPlace[ m_board.GetPlacedNum( ) ] );

            // Calculate the score for the board
            int score;
            m_scoreCal.Calculate( score );

            // if the score is non zero -> submit to ranker
            if( score != 0 )
            {
                if(score == 27)
                    m_board.printToStream( std::cout, 0,0 );
                m_scoreRank->Submit( score, m_board.GetPlacedNum( ), m_board.GetPlacedTilesInfo( ) );
            }

            // call itself recursively 
            RankExhaustively( );
            m_board.Undo( );
        }
    }
}