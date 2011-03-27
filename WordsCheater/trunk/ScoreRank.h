#ifndef SCORERANK_H
#define SCORERANK_H

namespace
{
    const int MAX_RESULTS        = 15;
    const int MAX_TILES_TO_PLACE = 7;
}

#include"BoardPosInfo.h"
#include <vector>
#include <string>

class ScoreRank
{
private:
    struct RankEntity
    {
        int           m_score;
        int           m_numPlacedTiles;
        BoardPosInfo* m_placedTiles;
    };
    struct GreaterRank
    {
        bool operator() ( const RankEntity& lhs, const RankEntity& rhs )
        {
            return lhs.m_score > rhs.m_score;
        }
    };
public:
    explicit ScoreRank( );

    void Submit( int score,
                 int stateSize,
                 BoardPosInfo* boardState );

    const std::vector<RankEntity> ScoreRank::GetResults();

private:
    BoardPosInfo        m_placedTilesBuffer[MAX_RESULTS][MAX_TILES_TO_PLACE];
    RankEntity          m_entitesHeap[MAX_RESULTS+1];
    RankEntity* const   m_heapFisrt;
    RankEntity* const   m_heapEnd;
};




#endif