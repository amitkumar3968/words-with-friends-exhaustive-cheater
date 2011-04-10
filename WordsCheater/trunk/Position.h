#ifndef POSITION_H
#define POSITION_H

struct Position
{
    explicit Position( );
    explicit Position( int row, int col );
    

    bool operator==( const Position& rhs ) const;
    bool operator!=( const Position& rhs ) const;

    int  m_row;
    int  m_col;
};

#endif