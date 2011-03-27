#include "ScoreRank.h"

#include <algorithm>


ScoreRank::ScoreRank( )
: m_heapFisrt   ( m_entitesHeap ),
  m_heapEnd     ( m_entitesHeap + MAX_RESULTS )
{
    for(int i =0; i < MAX_RESULTS +1 ; ++i)
    {
        m_entitesHeap[i].m_score         = 0;
        m_entitesHeap[i].m_placedTiles   = 0;
        m_entitesHeap[i].m_placedTiles   = m_placedTilesBuffer[i];
    }

    std::make_heap( m_heapFisrt, m_heapEnd, GreaterRank() );
}

void ScoreRank::Submit( int score, int stateSize, BoardPosInfo* boardState )
{
    //if input score is larger than the min of results
    if( score > m_entitesHeap[0].m_score )
    {
        std::pop_heap( m_heapFisrt, m_heapEnd + 1, GreaterRank() );

        m_heapEnd->m_score = score;
        m_heapEnd->m_numPlacedTiles = stateSize;
        std::memcpy( m_heapEnd->m_placedTiles, boardState, stateSize);
        
        std::push_heap( m_heapFisrt, m_heapEnd + 1, GreaterRank() );
    }
}

const std::vector<ScoreRank::RankEntity> ScoreRank::GetResults( )
{
    std::sort_heap( m_heapFisrt, m_heapEnd, GreaterRank() );
    return std::vector<RankEntity> (m_heapFisrt, m_heapEnd );
}