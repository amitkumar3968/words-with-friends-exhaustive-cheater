#ifndef BOARDPOSINFO_H
#define BOARDPOSINFO_H

struct BoardPosInfo
{
    enum TilePosType { NONE,
                       ORIGINAL,
                       PLACED };

    explicit BoardPosInfo( );

    TilePosType  m_tilePosType;
    char         m_char;
};

#endif