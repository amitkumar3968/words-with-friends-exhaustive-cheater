#ifndef MOVEOPTIMALIZER_H
#define MOVEOPTIMALIZER_H

#include "Board.h"
#include "ExhaustiveVisitor.h"
#include "ScoreRank.h"

#include <string>
#include <vector>

class MoveOptimalizer
{
public:


    MoveOptimalizer( const std::string& DictPath,
                     const std::string& inputBoardPath );
    virtual ~MoveOptimalizer( );

    void OptimizeMove( std::string& tileToPlace );

    void printResultToStream( std::ostream& stream );

private:
    Board               m_iniBoard;
    ScoreRank           m_ranker;
    ExhaustiveVisitor   m_visitor;
    std::string         m_inputBoardPath;

};


#endif