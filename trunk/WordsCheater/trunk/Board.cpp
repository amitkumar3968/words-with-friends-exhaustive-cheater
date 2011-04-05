#include "Board.h"

#include "PlacedTileInfo.h"

#include <fstream>
#include <iostream>

namespace
{
    void ResetBoardState( int& size, Board::GridInfo grid[][MAX_RESULTS], Position* placedTilesPos )
    {
        size = 0;
        for(int i=0;i<MAX_RESULTS;++i)
        {
            for(int j=0;j<MAX_RESULTS;++j)
            {
                grid[i][j].type = Board::EMPTY;
                grid[i][j].ch   = 0;
            }
        }
    
        for(int i=0;i<MAX_TILES_TO_PLACE;++i)
        {
            placedTilesPos[i].m_row        = 0;
            placedTilesPos[i].m_col        = 0;
        }
    }
}

Board::Iterator::Iterator( )
: m_board       ( 0 ),
  m_row         ( -1 ),
  m_col         ( -1 ),
  m_isVertical  ( true )
{
}

Board::Iterator::Iterator( Board*  board, int row, int col, bool isVertical )
: m_board       ( board ),
  m_row         ( row ),
  m_col         ( col ),
  m_isVertical  ( isVertical )
{
}

bool Board::Iterator::operator==( const Iterator& rhs ) const
{
    return ( m_row        == rhs.m_row &&
             m_col        == rhs.m_col &&
             m_isVertical == rhs.m_isVertical );
}

bool Board::Iterator::operator!=( const Iterator& rhs ) const
{
    return !( *this == rhs );
}

Board::Iterator& Board::Iterator::operator++()
{
    if( m_row == -1 || m_col == -1 )
    {
        return *this;
    }

    if( m_isVertical )
        ++m_row;
    else
        ++m_col;

    if( m_row > MAX_RESULTS-1 || m_row > MAX_RESULTS-1 )
        SetBoundary();

    return *this;
}

Board::Iterator& Board::Iterator::operator--()
{
    if( m_row == -1 || m_col == -1 )
    {
        return *this;
    }

    if( m_isVertical )
        --m_row;
    else
        --m_col;

    if( m_row < 0 || m_row < 0 )
        SetBoundary();

    return *this;
}

const Board::GridInfo& Board::Iterator::operator*() const
{
    if( m_row < 0 || m_row > MAX_RESULTS-1 ||
        m_col < 0 || m_col > MAX_RESULTS-1 )
    {
        throw std::runtime_error( __FUNCTION__ "dereferencing invalid iterator" );
    }

    return m_board->m_grid[m_row][m_col];
}

const Board::GridInfo* Board::Iterator::operator->() const
{
    if( m_row < 0 || m_row > MAX_RESULTS-1 ||
        m_col < 0 || m_col > MAX_RESULTS-1 )
    {
        throw std::runtime_error( __FUNCTION__ "dereferencing invalid iterator" );
    }
    return &( m_board->m_grid[m_row][m_col] );
}


void Board::Iterator::SetBoundary()
{
    m_row = -1;
    m_col = -1;
    m_isVertical = true;
}


Board::Board()
: BOUNDARY      ( ),
  m_placedNum   ( 0 )
{
    ResetBoardState( m_placedNum, m_grid, m_placedTilesPos );
}


Board::~Board()
{
}

void Board::ResetFromFile( const std::string& filePath )
{
    ResetBoardState( m_placedNum, m_grid, m_placedTilesPos );

    std::ifstream file ( filePath.c_str(), std::ios_base::in);
    if( !file )
        throw std::invalid_argument( __FUNCTION__ "Load Board file error" );

    int numLine = 0;
    std::string line;
    while( getline( file, line, '\n' ) )
    {
        if( line.size() >= MAX_RESULTS )
        {
            if( numLine > MAX_RESULTS-1 )
                throw std::invalid_argument( __FUNCTION__ "parse file line error" );
        
            for(int i=0;i<MAX_RESULTS;++i)
            {
                GridType type;
                char ch;
                if( parseFileChar( line[i], type, ch ) )
                {
                    m_grid[numLine][i].type = type;
                    m_grid[numLine][i].ch   = ch;
                }
                else
                    throw std::invalid_argument( __FUNCTION__ "parse file char error" );
            }
            ++numLine;
        }
    }

}

bool Board::Place( int row, int col, char ch )
{
    return true;
}

bool Board::Undo()
{
    return true;
}

const Position* Board::GetPlacedTiles() const
{
    return m_placedTilesPos;
}

int Board::GetPlacedNum() const
{
    return 0;
}

bool Board::GetEnds( int row, int col, bool isVertical, 
                     Iterator front, Iterator back )
{
    return true;
}

bool Board::GetLine( int row, int col, bool isVertical, 
                     Iterator begin, Iterator end )
{
    return true; 
}

void Board::printToStream( std::ostream& stream, PlacedTileInfo* placedTile, int placedSize ) const
{
    //place all placed tile first
    if( placedSize > MAX_TILES_TO_PLACE)
        throw std::runtime_error( __FUNCTION__ "placedSize larger than expected" );

    char placedBoard[MAX_RESULTS][MAX_RESULTS];
    for(int i=0;i<MAX_RESULTS;++i)
    {
        for(int j=0;j<MAX_RESULTS;++j)
        {
            placedBoard[i][j] = 0;
        }
    }
    for(int i=0;i<placedSize;++i)
        placedBoard[placedTile->m_row][placedTile->m_col] = placedTile->m_placedChar;

    //print to stream
    for(int i=0;i<MAX_RESULTS;++i)
    {
        for(int j=0;j<MAX_RESULTS;++j)
        {
            if( placedBoard[i][j] != 0 )
            {
                stream << placedBoard[i][j] << " ";
                if( m_grid[i][j].type != Board::EMPTY )
                    throw std::runtime_error( __FUNCTION__ "must be empty for placed tile" );
            }
            else if( m_grid[i][j].type == Board::ORIGINAL  )
            {
                stream << m_grid[i][j].ch << " ";
            }
            else if( m_grid[i][j].type == Board::EMPTY )
            {
                if( i == MAX_RESULTS/2 && j == 0 ||
                    i == 0 && j == MAX_RESULTS/2  ||
                    i == MAX_RESULTS/2 && j == MAX_RESULTS-1  ||
                    i == MAX_RESULTS-1 && j == MAX_RESULTS/2 )
                    stream << '+' << " ";
                else
                    stream << '-' << " ";
            }
            else
                throw std::runtime_error( __FUNCTION__ "unexpected grid type" );
        }
        stream << std::endl;
    }
}

bool Board::parseFileChar( const char fileChar, GridType& type, char& ch ) const
{
    if( fileChar == '-' || fileChar == '+' )
    {
        type = Board::EMPTY;
        ch = 0;
        return true;
    }
    else if( fileChar >= 'a' || fileChar <='z' )
    {
        type = Board::PLACED;
        ch = fileChar;
        return true;
    }
    else if( fileChar >= 'A' || fileChar <= 'Z' )
    {
        int diff = 'a' - 'A';
        type = Board::PLACED;
        //convert to lower case
        ch = fileChar + diff;
        return true;
    }
    return false;
}