#ifndef PLACEDTILEINFO_H
#define PLACEDTILEINFO_H

struct PlacedTileInfo
{
    explicit PlacedTileInfo( );
    explicit PlacedTileInfo( int row, int col, int ch );

    bool operator==( const PlacedTileInfo& rhs ) const;
    bool operator!=( const PlacedTileInfo& rhs ) const;

    int  m_row;
    int  m_col;
    char m_placedChar;
};

#endif