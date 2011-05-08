#ifndef BOARD_H
#define BOARD_H

namespace
{
    const int CASE_DIFF = 'a' - 'A';
}

#include "Position.h"
#include "PlacedTileInfo.h"

#include <string>
#include <vector>

struct PlacedTileInfo;

class Board
{
public:

    enum GridType
    {
        EMPTY,
        ORIGINAL,
        PLACED,
        INVALID
    };
    struct GridInfo
    {
        GridType type;
        char     ch;
    };

    class Iterator
    {
    public:
        explicit Iterator( Board*  board );
        explicit Iterator( Board*  board, int row, int col, bool isVertical );
        void Reset( int row, int col, bool isVertical  );
        bool operator==( const Iterator& rhs ) const;
        bool operator!=( const Iterator& rhs ) const;
        Iterator& operator++();
        Iterator& operator--();
        const GridInfo& operator*() const;
        const GridInfo* operator->() const;
        const Position GetPosition() const;
    private:
        Board*  m_board;
        int     m_row;
        int     m_col;
        bool    m_isVertical;
    };

public:
    static const int MAX_GRID           = 15;
    static const int MAX_TILES_TO_PLACE = 7;

public:
    Board();
    virtual ~Board();

public:
    void Reset();
    void Reset( const Board& board );
    void ResetFromFile( const std::string& filePath );
    bool Place( int row, int col, char ch );
    bool Undo();
    const Position* GetPlacedTiles() const;
    const PlacedTileInfo* GetPlacedTilesInfo();
    int GetPlacedNum() const;
    bool IsVertical( );
    bool GetEnds( int row, int col, bool isVertical, 
                  Iterator& front, Iterator& back );
    bool GetLine( int row, int col, bool isVertical, 
                  Iterator& begin, Iterator& end );
    void GetMarkedNeighbour( bool markedGrid[][MAX_GRID] );
    void printToStream( std::ostream& stream, PlacedTileInfo* placedTile, int placedSize ) const;
    bool ParseFileBoard( std::ifstream& file, std::vector<PlacedTileInfo>& placedTiles );

private:
    bool ParseFileChar( const char fileChar, GridType& type, char& ch, bool& isPlacedTiles ) const;

private:
    int               m_placedNum;
    GridInfo          m_grid[MAX_GRID][MAX_GRID];
    Position          m_placedTilesPos[MAX_TILES_TO_PLACE];
    PlacedTileInfo    m_placedTilesInfo[MAX_TILES_TO_PLACE];
    GridInfo          m_invalidGrid;
    bool              m_isVertical;
};
#endif
