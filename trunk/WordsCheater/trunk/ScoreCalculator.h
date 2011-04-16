#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

class Board;
class Dictionary;

class ScoreCalculator
{
private:
    enum LineScoreResult
    {
        NEVER_VALID,
        NOT_VALID,
        ONE_TILE,
        VALID,
    };

public:
    ScoreCalculator( Board* board, Dictionary* dict );
    ~ScoreCalculator( );

    bool Calculate( int& score );
    LineScoreResult CalculateLine( const int row,
                                   const int col,
                                   const bool isVertical,
                                   int& score );

private:
    Board*	        m_board;
    Dictionary*     m_dict;

};

#endif