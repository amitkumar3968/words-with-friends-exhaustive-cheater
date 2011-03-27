#include "TestHarness.h"
#include "ScoreRank.h"
#include "PlacedTileInfo.h"

TEST( ScoreRank, Submit )
{
    ScoreRank subject;

    int          score[30];
    int          placedSize[30];

    score[0]   = 35; placedSize[0]   = 0;
    score[1]   = 11; placedSize[1]   = score[1]  %7 + 1;
    score[2]   = 0 ; placedSize[2]   = score[2]  %7 + 1;
    score[3]   = 16; placedSize[3]   = score[3]  %7 + 1;
    score[4]   = 12; placedSize[4]   = score[4]  %7 + 1;
    score[5]   = 1 ; placedSize[5]   = score[5]  %7 + 1;
    score[6]   = 6 ; placedSize[6]   = score[6]  %7 + 1;
    score[7]   = 18; placedSize[7]   = score[7]  %7 + 1;
    score[8]   = 35; placedSize[8]   = 8;
    score[9]   = 35; placedSize[9]   = 9;
    score[10]  = 35; placedSize[10]  = 0;
    score[11]  = 10; placedSize[11]  = score[11] %7 + 1;
    score[12]  = 9 ; placedSize[12]  = score[12] %7 + 1;
    score[13]  = 5 ; placedSize[13]  = score[13] %7 + 1;
    score[14]  = 14; placedSize[14]  = score[14] %7 + 1;
    score[15]  = 2 ; placedSize[15]  = score[15] %7 + 1;
    score[16]  = 13; placedSize[16]  = score[16] %7 + 1;
    score[17]  = 4 ; placedSize[17]  = score[17] %7 + 1;
    score[18]  = 35; placedSize[18]  = 8;
    score[19]  = 35; placedSize[19]  = 9;
    score[20]  = 35; placedSize[20]  = 0;
    score[21]  = 17; placedSize[21]  = score[21] %7 + 1;
    score[22]  = 0 ; placedSize[22]  = score[22] %7 + 1;
    score[23]  = 3 ; placedSize[23]  = score[23] %7 + 1;
    score[24]  = 7 ; placedSize[24]  = score[24] %7 + 1;
    score[25]  = 8 ; placedSize[25]  = score[25] %7 + 1;
    score[26]  = 0 ; placedSize[26]  = score[26] %7 + 1;
    score[27]  = 15; placedSize[27]  = score[27] %7 + 1;
    score[28]  = 35; placedSize[28]  = 8;
    score[29]  = 35; placedSize[29]  = 9;

    PlacedTileInfo placedTiles[8];
    for(int i = 0; i< 8; ++i )
    {
        placedTiles[i].m_row = 2*i + i;
        placedTiles[i].m_col = 2*i + i;
        placedTiles[i].m_placedChar = 'a' +  2*i + i;
    }

    for(int i =0; i<30; ++i)
        subject.Submit( score[i], placedSize[i], placedTiles );

    std::vector<ScoreRank::RankEntity>::const_iterator begin;
    std::vector<ScoreRank::RankEntity>::const_iterator end;
    subject.GetResults( begin, end );

    int expScore = 18;

    for( std::vector<ScoreRank::RankEntity>::const_iterator itr = begin;
         itr != end;
         ++itr )
    {
        CHECK( itr->m_score == expScore );
        CHECK( itr->m_numPlacedTiles == itr->m_score % 7 + 1);
        CHECK( std::memcmp( itr->m_placedTiles, placedTiles, (itr->m_numPlacedTiles) * sizeof(ScoreRank::RankEntity) ) == 0 );
        --expScore;
    }
}

TEST( ScoreRank, Submit_with_few_results )
{
    ScoreRank subject;

    int          score[30];
    int          placedSize[30];

    score[0]   = 35; placedSize[0]   = 0;
    score[1]   = 11; placedSize[1]   = score[1]  %7 + 1;
    score[2]   = 0 ; placedSize[2]   = 0;
    score[3]   = 16; placedSize[3]   = score[3]  %7 + 1;
    score[4]   = 12; placedSize[4]   = score[4]  %7 + 1;
    score[5]   = 1 ; placedSize[5]   = 0;
    score[6]   = 6 ; placedSize[6]   = 0;
    score[7]   = 18; placedSize[7]   = score[7]  %7 + 1;
    score[8]   = 35; placedSize[8]   = 8;
    score[9]   = 35; placedSize[9]   = 9;
    score[10]  = 35; placedSize[10]  = 0;
    score[11]  = 10; placedSize[11]  = score[11] %7 + 1;
    score[12]  = 9 ; placedSize[12]  = score[12] %7 + 1;
    score[13]  = 5 ; placedSize[13]  = 0;
    score[14]  = 14; placedSize[14]  = score[14] %7 + 1;
    score[15]  = 2 ; placedSize[15]  = 0;
    score[16]  = 13; placedSize[16]  = score[16] %7 + 1;
    score[17]  = 4 ; placedSize[17]  = 0;
    score[18]  = 35; placedSize[18]  = 8;
    score[19]  = 35; placedSize[19]  = 9;
    score[20]  = 35; placedSize[20]  = 0;
    score[21]  = 17; placedSize[21]  = score[21] %7 + 1;
    score[22]  = 0 ; placedSize[22]  = 0;
    score[23]  = 3 ; placedSize[23]  = 0;
    score[24]  = 7 ; placedSize[24]  = 0;
    score[25]  = 8 ; placedSize[25]  = 0;
    score[26]  = 0 ; placedSize[26]  = 0;
    score[27]  = 15; placedSize[27]  = score[27] %7 + 1;
    score[28]  = 35; placedSize[28]  = 8;
    score[29]  = 35; placedSize[29]  = 9;

    PlacedTileInfo placedTiles[8];
    for(int i = 0; i< 8; ++i )
    {
        placedTiles[i].m_row = 2*i + i;
        placedTiles[i].m_col = 2*i + i;
        placedTiles[i].m_placedChar = 'a' +  2*i + i;
    }

    for(int i =0; i<30; ++i)
        subject.Submit( score[i], placedSize[i], placedTiles );

    std::vector<ScoreRank::RankEntity>::const_iterator begin;
    std::vector<ScoreRank::RankEntity>::const_iterator end;
    subject.GetResults( begin, end );

    int expScore = 18;

    for( std::vector<ScoreRank::RankEntity>::const_iterator itr = begin;
         itr != end;
         ++itr )
    {
        CHECK( itr->m_score == expScore );
        CHECK( itr->m_numPlacedTiles == itr->m_score % 7 + 1);
        CHECK( std::memcmp( itr->m_placedTiles, placedTiles, (itr->m_numPlacedTiles) * sizeof(ScoreRank::RankEntity) ) == 0 );
        --expScore;
    }
}



TEST( ScoreRank, Reset )
{
    ScoreRank subject;

    int          score[30];
    int          placedSize[30];

    score[0]   = 35; placedSize[0]   = 0;
    score[1]   = 11; placedSize[1]   = score[1]  %7 + 1;
    score[2]   = 0 ; placedSize[2]   = score[2]  %7 + 1;
    score[3]   = 16; placedSize[3]   = score[3]  %7 + 1;
    score[4]   = 12; placedSize[4]   = score[4]  %7 + 1;
    score[5]   = 1 ; placedSize[5]   = score[5]  %7 + 1;
    score[6]   = 6 ; placedSize[6]   = score[6]  %7 + 1;
    score[7]   = 18; placedSize[7]   = score[7]  %7 + 1;
    score[8]   = 35; placedSize[8]   = 8;
    score[9]   = 35; placedSize[9]   = 9;
    score[10]  = 35; placedSize[10]  = 0;
    score[11]  = 10; placedSize[11]  = score[11] %7 + 1;
    score[12]  = 9 ; placedSize[12]  = score[12] %7 + 1;
    score[13]  = 5 ; placedSize[13]  = score[13] %7 + 1;
    score[14]  = 14; placedSize[14]  = score[14] %7 + 1;
    score[15]  = 2 ; placedSize[15]  = score[15] %7 + 1;
    score[16]  = 13; placedSize[16]  = score[16] %7 + 1;
    score[17]  = 4 ; placedSize[17]  = score[17] %7 + 1;
    score[18]  = 35; placedSize[18]  = 8;
    score[19]  = 35; placedSize[19]  = 9;
    score[20]  = 35; placedSize[20]  = 0;
    score[21]  = 17; placedSize[21]  = score[21] %7 + 1;
    score[22]  = 0 ; placedSize[22]  = score[22] %7 + 1;
    score[23]  = 3 ; placedSize[23]  = score[23] %7 + 1;
    score[24]  = 7 ; placedSize[24]  = score[24] %7 + 1;
    score[25]  = 8 ; placedSize[25]  = score[25] %7 + 1;
    score[26]  = 0 ; placedSize[26]  = score[26] %7 + 1;
    score[27]  = 15; placedSize[27]  = score[27] %7 + 1;
    score[28]  = 35; placedSize[28]  = 8;
    score[29]  = 35; placedSize[29]  = 9;

    PlacedTileInfo placedTiles[8];
    for(int i = 0; i< 8; ++i )
    {
        placedTiles[i].m_row = 2*i + i;
        placedTiles[i].m_col = 2*i + i;
        placedTiles[i].m_placedChar = 'a' +  2*i + i;
    }

    for(int i =0; i<30; ++i)
        subject.Submit( score[i], placedSize[i], placedTiles );

    subject.Reset();
    std::vector<ScoreRank::RankEntity>::const_iterator begin;
    std::vector<ScoreRank::RankEntity>::const_iterator end;
    subject.GetResults( begin, end );

    CHECK( begin == end );
}