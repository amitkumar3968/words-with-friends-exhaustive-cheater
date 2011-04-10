#include "Board.h"

#include "PlacedTileInfo.h"

#include <fstream>
#include <iostream>

namespace
{
    void ResetBoardState( Board::GridInfo grid[][MAX_RESULTS], Position* placedTilesPos, int& m_placedNum )
    {
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
        m_placedNum = 0;
    }
}

Board::Iterator::Iterator( Board*  board )
: m_board       ( board ),
  m_row         ( -1 ),
  m_col         ( -1 ),
  m_isVertical  ( true )
{
    if( !m_board )
        throw std::invalid_argument( __FUNCTION__ "pointer board cannot be null" );
}

Board::Iterator::Iterator( Board*  board, int row, int col, bool isVertical )
: m_board       ( board ),
  m_row         ( row ),
  m_col         ( col ),
  m_isVertical  ( isVertical )
{
    if( !m_board )
        throw std::invalid_argument( __FUNCTION__ "pointer board cannot be null" );
}

void Board::Iterator::Reset( int row, int col, bool isVertical  )
{
    m_row = row;
    m_col = col;
    m_isVertical = isVertical;
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
    if( m_isVertical )
        ++m_row;
    else
        ++m_col;

    return *this;
}

Board::Iterator& Board::Iterator::operator--()
{
    if( m_isVertical )
        --m_row;
    else
        --m_col;

    return *this;
}

const Board::GridInfo& Board::Iterator::operator*() const
{
    if( m_row < 0 || m_row > MAX_RESULTS-1 ||
        m_col < 0 || m_col > MAX_RESULTS-1 )
        return m_board->m_invalidGrid;

    return m_board->m_grid[m_row][m_col];
}

const Board::GridInfo* Board::Iterator::operator->() const
{
    if( m_row < 0 || m_row > MAX_RESULTS-1 ||
        m_col < 0 || m_col > MAX_RESULTS-1 )
        return &m_board->m_invalidGrid;

    return &( m_board->m_grid[m_row][m_col] );
}

Board::Board()
: m_invalidGrid ()
{
    m_invalidGrid.type = INVALID;
    m_invalidGrid.ch = 0;

    ResetBoardState( m_grid, m_placedTilesPos, m_placedNum );
}


Board::~Board()
{
}

void Board::ResetFromFile( const std::string& filePath )
{
    ResetBoardState( m_grid, m_placedTilesPos, m_placedNum );

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
    if( m_grid[row][col].type != Board::EMPTY ||
        m_placedNum < 0 ||
        m_placedNum > 7 )
        return false;

    m_placedTilesPos[m_placedNum].m_row = row;
    m_placedTilesPos[m_placedNum].m_col = col;

    m_grid[row][col].type = Board::PLACED;
    m_grid[row][col].ch = ch;

    ++m_placedNum;

    return true;
}

bool Board::Undo()
{
    if( m_placedNum <= 0 )
        return false;

    int row = m_placedTilesPos[m_placedNum-1].m_row;
    int col = m_placedTilesPos[m_placedNum-1].m_col;
    m_grid[row][col].type = Board::EMPTY;

    --m_placedNum;
    return true;
}

const Position* Board::GetPlacedTiles() const
{
    return m_placedTilesPos;
}

int Board::GetPlacedNum() const
{
    return m_placedNum;
}

bool Board::GetEnds( int row, int col, bool isVertical, 
                     Iterator& front, Iterator& back )
{
    if( !GetLine( row, col, isVertical, front, back ) )
        return false;
    --back;
    return true;
}

bool Board::GetLine( int row, int col, bool isVertical, 
                     Iterator& begin, Iterator& end )
{
    begin.Reset( row, col, isVertical );
    if(  begin->type != ORIGINAL && begin->type != PLACED )
        return false;

    while( begin->type == ORIGINAL || begin->type == PLACED )
        --begin;

    ++begin;

    end.Reset( row, col, isVertical );
    while( end->type == ORIGINAL || end->type == PLACED )
        ++end;

    return true;
}

void Board::printToStream( std::ostream& stream, PlacedTileInfo* placedTile, int placedSize ) const
{
    //place all placed tile first
    if( placedSize < 0 || placedSize > MAX_TILES_TO_PLACE-1 )
        throw std::runtime_error( __FUNCTION__ "invalid placedSize" );

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
                //convert to upper case
                stream << placedBoard[i][j] - CASE_DIFF << " ";
                if( m_grid[i][j].type != Board::EMPTY )
                    throw std::runtime_error( __FUNCTION__ "must be empty for placed tile" );
            }
            else if( m_grid[i][j].type == Board::ORIGINAL  )
            {
                //convert to upper case
                stream << static_cast<char> ( m_grid[i][j].ch - CASE_DIFF ) << " " ;
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
        stream << std::endl ;
    }
    stream << std::endl;
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
        type = Board::ORIGINAL;
        ch = fileChar;
        return true;
    }
    else if( fileChar >= 'A' || fileChar <= 'Z' )
    {
        type = Board::ORIGINAL;
        //convert to lower case
        ch = fileChar + CASE_DIFF;
        return true;
    }
    return false;
}