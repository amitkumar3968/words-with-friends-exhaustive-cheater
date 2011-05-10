#ifndef MOVEOPTIMALIZER_H
#define MOVEOPTIMALIZER_H

#include "Board.h"
#include "ExhaustiveVisitor.h"
#include "ScoreRank.h"

#include <string>
#include <vector>

typedef std::vector<ScoreRank::RankEntity>::const_iterator Result_it;

class MoveOptimalizer
{
public:


    MoveOptimalizer( const std::string& DictPath,
                     const std::string& inputBoardPath );
    virtual ~MoveOptimalizer( );

    void OptimizeMove( std::vector<char>& tileToPlace );

    Result_it& result_begin( );
    Result_it& result_end( );

private:
    Board               m_iniBoard;
    ScoreRank           m_ranker;
    ExhaustiveVisitor   m_visitor;
    std::string         m_inputBoardPath;
    Result_it           m_resultBegin;
    Result_it           m_resultEnd;
};


#endif