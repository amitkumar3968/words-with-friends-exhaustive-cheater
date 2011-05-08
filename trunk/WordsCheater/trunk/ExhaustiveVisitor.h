#ifndef EXHAUSTIVEVISITOR_H
#define EXHAUSTIVEVISITOR_H

#include "Board.h"
#include "PlacedTileInfo.h"
#include "TrieDictionary.h"
#include "PositionArbitrator.h"
#include "ScoreCalculator.h"

class ScoreRank;

class ExhaustiveVisitor
{
public:
    explicit ExhaustiveVisitor( ScoreRank* scoreRank, std::string dictPath );
    virtual ~ExhaustiveVisitor( );

    void Initialize( const Board board, const char* tilesToPlace );
    void RankExhaustively( );

private:
    Board               m_board;
    char                m_tilesToPlace[Board::MAX_TILES_TO_PLACE];
    PlacedTileInfo      m_placedTileInfo[Board::MAX_TILES_TO_PLACE];
    TrieDictionary      m_dict;
    PositionArbitrator  m_placingPos;
    ScoreCalculator     m_scoreCal;


    ScoreRank*          m_scoreRank;
};

#endif