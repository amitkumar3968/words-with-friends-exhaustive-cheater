#ifndef POSITIONARBITRATOR_H
#define POSITIONARBITRATOR_H

#include "Position.h"

#include <vector>

class Board;

class PositionArbitrator
{
public:
    explicit PositionArbitrator( Board* board );
    virtual ~PositionArbitrator( );

    void Reset( );
    std::vector<Position>& GetPositionsToPlace( );

private:
    void AddEndsToResult( int row, int col, bool isVertical );

private:
    Board*                  m_board;
    std::vector<Position>   m_positionsFor1stPlaced;
    std::vector<Position>   m_positions;
};

#endif