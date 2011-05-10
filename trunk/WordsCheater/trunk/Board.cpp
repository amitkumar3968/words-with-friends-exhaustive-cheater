#include "Board.h"

#include <fstream>
#include <iostream>

namespace
{
    void ResetBoardState( Board::GridInfo grid[][Board::MAX_GRID], Position* placedTilesPos, int& m_placedNum )
    {
        for(int i=0;i<Board::MAX_GRID;++i)
        {
            for(int j=0;j<Board::MAX_GRID;++j)
            {
                grid[i][j].type = Board::EMPTY;
                grid[i][j].ch   = 0;
            }
        }
    
        for(int i=0;i<Board::MAX_TILES_TO_PLACE;++i)
        {
            placedTilesPos[i].m_row        = 0;
            placedTilesPos[i].m_col        = 0;
        }
        m_placedNum = 0;
    }

    void MarkTrue( bool grid[][Board::MAX_GRID], int row, int col )
    {
            if (row < 0 || row > Board::MAX_GRID-1 ||
                col < 0 || col > Board::MAX_GRID-1 )
                return;

            grid[row][col] = true;
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
    if( m_row < 0 || m_row > MAX_GRID-1 ||
        m_col < 0 || m_col > MAX_GRID-1 )
        return m_board->m_invalidGrid;

    return m_board->m_grid[m_row][m_col];
}

const Board::GridInfo* Board::Iterator::operator->() const
{
    if( m_row < 0 || m_row > MAX_GRID-1 ||
        m_col < 0 || m_col > MAX_GRID-1 )
        return &m_board->m_invalidGrid;

    return &( m_board->m_grid[m_row][m_col] );
}

const Position  Board::Iterator::GetPosition() const
{
    return Position( m_row, m_col );
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

void Board::Reset( )
{
    ResetBoardState( m_grid, m_placedTilesPos, m_placedNum );
}

void Board::Reset( const Board& board )
{
    ResetBoardState( m_grid, m_placedTilesPos, m_placedNum );
    for(int i=0;i<Board::MAX_GRID;++i)
    {
        for(int j=0;j<Board::MAX_GRID;++j)
        {
            m_grid[i][j].type = board.m_grid[i][j].type;
            m_grid[i][j].ch   = board.m_grid[i][j].ch;
        }
    }

}


void Board::ResetFromFile( const std::string& filePath )
{
    ResetBoardState( m_grid, m_placedTilesPos, m_placedNum );

    std::ifstream file ( filePath.c_str(), std::ios_base::in );
    if( !file )
        throw std::invalid_argument( __FUNCTION__ "Load Board file error" );

    ParseFileBoard( file, std::vector<PlacedTileInfo>() );
}

bool Board::Place( int row, int col, char ch )
{
    if( m_grid[row][col].type != Board::EMPTY ||
        m_placedNum < 0 ||
        m_placedNum > 7 )
        return false;

    if( m_placedNum == 1 )
    {
        if( m_placedTilesPos[0].m_row == row )
            m_isVertical = false;
        else if ( m_placedTilesPos[0].m_col == col )
            m_isVertical = true;
        else
            return false;
    }

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

const PlacedTileInfo* Board::GetPlacedTilesInfo()
{
    for( int i=0; i<GetPlacedNum( ); ++i )
    {
        m_placedTilesInfo[i].m_row = m_placedTilesPos[i].m_row;
        m_placedTilesInfo[i].m_col = m_placedTilesPos[i].m_col;
        m_placedTilesInfo[i].m_placedChar = m_grid[m_placedTilesPos[i].m_row][m_placedTilesPos[i].m_col].ch;
    }
    return m_placedTilesInfo;
}

int Board::GetPlacedNum() const
{
    return m_placedNum;
}

bool Board::IsVertical( )
{
    return m_isVertical;
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

void Board::GetMarkedNeighbour( bool grid[][MAX_GRID] )
{
    for(int i=0;i<MAX_GRID;++i)
    {
        for(int j=0;j<MAX_GRID;++j)
        {
            grid[i][j] = false;
        }
    }

    for(int i=0;i<MAX_GRID;++i)
    {
        for(int j=0;j<MAX_GRID;++j)
        {
            if( m_grid[i][j].type == ORIGINAL )
            {
                MarkTrue( grid ,i ,j-1 );
                MarkTrue( grid ,i ,j+1 );
                MarkTrue( grid ,i-1 ,j );
                MarkTrue( grid ,i+1 ,j );
            }
            else if( m_grid[i][j].type != EMPTY )
                throw std::runtime_error( __FUNCTION__ "grid must be ORIGIN/EMPTY" );
        }
    }

    for(int i=0;i<MAX_GRID;++i)
    {
        for(int j=0;j<MAX_GRID;++j)
        {
            if( m_grid[i][j].type == ORIGINAL )
            {
                grid[i][j] = false;
            }
            else if( m_grid[i][j].type != EMPTY )
                throw std::runtime_error( __FUNCTION__ "grid must be ORIGIN/EMPTY" );
        }
    }
}

void Board::printToStream( std::ostream& stream, PlacedTileInfo* placedTile, int placedSize ) const
{
    //place all placed tile first
    if( placedSize < 0 || placedSize > MAX_TILES_TO_PLACE )
        throw std::runtime_error( __FUNCTION__ " invalid placedSize" );

    char placedBoard[MAX_GRID][MAX_GRID];
    for(int i=0;i<MAX_GRID;++i)
    {
        for(int j=0;j<MAX_GRID;++j)
        {
            placedBoard[i][j] = 0;
        }
    }
    for(int i=0;i<placedSize;++i)
        placedBoard[placedTile[i].m_row][placedTile[i].m_col] = placedTile[i].m_placedChar;

    //print to stream
    for(int i=0;i<MAX_GRID;++i)
    {
        for(int j=0;j<MAX_GRID;++j)
        {
            if( placedBoard[i][j] != 0 )
            {    
                //convert to upper case
                stream << static_cast<char>( placedBoard[i][j] - CASE_DIFF ) << " ";
                if( m_grid[i][j].type != Board::EMPTY )
                    throw std::runtime_error( __FUNCTION__ "must be empty for placed tile" );
            }
            else if( m_grid[i][j].type == Board::ORIGINAL  )
            {
                stream << m_grid[i][j].ch << " " ;
            }
            else if( m_grid[i][j].type == Board::EMPTY )
            {
                if( i == MAX_GRID/2 && j == 0 ||
                    i == 0 && j == MAX_GRID/2  ||
                    i == MAX_GRID/2 && j == MAX_GRID-1  ||
                    i == MAX_GRID-1 && j == MAX_GRID/2 )
                    stream << '+' << " ";
                else
                    stream << '-' << " ";
            }
            else if( m_grid[i][j].type == Board::PLACED && placedSize  == 0 )
            {
                //covert to upper case
                stream << static_cast<char> ( m_grid[i][j].ch - CASE_DIFF ) << " " ;            
            }
            else
                throw std::runtime_error( __FUNCTION__ "unexpected grid type" );
        }
        stream << std::endl ;
    }
    stream << std::endl;
}

bool Board::ParseFileBoard( std::ifstream& file, std::vector<PlacedTileInfo>& placedTiles  )
{
    std::string line;
    std::vector<char> placedTile;
    int numLine = 0;
    while( numLine<MAX_GRID && getline( file, line, '\n' ))
    {

        if( line.size() == MAX_GRID )
        {
            for(int i=0;i<MAX_GRID;++i)
            {
                GridType type;
                char ch;
                bool isPlacedTiles;
                if( ParseFileChar( line[i], type, ch, isPlacedTiles ) )
                {
                    m_grid[numLine][i].type = type;
                    m_grid[numLine][i].ch   = ch;
                    if( isPlacedTiles )
                        placedTiles.push_back( PlacedTileInfo( numLine, i, static_cast<char>( line[i] + CASE_DIFF ) ) );
                }
                else
                    throw std::invalid_argument( __FUNCTION__ " parse file char error" );
            }
            ++numLine;
        }
        else
            throw std::invalid_argument( __FUNCTION__ " parse line error" );
    }

    return numLine == MAX_GRID;
}

bool Board::ParseFileChar( const char fileChar, GridType& type, char& ch, bool& isPlacedTiles ) const
{
    isPlacedTiles = false;
    if( fileChar == '-' || fileChar == '+' )
    {
        type = Board::EMPTY;
        ch = 0;
        return true;
    }
    else if( fileChar >= 'A' && fileChar <= 'Z' )
    {
        type = Board::EMPTY;
        ch = 0;
        isPlacedTiles = true;
        return true;
    }
    else if( fileChar >= 'a' && fileChar <='z' )
    {
        type = Board::ORIGINAL;
        ch = fileChar;
        return true;
    }

    return false;
}