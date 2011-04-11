#include "PositionArbitrator.h"

#include "Board.h"



PositionArbitrator::PositionArbitrator( Board* board )
: m_board                   ( board ),
  m_positionsFor1stPlaced   ( ),
  m_positions               ( )
{
    if( !m_board )
        throw std::invalid_argument( __FUNCTION__ "board cannot be null" );

    m_positionsFor1stPlaced.reserve( Board::MAX_GRID * Board::MAX_GRID );
    m_positions.reserve( 4 );
}

PositionArbitrator::~PositionArbitrator( )
{
}

void PositionArbitrator::Reset( )
{
    bool validToPlace[Board::MAX_GRID][Board::MAX_GRID];
    m_board->GetMarkedNeighbour( validToPlace );

    for(int i=0;i<Board::MAX_GRID;++i)
    {
        for(int j=0;j<Board::MAX_GRID;++j)
        {
            if( validToPlace[i][j] )
                m_positionsFor1stPlaced.push_back( Position( i, j ) );
        }
    }
}

std::vector<Position>& PositionArbitrator::GetPositionsToPlace( )
{
    m_positions.clear();
    if( m_board->GetPlacedNum() == 0 )
    {
        return m_positionsFor1stPlaced; 
    }
    else
    {
        const Position* placedTile = m_board->GetPlacedTiles();
        if( m_board->GetPlacedNum() == 1 )
        {
            AddEndsToResult( placedTile->m_row, placedTile->m_col, true );
            AddEndsToResult( placedTile->m_row, placedTile->m_col, false );
        }
        else if ( m_board->GetPlacedNum() > 1 && 
                  m_board->GetPlacedNum() < Board::MAX_TILES_TO_PLACE )
        {
            AddEndsToResult(placedTile[m_board->GetPlacedNum()-1].m_row,
                            placedTile[m_board->GetPlacedNum()-1].m_col,
                            m_board->IsVertical() );
        }
        else
            throw std::runtime_error( __FUNCTION__ "invalid placed num" );
    }
    return m_positions;
}

void PositionArbitrator::AddEndsToResult( int row, int col, bool isVertical )
{
    Board::Iterator begin( m_board );
    Board::Iterator end( m_board );
    m_board->GetLine(row, col, isVertical, begin, end );
    --begin;
    if( begin->type == Board::EMPTY )
        m_positions.push_back( begin.GetPosition() );
    if( end->type == Board::EMPTY )
        m_positions.push_back( end.GetPosition() );
}

