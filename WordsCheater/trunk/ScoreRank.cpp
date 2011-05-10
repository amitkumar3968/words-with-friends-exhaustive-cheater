#include "ScoreRank.h"

#include <algorithm>

ScoreRank::ScoreRank( )
: m_heapFisrt   ( m_entitesHeap ),
  m_heapLast    ( m_entitesHeap + RANKER_CAPACITY -1 ),
  m_heapEnd     ( m_entitesHeap + RANKER_CAPACITY ),
  s_submitCount( 0 ),
  s_recordedCount( 0 )
{
    for(int i =0; i < RANKER_CAPACITY ; ++i)
    {
        m_entitesHeap[i].m_score           = 0;
        m_entitesHeap[i].m_numPlacedTiles  = 0;
        for(int j=0; j<MAX_TILES_TO_PLACE; ++j)
        {
            m_placedTilesBuffer[i][j].m_row         = -1;
            m_placedTilesBuffer[i][j].m_col         = -1;
            m_placedTilesBuffer[i][j].m_placedChar  = 0;
        }
        m_entitesHeap[i].m_placedTiles = m_placedTilesBuffer[i];
    }

    m_results.reserve( RANKER_CAPACITY );
    m_results.clear();

    std::make_heap( m_heapFisrt, m_heapEnd, GreaterRank() );
}

void ScoreRank::Submit( int score, int stateSize, const PlacedTileInfo* placedTiles )
{
    ++s_submitCount;
    //if input score is larger than the min of results
    if( stateSize > 0 &&
        stateSize <= MAX_TILES_TO_PLACE && 
        score > m_entitesHeap[0].m_score )
    {
        ++s_recordedCount;
        std::pop_heap( m_heapFisrt, m_heapEnd, GreaterRank() );

        m_heapLast->m_score = score;
        m_heapLast->m_numPlacedTiles = stateSize;
        std::memcpy( m_heapLast->m_placedTiles,
                     placedTiles,
                     stateSize * sizeof(ScoreRank::RankEntity) );
        
        std::push_heap( m_heapFisrt, m_heapEnd, GreaterRank() );
    }
}

void ScoreRank::GetResults( std::vector<RankEntity>::const_iterator& begin,
                            std::vector<RankEntity>::const_iterator& end)
{
    std::sort_heap( m_heapFisrt, m_heapEnd, GreaterRank() );
    const RankEntity* itr = m_heapFisrt;
    while( itr->m_score > 0 &&
           itr->m_placedTiles > 0 &&
           itr != m_heapEnd )
    {
        m_results.push_back( *itr );
        ++itr;
    }
    begin = m_results.begin();
    end   = m_results.end();
}

void ScoreRank::Reset()
{
    for(int i =0; i < RANKER_CAPACITY ; ++i)
    {
        m_entitesHeap[i].m_score           = 0;
        m_entitesHeap[i].m_numPlacedTiles  = 0;
        for(int j=0; j<MAX_TILES_TO_PLACE; ++j)
        {
            m_placedTilesBuffer[i][j].m_row         = -1;
            m_placedTilesBuffer[i][j].m_col         = -1;
            m_placedTilesBuffer[i][j].m_placedChar  = 0;
        }
        m_entitesHeap[i].m_placedTiles = m_placedTilesBuffer[i];
    }
    m_results.clear();

    std::make_heap( m_heapFisrt, m_heapEnd, GreaterRank() );
}

void ScoreRank::ResetStat()
{
    s_submitCount = 0;
    s_recordedCount = 0;
}