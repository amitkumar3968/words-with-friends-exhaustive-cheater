#ifndef SCORERANK_H
#define SCORERANK_H

namespace
{
    const int RANKER_CAPACITY    = 1000;
    const int MAX_GRID           = 15;
    const int MAX_TILES_TO_PLACE = 7;
}

#include"PlacedTileInfo.h"
#include <vector>
#include <string>

class ScoreRank
{
public:
    struct RankEntity
    {
        int              m_score;
        int              m_numPlacedTiles;
        PlacedTileInfo*  m_placedTiles;
    };
private:
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
                 const PlacedTileInfo* placedTiles );

    void GetResults( std::vector<RankEntity>::const_iterator& begin,
                     std::vector<RankEntity>::const_iterator& end );

    void Reset();

private:
    PlacedTileInfo           m_placedTilesBuffer[RANKER_CAPACITY][MAX_TILES_TO_PLACE];
    RankEntity               m_entitesHeap[RANKER_CAPACITY];
    std::vector<RankEntity>  m_results;
    RankEntity* const        m_heapFisrt;
    RankEntity* const        m_heapLast;
    RankEntity* const        m_heapEnd;

//stat
public:
    int     s_submitCount;
    int     s_recordedCount;

    void ResetStat();
};




#endif