#include "ScoreCalculator.h"

#include "Board.h"
#include "Dictionary.h"

namespace
{
    enum GridBouns
    {
        II, //nothing
        DL,
        TL,
        DW,
        TW
    };

    const GridBouns BONUS[Board::MAX_GRID][Board::MAX_GRID]
        =   {
                { II, II, II, TW, II, II, TL, II, TL, II, II, TW, II, II, II,  },
                { II, II, DL, II, II, DW, II, II, II, DW, II, II, DL, II, II,  },
                { II, DL, II, II, DL, II, II, II, II, II, DL, II, II, DL, II,  },
                { TW, II, II, TL, II, II, II, DW, II, II, II, TL, II, II, TW,  },
                { II, II, DL, II, II, II, DL, II, DL, II, II, II, DL, II, II,  },
                { II, DW, II, II, II, TL, II, II, II, TL, II, II, II, DW, II,  },
                { TL, II, II, II, DL, II, II, II, II, II, DL, II, II, II, TL,  },
                { II, II, II, DW, II, II, II, II, II, II, II, DW, II, II, II,  },
                { TL, II, II, II, DL, II, II, II, II, II, DL, II, II, II, TL,  },
                { II, DW, II, II, II, TL, II, II, II, TL, II, II, II, DW, II,  },
                { II, II, DL, II, II, II, DL, II, DL, II, II, II, DL, II, II,  },
                { TW, II, II, TL, II, II, II, DW, II, II, II, TL, II, II, TW,  },
                { II, DL, II, II, DL, II, II, II, II, II, DL, II, II, DL, II,  },
                { II, II, DL, II, II, DW, II, II, II, DW, II, II, DL, II, II,  },
                { II, II, II, TW, II, II, TL, II, TL, II, II, TW, II, II, II,  }
            };
    //                           a  b  c  d  e  f  g  h  i  j   k  l  m  n  o  p  q   r  s  t  u  v  w  x  y  z   *
    const int CHAR_SCORE[27] = { 1, 4, 4, 2, 1, 4, 3, 3, 1, 10, 5, 2, 4, 2, 1, 4, 10, 1, 1, 1, 2, 5, 4, 8, 3, 10, 0 };
    const int CHAR_START = 'a';


}

ScoreCalculator::ScoreCalculator( Board* board, Dictionary* dict )
: m_board   ( board ),
  m_dict    ( dict )
{
    if( !m_board )
        throw std::invalid_argument( __FUNCTION__ "board cannot be null" );
    if( !m_dict )
        throw std::invalid_argument( __FUNCTION__ "dict cannot be null" );
}


ScoreCalculator::~ScoreCalculator( )
{
}


bool ScoreCalculator::Calculate( int& score )
{
    score = 0;
    int placedNum = m_board->GetPlacedNum();
    const Position* placedTiles = m_board->GetPlacedTiles();

    LineScoreResult result = CalculateLine( placedTiles[0].m_row, placedTiles[0].m_col, m_board->IsVertical(), score );
    if( result == NEVER_VALID )
        return false;
    else if( result == NOT_VALID )
        return true;
    else if ( result == ONE_TILE )
        throw std::runtime_error( __FUNCTION__ "only one tile, should be problem of PositionArbitrator");
    

    Board::Iterator start( m_board ), end( m_board );
    for( int i =0; i < placedNum; ++i )
    {
        int lineScore = 0;
        LineScoreResult lineResult = CalculateLine( placedTiles[i].m_row, placedTiles[i].m_col, !m_board->IsVertical(), lineScore );
    
        if( result == NEVER_VALID )
            return false;
        else if( result == NOT_VALID )
        {
            score = 0;
            return true;
        }
        else if( result == VALID ) 
        {
            score += lineScore;
        }
    }
    return true;
}

ScoreCalculator::LineScoreResult ScoreCalculator::CalculateLine( const int row,
                                                                 const int col,
                                                                 const bool isVertical,
                                                                 int& score )
{
    Board::Iterator start( m_board ), end( m_board );
    m_board->GetLine( row, col, isVertical, start, end );

    std::string str;
    str.reserve( Board::MAX_GRID );
    int multiplier = 1;
    score = 0;

    int numTiles = 0;
    for( Board::Iterator itr( start ) ; itr != end; ++itr )
    {
        str.push_back( itr->ch );
        ++numTiles;
    }
    if( numTiles == 1 )
        return ONE_TILE;

    if( !m_dict->IsSubStringValid( str ) )
        return NEVER_VALID;

    if( !m_dict->IsStringValid( str ) )
        return NOT_VALID;

    for( Board::Iterator itr( start ) ; itr != end; ++itr )
    {
        if( itr->type == Board::ORIGINAL )
            score += CHAR_SCORE[ itr->ch - CHAR_START ];
        else if( itr->type == Board::PLACED )
        {
            Position pos = itr.GetPosition();
            if( BONUS[pos.m_row][pos.m_col] == II )
                score += CHAR_SCORE[ itr->ch - CHAR_START ];

            else if( BONUS[pos.m_row][pos.m_col] == DL )
                score += CHAR_SCORE[ itr->ch - CHAR_START ] * 2;

            else if( BONUS[pos.m_row][pos.m_col] == TL )
                score += CHAR_SCORE[ itr->ch - CHAR_START ] * 3;

            else if( BONUS[pos.m_row][pos.m_col] == DW )
            {
                score += CHAR_SCORE[ itr->ch - CHAR_START ];
                multiplier *= 2;
            }
            else if( BONUS[pos.m_row][pos.m_col] == TW )
            {
                score += CHAR_SCORE[ itr->ch - CHAR_START ];
                multiplier *= 3;
            }
        }
    }
    score *= multiplier;
    return VALID;
}