#include "PlacedTileInfo.h"


PlacedTileInfo::PlacedTileInfo()
{
    m_row = -1;
    m_col = -1;
    m_placedChar = 0;
}

PlacedTileInfo::PlacedTileInfo(int row, int col, int ch )
{
    m_row = row;
    m_col = col;
    m_placedChar = ch;
}

bool PlacedTileInfo::operator==( const PlacedTileInfo& rhs ) const
{
    return ( m_row == rhs.m_row &&
             m_col == rhs.m_col &&
             m_placedChar == rhs.m_placedChar );
}

bool PlacedTileInfo::operator!=( const PlacedTileInfo& rhs ) const
{
    return !( *this == rhs );
}