#include "Position.h"


Position::Position()
{
    int  m_row = -1;
    int  m_col = -1;
}

Position::Position(int row, int col )
{
    int  m_row = row;
    int  m_col = col;
}

bool Position::operator==( const Position& rhs ) const
{
    return ( m_row == rhs.m_row &&
             m_col == rhs.m_col );
}

bool Position::operator!=( const Position& rhs ) const
{
    return !( *this == rhs );
}