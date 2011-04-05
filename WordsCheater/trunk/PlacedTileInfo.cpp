#include "PlacedTileInfo.h"


PlacedTileInfo::PlacedTileInfo()
{
    int  m_row = -1;
    int  m_col = -1;
    char m_placedChar = 0;
}

PlacedTileInfo::PlacedTileInfo(int row, int col, int ch )
{
    int  m_row = row;
    int  m_col = col;
    char m_placedChar = ch;
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